#include <gui/pwmsetup_screen/pwmSetupView.hpp>

pwmSetupView::pwmSetupView()
{

}

void pwmSetupView::setupScreen()
{
    pwmSetupViewBase::setupScreen();
}

void pwmSetupView::tearDownScreen()
{
    pwmSetupViewBase::tearDownScreen();
}

void pwmSetupView::changePWMfreq(int value)
{
	presenter-> changePWMfreq(value);
}

void pwmSetupView::pwmStart()
{
	presenter-> pwmStart();
}
void pwmSetupView::pwmStop()
{
	presenter-> pwmStop();
}
