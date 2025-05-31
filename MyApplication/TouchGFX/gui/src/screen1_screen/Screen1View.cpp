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
		if(res=='T'&&!isShot)
		{
			tickRecord = tickCount;
			currentEgg.moveTo(originX, originY);
			isShot = 1;
			storeX =0;
			storeY =0;
			direction = eggAngle;
		}
	}


	// If a shot is active, update the egg's position
	if(isShot)
	{
		float sinx = sin(direction);
		float cosx = cos(direction);
		storeX += sinx;
		storeY -= cosx;
		float moveX = currentEgg.getX() + sinx*3;
		float moveY = currentEgg.getY() - cosx*3;

		vector2 nextGridPos = grid1.getGridFromPosition(moveX, moveY);
		vector2 currentGridPos = grid1.getGridFromPosition(currentEgg.getX(), currentEgg.getY());

		if(nextGridPos.x < 0 && direction > 3.14)
		{
			direction = 6.28 - direction;
		}
		else if(nextGridPos.x > GRID_SIZE_X - 1 && direction < 3.14)
		{
			direction = 6.28 - direction;
		}

		// Handle vertical (y-axis) boundaries: if the egg goes off the grid vertically, reset its position and stop the shot
		if(nextGridPos.y < 0 )
		{
			currentEgg.moveTo(grid1.getPosX(currentGridPos), grid1.getPosY(currentGridPos));
			isShot = 0;
		}
		else
		{
			if(storeX > 1)
			{
				currentEgg.moveRelative(1,0);
				storeX -= 1;
			}
			else if(storeX < -1)
			{
				currentEgg.moveRelative(-1,0);
				storeX += 1;
			}
		    if(storeY > 1)
			{
				currentEgg.moveRelative(0,1);
				storeY -= 1;
			}
			else if(storeY < -1)	
			{
				currentEgg.moveRelative(0,-1);
				storeY += 1;
			}
		}
	}
	else
	{
		EggDirection.setZAngle(eggAngle);
	}

	invalidate();
}

float  CalculateEggAngle(int tickCount)
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
