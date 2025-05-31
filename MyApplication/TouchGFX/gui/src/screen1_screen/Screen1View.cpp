#include <gui/screen1_screen/Screen1View.hpp>
#include "cmsis_os.h"
#include <cmath>

extern osMessageQueueId_t Queue1Handle;
void CalculateEggAngle(int tickCount, float &eggAngle);
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

	float eggAngle;
	CalculateEggAngle(tickCount, eggAngle);

	EggDirection.setZAngle(eggAngle * (3.14f/180.0f));

	if(isShot)
	{
		float posX = currentEgg.getX() + sin(direction)*3;
		float posY = currentEgg.getY() - cos(direction)*3;
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

void CalculateEggAngle(int tickCount, float &eggAngle)
{
	int cycle = tickCount % 180;
		if(cycle < 90)
		{
			eggAngle = 315 + cycle; // increasing from -45 to 45
		}
		else
		{
			eggAngle = 405 - (cycle - 90); // decreasing from 45 back to -45
		}
}
