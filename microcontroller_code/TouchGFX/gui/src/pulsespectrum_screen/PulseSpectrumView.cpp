/*View is the visual appearance of the UX*/

#include <gui/pulsespectrum_screen/PulseSpectrumView.hpp>
#include <stdlib.h>
#include <math.h>

/**/
PulseSpectrumView::PulseSpectrumView()
{

	// initialize elements of array binCounter to 0
   for ( int i = 0; i < 1000; i++ )
   {
	  binCounter[i] = 0;
   }
}

void PulseSpectrumView::setupScreen()
{
    PulseSpectrumViewBase::setupScreen();
}

void PulseSpectrumView::tearDownScreen()
{
    PulseSpectrumViewBase::tearDownScreen();
}

void PulseSpectrumView::UpdateGraph(uint16_t value)
{
	//int mappedVal = ((int)value)*(999)/(4095);//map 12 bit number onto a 0-999 (no offset)
	int mappedVal = ((int)value+1404)*(999)/(4095);//map 12 bit number onto a 0-999 (with offset)
	histogram.addDataPoint(mappedVal, binCounter[mappedVal]);
	binCounter[mappedVal] = binCounter[mappedVal] +1;
	//histogram.addDataPoint(value, binCounter[value]);
	//binCounter[value] = binCounter[value] +1;

}

void PulseSpectrumView::clearGraph()
{
    for(int k = 0; k<1000; k++)
    {
    	histogram.addDataPoint(k, 0);
    	binCounter[k]=0;
    }
}
