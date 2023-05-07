#ifndef PULSESPECTRUMPRESENTER_HPP
#define PULSESPECTRUMPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class PulseSpectrumView;

class PulseSpectrumPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    PulseSpectrumPresenter(PulseSpectrumView& v);

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

    void UpdateGraph(uint16_t value);

    virtual void clearGraph();

    virtual ~PulseSpectrumPresenter() {};

private:
    PulseSpectrumPresenter();

    PulseSpectrumView& view;
};

#endif // PULSESPECTRUMPRESENTER_HPP
