#include <gui/screen3_screen/Screen3View.hpp>
#include <cstdio>
#include <gui/model/Model.hpp>
#include "cmsis_os.h"
#include <gui/model/Model.hpp>
extern osMessageQueueId_t Queue1Handle;
touchgfx::Unicode::UnicodeChar point3Buffer[10];
Screen3View::Screen3View()
{

}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
    score = presenter->loadScore();
    updateText();
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}

void Screen3View::handleTickEvent()
{
	Screen3ViewBase::handleTickEvent();
	if(osMessageQueueGetCount(Queue1Handle) > 0)
	{
		uint8_t res;
		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if(res=='T')
		{
			static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen2ScreenNoTransition();
		}
	}
}
void Screen3View::updateText()
{
    Unicode::snprintf(point3Buffer, sizeof(point3Buffer) / sizeof(point3Buffer[0]), "%d", score);
    ScoreText.setWildcard(point3Buffer);
    ScoreText.invalidate();
}

int Screen3Presenter::loadScore()
{
	return model->getScore();
}


