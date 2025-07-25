/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN4VIEWBASE_HPP
#define SCREEN4VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen4_screen/Screen4Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

class Screen4ViewBase : public touchgfx::View<Screen4Presenter>
{
public:
    Screen4ViewBase();
    virtual ~Screen4ViewBase();
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void onLevel1Clicked()
    {
        // Override and implement this function in Screen4
    }
    virtual void onLevel2Clicked()
    {
        // Override and implement this function in Screen4
    }
    virtual void onLevel3Clicked()
    {
        // Override and implement this function in Screen4
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::ButtonWithLabel Level3;
    touchgfx::ButtonWithLabel Level2;
    touchgfx::ButtonWithLabel Level1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen4ViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SCREEN4VIEWBASE_HPP
