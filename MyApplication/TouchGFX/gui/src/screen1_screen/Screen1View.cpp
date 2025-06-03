#include <gui/screen1_screen/Screen1View.hpp>
#include "cmsis_os.h"
#include <cmath>
#include "Vector2.hpp"
#include <cstdio>
#define pi 3.14

extern osMessageQueueId_t Queue1Handle;
float CalculateEggAngle(int tickCount);
Screen1View::Screen1View()
{
	tickCount = 0;
	testValue = 0;
	tickDelay = 100;
	tickRecord =0;
	isShot =0;
	originX= currentEgg.getX();
	originY= currentEgg.getY();
	grid1 = grid();
	direction = -pi/3;
	storeX = 0;
	storeY = 0;
	newShotImageCounter = 0;
	currentShotImage = nullptr;
	eggPool = eggPoolManager();	
}


void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}
void Screen1View::handleTickEvent()
{

	Screen1ViewBase::handleTickEvent();
	tickCount++;

	float eggAngle = CalculateEggAngle(tickCount);



	// Process incoming message first to trigger a new shot
	if(osMessageQueueGetCount(Queue1Handle) > 0)
	{
		uint8_t res;
		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if(res=='T' && !isShot)
		{
			tickRecord = tickCount;
			createNewImage();
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
		float checkX = currentX + 0.5 * GRID_UNIT * (direction > pi ? -1 : 1);
		float checkY = currentY - 0.5 * GRID_UNIT;

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
		storeX += dx * 3.0f; // change to speed value
		storeY += dy * 3.0f;

		int moveX = static_cast<int>(storeX);
		int moveY = static_cast<int>(storeY);

		// Handle stacking balls
		if(nextVerticalGridPos.y ==-1 || grid1.getGridValue(nextVerticalGridPos)!=0 || grid1.getGridValue(nextHorizontalGridPos)!=0)
		{
			currentShotImage->moveTo(grid1.getPosX(currentGridPos), grid1.getPosY(currentGridPos));
			grid1.setGridValue(currentGridPos, 1);
			grid1.setGridReference(currentGridPos, currentShotImage);
			handleCollition();
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
		EggDirection.setZAngle(eggAngle);
	}

	invalidate();
}

void Screen1View::createNewImage()
{
	auto egg = eggPool.getEggFromPool();
	if (egg) {
		egg->setBitmap(touchgfx::Bitmap(BITMAP_GREEN_REMOVEBG_PREVIEW_ID));
	    egg->setXY(originX, originY);
	    egg->setVisible(true);
	    egg->setAlpha(255);
	    add(*egg);
	    egg->invalidate();
	}
    currentShotImage = egg;
    newShotImageCounter++;
}
void Screen1View::handleCollition()
{
	float currentX = currentShotImage->getX();
	float currentY = currentShotImage->getY();	
	vector2 currentGridPos = grid1.getGridFromPosition(currentX, currentY);
	vector2 output[64];
	int floodFillCount = grid1.floodFill(currentGridPos.x, currentGridPos.y, output, 64);
	if(floodFillCount > 3)
	{
		for(int i = 0; i < floodFillCount; i++)
		{
			grid1.setGridValue(output[i], 0);
			grid1.getGridReference(output[i])->setVisible(false);
			eggPool.returnEggToPool(grid1.getGridReference(output[i]));
			grid1.setGridReference(output[i], nullptr);
		}
	}

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


