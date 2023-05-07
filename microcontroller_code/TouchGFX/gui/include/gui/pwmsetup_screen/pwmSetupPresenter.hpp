#ifndef PWMSETUPPRESENTER_HPP
#define PWMSETUPPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class pwmSetupView;

class pwmSetupPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    pwmSetupPresenter(pwmSetupView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~pwmSetupPresenter() {};

    void changePWMfreq(int value);

    void pwmStart();

    void pwmStop();

private:
    pwmSetupPresenter();

    pwmSetupView& view;
};

#endif // PWMSETUPPRESENTER_HPP
