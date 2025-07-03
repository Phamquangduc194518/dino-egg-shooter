#ifndef SCREEN4VIEW_HPP
#define SCREEN4VIEW_HPP

#include <gui_generated/screen4_screen/Screen4ViewBase.hpp>
#include <gui/screen4_screen/Screen4Presenter.hpp>

class Screen4View : public Screen4ViewBase
{
public:
    Screen4View();
    virtual ~Screen4View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void onLevel1Clicked();
    virtual void onLevel2Clicked();
    virtual void onLevel3Clicked();

protected:
};

#endif // SCREEN4VIEW_HPP
