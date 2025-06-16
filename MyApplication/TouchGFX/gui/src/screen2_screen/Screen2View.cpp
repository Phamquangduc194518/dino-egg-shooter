#include <gui/screen2_screen/Screen2View.hpp>
#include <cstdio>
#include <gui/model/Model.hpp>
#include "cmsis_os.h"

extern osMessageQueueId_t Queue1Handle;

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::handleTickEvent()
{
	Screen2ViewBase::handleTickEvent();
	if(osMessageQueueGetCount(Queue1Handle) > 0)
		{
			uint8_t res;
			osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
			if(res=='T')
			{
				static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen4ScreenSlideTransitionWest();
			}
		}
}

