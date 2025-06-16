#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include "../../../../../STM32CubeIDE/Application/User/grid.hpp"
#include "../../../../generated/images/include/BitmapDatabase.hpp"
#include "../../../../../STM32CubeIDE/Application/User/eggPool.hpp"
#include "../../../../../STM32CubeIDE/Application/User/gameLevel.hpp"
class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void createNewImage(uint8_t RNGValue);
    virtual void createNewImage(uint8_t *RNGValue);
    virtual void changeShotImage(uint8_t *RNGValue);
    virtual void handleCollision();
    virtual void loadLevel(int levelIndex);
    virtual void updateText(int score, int collected, int total);

protected:

    uint8_t rngValue;
    uint32_t tickCount;
    uint32_t tickDelay;
    uint32_t tickRecord;
    uint16_t originX;
    uint16_t originY;
    bool isShot;
    float direction;
    float storeX;
    float storeY;
    int time;
    int eggNumber;
    int maxEgg;
    grid grid1;
    gameLevel levelController;
    touchgfx::Image* currentShotImage;
    eggPoolManager eggPool;     
};

#endif // SCREEN1VIEW_HPP
