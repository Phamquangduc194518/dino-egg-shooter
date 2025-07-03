#include <gui/screen1_screen/Screen1View.hpp>
#include "cmsis_os.h"
#include <cmath>
#include "Vector2.hpp"
#include <cstdio>
#include <gui/model/Model.hpp>
extern "C" {
#include "FlashStorage.h"
}
extern osMessageQueueId_t Queue1Handle;
#define pi 3.14
#define maxTime 20000
#define maxEggAllow 30
float CalculateEggAngle(int tickCount);
touchgfx::Unicode::UnicodeChar pointBuffer[10];      // đủ cho 5 chữ số + null
touchgfx::Unicode::UnicodeChar eggsNumberBuffer[10];
touchgfx::Unicode::UnicodeChar eggsCapBuffer[10];    // đủ cho dạng "Eggs: 5/10"
touchgfx::Image brokenegg;
Screen1View::Screen1View()
{
	grid1		 		= grid();
	rngValue 			= 1;
	tickCount 			= 0;
	tickDelay 			= 100;
	tickRecord 			= 0;
	currentShotImage 	= nullptr;
	eggPool 			= eggPoolManager();
	levelController 	= gameLevel();

	originX				= currentEgg.getX();
	originY				= currentEgg.getY();

	isShot 				= 0;
	direction 			= -pi/3;
	storeX 				= 0;
	storeY 				= 0;
	eggNumber 			= 0;

	time				= maxTime;
	maxEgg				= maxEggAllow;
	invalidate();

	score =0;
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    changeShotImage(&rngValue);
    loadLevel(presenter->getLevel());
//    Flash_Clear();
    brokenegg.setBitmap(Bitmap(BITMAP_EGG_BROKEN_ID));
    brokenegg.setVisible(false);
    brokenegg.setAlpha(255);
    brokenegg.setXY(0, 0);
    add(brokenegg);
    brokenegg.invalidate();

    splashTimer = 0;
    isSplashVisible = false;
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}
void Screen1View::handleTickEvent()
{

	if(time <=0|| eggNumber >= maxEggAllow)
	{
		time = 0;
		for (int y = 0; y < GRID_SIZE_Y; ++y) {
		        for (int x = 0; x < GRID_SIZE_X; ++x) {
		            vector2 pos(x, y);
		            if (grid1.getGridValue(pos) != 0) {
		                touchgfx::Image* egg = grid1.getGridReference(pos);
		                if (egg) {
		                    egg->setVisible(false);
		                    egg->setAlpha(0);
		                    egg->invalidate();
		                    eggPool.returnEggToPool(egg);
		                    remove(*egg);
		                }
		                grid1.setGridValue(pos, 0);
		                grid1.setGridReference(pos, nullptr);
		            }
		        }
		    }

		    eggNumber = 0;
		    presenter->onLose(score);
		    static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen3ScreenNoTransition();
	}
	else if (eggNumber ==0)
	{
		presenter->onLose(score);
		static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen3ScreenNoTransition();
	}

	if (isSplashVisible) {
	    splashTimer++;
	    if (splashTimer > 10) {
	        brokenegg.setVisible(false);
	        brokenegg.invalidate();
	        isSplashVisible = false;
	    }
	}

	Screen1ViewBase::handleTickEvent();
	tickCount++;

	float eggAngle = CalculateEggAngle(tickCount);
	time -= 1 ; // time Score
	updateText( time, eggNumber,maxEgg);


	// Process incoming message first to trigger a new shot
	if(osMessageQueueGetCount(Queue1Handle) > 0)
	{
		uint8_t res;
		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if(res=='T' && !isShot)
		{
			//TODO, add soundEff
			//Shot Sound
			tickRecord = tickCount;
			createNewImage(&rngValue);
			currentEgg.setAlpha(0);
			changeShotImage(&rngValue);
			currentShotImage->moveTo(originX, originY);
			isShot = 1;
			storeX =0;
			storeY =0;
			direction = eggAngle;
		}
	}


	// If a shot is active, update the egg's position
	if(isShot)
	{
		// check the current direction. if need to change change this
		float dx = sin(direction);
		float dy = -cos(direction);
		float currentX = currentShotImage->getX();
		float currentY = currentShotImage->getY();
		float checkX = currentX + 1 * GRID_UNIT * (direction > pi ? -1 : 1);
		float checkY = currentY - 1 * GRID_UNIT;

		vector2 nextHorizontalGridPos = grid1.getGridFromPosition(checkX, currentY);
		vector2 nextVerticalGridPos = grid1.getGridFromPosition(currentX, checkY);
		vector2 currentGridPos = grid1.getGridFromPosition(currentX, currentY);

		if(nextHorizontalGridPos.x == -1 && direction > pi)
		{
			direction = 2*pi - direction;
		}
		else if(nextHorizontalGridPos.x == GRID_SIZE_X && direction < pi)
		{
			direction = 2*pi - direction;
		}

		//change direction
		dx = sin(direction);
		dy = -cos(direction);

		//ball movement base on dx, dy.
		storeX += dx * 6.0f; // change to speed value
		storeY += dy * 6.0f;

		int moveX = static_cast<int>(storeX);
		int moveY = static_cast<int>(storeY);

		// Handle stacking balls
		if(nextVerticalGridPos.y ==-1 || grid1.getGridValue(nextHorizontalGridPos)!=0 || grid1.getGridValue(nextVerticalGridPos)!=0)
		{
			if(grid1.getGridValue(currentGridPos) != 0)
			{
				if(grid1.getGridValue(nextVerticalGridPos) == 0)
				{
					currentShotImage->moveTo(
						grid1.getPosX(currentGridPos),
						grid1.getPosY(vector2(0, currentGridPos.y + 1))
					);
				}
				else if(grid1.getGridValue(nextHorizontalGridPos) == 0)
				{
					int offset = (direction > pi) ? 1 : -1;
					currentShotImage->moveTo(
						grid1.getPosX(vector2(0, currentGridPos.y + offset)),
						grid1.getPosY(currentGridPos)
					);
				}
			}


			else
			{
				currentShotImage->moveTo(grid1.getPosX(currentGridPos), grid1.getPosY(currentGridPos));
			}

			grid1.setGridValue(currentGridPos, rngValue);
			grid1.setGridReference(currentGridPos, currentShotImage);
			handleCollision();
			currentEgg.setAlpha(255);
			currentEgg.invalidate();
			isShot = 0;
		}
		// Handle Move
		else if (moveX != 0 || moveY != 0)
		{
			currentShotImage->moveRelative(moveX, moveY);
			currentShotImage->invalidate();

			storeX -= moveX;
			storeY -= moveY;
		}
	}
	else
	{

	}
	EggDirection.setZAngle(eggAngle);
	EggDirection.invalidate();

}

void Screen1View::createNewImage(uint8_t RNGValue)
{
	auto egg = eggPool.getEggFromPool();
	if (egg) {
		switch(RNGValue)
		{
			case 1:
				egg->setBitmap(touchgfx::Bitmap(BITMAP_EGG_BLUE_ID));
				break;
			case 2:
				egg->setBitmap(touchgfx::Bitmap(BITMAP_EGG_GREEN_ID));
				break;
			case 3:
				egg->setBitmap(touchgfx::Bitmap(BITMAP_EGG_RED_ID));
				break;
			case 4:
				egg->setBitmap(touchgfx::Bitmap(BITMAP_EGG_ORANGE_ID));
				break;
		}

	    egg->setXY(originX, originY);
	    egg->setVisible(true);
	    egg->setAlpha(255);
	    add(*egg);
	    egg->invalidate();
	}
    currentShotImage = egg;
}
void Screen1View::createNewImage(uint8_t *RNGValue)
{
	auto egg = eggPool.getEggFromPool();
	if (egg) {
		switch(*RNGValue)
		{
			case 1:
				egg->setBitmap(touchgfx::Bitmap(BITMAP_EGG_BLUE_ID));
				break;
			case 2:
				egg->setBitmap(touchgfx::Bitmap(BITMAP_EGG_GREEN_ID));
				break;
			case 3:
				egg->setBitmap(touchgfx::Bitmap(BITMAP_EGG_RED_ID));
				break;
			case 4:
				egg->setBitmap(touchgfx::Bitmap(BITMAP_EGG_ORANGE_ID));
				break;
		}

	    egg->setXY(originX, originY);
	    egg->setVisible(true);
	    egg->setAlpha(255);
	    add(*egg);
	    egg->invalidate();
	}
    currentShotImage = egg;
}

void Screen1View::changeShotImage(uint8_t *RNGValue)
{
	switch(*RNGValue)
	{
		case 1:
			currentEgg.setBitmap(touchgfx::Bitmap(BITMAP_EGG_BLUE_ID));
			break;
		case 2:
			currentEgg.setBitmap(touchgfx::Bitmap(BITMAP_EGG_GREEN_ID));
			break;
		case 3:
			currentEgg.setBitmap(touchgfx::Bitmap(BITMAP_EGG_RED_ID));
			break;
		case 4:
			currentEgg.setBitmap(touchgfx::Bitmap(BITMAP_EGG_ORANGE_ID));
			break;
	}
	currentEgg.invalidate();
}

void Screen1View::handleCollision()
{
	//TODO, add soundEff
	//Collition sound
    float currentX = currentShotImage->getX();
    float currentY = currentShotImage->getY();
    vector2 currentGridPos = grid1.getGridFromPosition(currentX, currentY);
    vector2 output[64];
    int floodFillCount = grid1.floodFill(currentGridPos.x, currentGridPos.y, output, 64);
    eggNumber++;
    if (floodFillCount > 2)
    {
    	//TODO, add soundEff
    	//Break sound
    	score += floodFillCount * 10;
    	vector2 splashPos = output[0];  // Vị trí quả trứng đầu tiên trong nhóm
    	int splashX = grid1.getPosX(splashPos);
    	int splashY = grid1.getPosY(splashPos);

    	splashX += (GRID_UNIT - brokenegg.getWidth()) / 2;
    	splashY += (GRID_UNIT - brokenegg.getHeight()) / 2;

    	brokenegg.setXY(splashX, splashY);
    	brokenegg.setVisible(true);
    	brokenegg.invalidate();
    	splashTimer = 0;
        isSplashVisible = true;

        for (int i = 0; i < floodFillCount; i++)
        {
            vector2 pos = output[i];
            touchgfx::Image* egg = grid1.getGridReference(pos);
            if (egg)
            {
            	egg->setVisible(false);
            	egg->setAlpha(0);
            	egg->invalidate();
                eggPool.returnEggToPool(egg);
                eggNumber--;
                remove(*egg);
            }
            grid1.setGridValue(pos, 0);
            grid1.setGridReference(pos, nullptr);
        }
    }

    grid1.resetVisit();
    do
    {
        floodFillCount = grid1.findIsolatedGroupsWithoutYZero(output);
        for (int i = 0; i < floodFillCount; i++)
        {
            vector2 pos = output[i];
            touchgfx::Image* egg = grid1.getGridReference(pos);
            if (egg)
            {
            	egg->setVisible(false);
            	egg->setAlpha(0);
            	egg->invalidate();
                eggPool.returnEggToPool(egg);
                eggNumber--;
                remove(*egg);
            }
            grid1.setGridValue(pos, 0);
            grid1.setGridReference(pos, nullptr);
        }

    } while (!grid1.doneVisit);

    rngValue = tickRecord % 4 + 1;
    changeShotImage(&rngValue);
}


float CalculateEggAngle(int tickCount)
{
	float cycle = tickCount % 360;
	float returValue  =0;
	if(cycle< 60)
	{
		returValue= cycle /2 ; // 0-30 return 0-30
	}
	else if(cycle < 90)
	{
		returValue=  cycle-30; // 30-90 return 30-60
	}
	else if(cycle < 120)
	{
		returValue=  150-cycle; // 90-120 return 60-30
	}
	else if(cycle < 180)
	{
		returValue=  (180-cycle)/2; // 120-180 return 30-0
	}
	else if(cycle < 240)
	{
		returValue= 450 - cycle/2; // 180-240 return 360-330
	}
	else if(cycle < 270)
	{
		returValue= 570 - cycle; // 240-270 return 330-300
	}
	else if(cycle < 300)
	{
		returValue= cycle + 30; // 270-300 return 300-330
	}
	else if(cycle < 360)
	{
		returValue= cycle/2 + 180; // 300-360 return 330-360
	}

	return returValue * 3.14/180 ;
}

void Screen1View::loadLevel(int levelIndex)
{
	eggNumber = 0;
    level currentLevel = levelController.getLevel(levelIndex);

    for (int i = 0; i < 77; ++i)
    {
        uint8_t tileType = currentLevel.levelData[i];
        if (tileType != 0)
        {
            vector2 gridPos = vector2(i%11,i/11);
            eggNumber++;
            // Create a new image for this tile
            createNewImage(tileType);
            currentShotImage->moveTo(grid1.getPosX(gridPos), grid1.getPosY(gridPos));
            grid1.setGridValue(gridPos, tileType);
            grid1.setGridReference(gridPos, currentShotImage);

        }
    }
    printf(">>> Loaded level %d, eggNumber = %d\n", levelIndex, eggNumber);
}

int Screen1Presenter::getLevel()
{
    return model->getLevel();
}

void Screen1Presenter::onLose(int score)
{
    return model->setScore(score);
}
void Screen1View::updateText(int score, int collected, int total)
{
    Unicode::snprintf(pointBuffer, sizeof(pointBuffer) / sizeof(pointBuffer[0]), "%d", score);
    Point.setWildcard(pointBuffer);
    Point.invalidate();

    Unicode::snprintf(eggsNumberBuffer, sizeof(eggsNumberBuffer) / sizeof(eggsNumberBuffer[0]), "%d", collected);
    Unicode::snprintf(eggsCapBuffer, sizeof(eggsCapBuffer) / sizeof(eggsCapBuffer[0]), "%d", total);

    EggsCap.setWildcard1(eggsNumberBuffer);
    EggsCap.setWildcard2(eggsCapBuffer);
    EggsCap.invalidate();
}
