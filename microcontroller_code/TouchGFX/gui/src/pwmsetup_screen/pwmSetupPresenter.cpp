#include <gui/pwmsetup_screen/pwmSetupView.hpp>
#include <gui/pwmsetup_screen/pwmSetupPresenter.hpp>


pwmSetupPresenter::pwmSetupPresenter(pwmSetupView& v)
    : view(v)
{

}

void pwmSetupPresenter::activate()
{

}

void pwmSetupPresenter::deactivate()
{

}

void pwmSetupPresenter::changePWMfreq(int value)
{
	model -> changePWMfreq(value);
}
void pwmSetupPresenter::pwmStart()
{
	model-> pwmStart();
}
void pwmSetupPresenter::pwmStop()
{
	model-> pwmStop();
}
