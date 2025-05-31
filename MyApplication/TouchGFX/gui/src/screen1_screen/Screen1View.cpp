#include <gui/screen1_screen/Screen1View.hpp>
#include "cmsis_os.h"
#include <cmath>
#include "Vector2.hpp"

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

	EggDirection.setZAngle(eggAngle * (3.14f/180.0f));

	if(isShot)
	{
		float posX = currentEgg.getX() + sin(direction)*3;
		float posY = currentEgg.getY() - cos(direction)*3;

		vector2 nextGridPos = grid1.getGridFromPosition(posX,posY);
		vector2 currentGridPos = grid1.getGridFromPosition(posX,posY);
		if(nextGridPos.x < 0 && direction > 3.14)
		{
			direction = 6.28 - direction  ;
		}
		else if(nextGridPos.x >= GRID_SIZE_X-1 && direction < 3.14)
		{
			direction = 6.28 - direction;
		}

		currentEgg.moveTo(posX,posY);
	}


	if(osMessageQueueGetCount(Queue1Handle)>0)
	{

		uint8_t res;
		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if(res=='T')
		{
			tickRecord = tickCount;
//			TestingEgg.moveTo(grid1.getPosX(testValue), grid1.getPosY(testValue));
//			testValue++;
			currentEgg.moveTo(originX,originY);
			isShot = 1;
			direction = eggAngle * (3.14f/180.0f);
		}

		if(tickCount- tickRecord >= tickDelay)
		{
			isShot = 0;
		}
	}
	invalidate();
}

float  CalculateEggAngle(int tickCount)
{
	int cycle = tickCount % 240;
		if(cycle< 60)
		{
			return cycle;
		}
		else if(cycle < 120)
		{
			return   120 - cycle;
		}
		else if(cycle < 180)
		{
			return 480 - cycle;
		}
		else if(cycle < 240)
		{
			return  120 + cycle;
		}
}
