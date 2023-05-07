#ifndef STARTUPVIEW_HPP
#define STARTUPVIEW_HPP

#include <gui_generated/startup_screen/StartupViewBase.hpp>
#include <gui/startup_screen/StartupPresenter.hpp>

class StartupView : public StartupViewBase
{
public:
    StartupView();
    virtual ~StartupView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // STARTUPVIEW_HPP
