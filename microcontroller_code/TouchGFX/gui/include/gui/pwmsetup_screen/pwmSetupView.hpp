#ifndef PWMSETUPVIEW_HPP
#define PWMSETUPVIEW_HPP

#include <gui_generated/pwmsetup_screen/pwmSetupViewBase.hpp>
#include <gui/pwmsetup_screen/pwmSetupPresenter.hpp>

class pwmSetupView : public pwmSetupViewBase
{
public:
    pwmSetupView();
    virtual ~pwmSetupView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void changePWMfreq(int value);
    virtual void pwmStart();
    virtual void pwmStop();
protected:
};

#endif // PWMSETUPVIEW_HPP
