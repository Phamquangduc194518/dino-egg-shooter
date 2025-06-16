#include <gui/screen4_screen/Screen4View.hpp>
#include <cstdio>
#include <gui/model/Model.hpp>
#include "cmsis_os.h"

extern osMessageQueueId_t Queue1Handle;
Screen4View::Screen4View()
{

}

void Screen4View::setupScreen()
{
    Screen4ViewBase::setupScreen();
}

void Screen4View::tearDownScreen()
{
    Screen4ViewBase::tearDownScreen();
}
void Screen4View::handleTickEvent()
{
	Screen4ViewBase::handleTickEvent();
	if(osMessageQueueGetCount(Queue1Handle) > 0)
	{
		uint8_t res;
		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if(res=='T')
		{
			presenter->setLevel(0);
			static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen1ScreenNoTransition();
		}
	}
}
void Screen4Presenter::setLevel(int level)
{
    model->setLevel(level);
}
