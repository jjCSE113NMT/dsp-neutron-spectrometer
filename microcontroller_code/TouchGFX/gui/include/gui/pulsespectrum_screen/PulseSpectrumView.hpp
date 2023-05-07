#ifndef PULSESPECTRUMVIEW_HPP
#define PULSESPECTRUMVIEW_HPP

#include <gui_generated/pulsespectrum_screen/PulseSpectrumViewBase.hpp>
#include <gui/pulsespectrum_screen/PulseSpectrumPresenter.hpp>

class PulseSpectrumView : public PulseSpectrumViewBase
{
public:
    PulseSpectrumView();
    virtual ~PulseSpectrumView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void UpdateGraph(uint16_t value);
    virtual void clearGraph();
protected:
        int binCounter[1000];
};

#endif // PULSESPECTRUMVIEW_HPP
