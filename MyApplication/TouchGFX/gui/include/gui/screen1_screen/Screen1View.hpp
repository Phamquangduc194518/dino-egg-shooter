#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include "../../../../../STM32CubeIDE/Application/User/grid.hpp"
#include "../../../../generated/images/include/BitmapDatabase.hpp"
#include "../../../../../STM32CubeIDE/Application/User/eggPool.hpp"
class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void createNewImage();
    virtual void handleCollition();
protected:

    uint32_t tickCount;
    uint32_t testValue;
    uint32_t tickDelay;
    uint32_t tickRecord;
    uint16_t originX;
    uint16_t originY;
    bool isShot;
    float direction;
    float storeX;
    float storeY;
    grid grid1;

    touchgfx::Image* currentShotImage;
    int newShotImageCounter;

    eggPoolManager eggPool;  
};

#endif // SCREEN1VIEW_HPP
