/*Presenter is the logic for the user interface
 * events flow from model and view to the presenter
 * processes events and updates according to changes in model and view
 * DSP, and calculations will take place here*/


#include <gui/pulsespectrum_screen/PulseSpectrumView.hpp>
#include <gui/pulsespectrum_screen/PulseSpectrumPresenter.hpp>

PulseSpectrumPresenter::PulseSpectrumPresenter(PulseSpectrumView& v)
    : view(v)
{

}

void PulseSpectrumPresenter::activate()
{

}

void PulseSpectrumPresenter::deactivate()
{

}

/*updates the histogram*/
void PulseSpectrumPresenter::UpdateGraph(uint16_t value)
{
	view.UpdateGraph(value);
}
/*updates the histogram*/
void PulseSpectrumPresenter::clearGraph()
{
	view.clearGraph();
}
