/*Model is interfaced to the system/main.c
 * model is the only interface with hardware and backend application*/
#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_it.h>
#include <stdint.h>

/*declare any variables from main here*/
extern __IO uint16_t pulseHeight;
extern TIM_HandleTypeDef htim12;
/*local variables*/
volatile uint16_t lastHeight = 0;
Model::Model() : modelListener(0)
{

}

//this function gets called every time the screen refreshes, typically 60Hz
void Model::tick()
{

	if( (pulseHeight != lastHeight) && (pulseHeight != 0) )
	{
		lastHeight = pulseHeight;
		modelListener->UpdateGraph(pulseHeight);

	}
}

void Model::changePWMfreq(int value)
{
	//HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	//__HAL_TIM_SET_PRESCALER(&htim12, value-1);
	__HAL_TIM_SET_AUTORELOAD(&htim12, value);
}

void Model::pwmStop()
{
	HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_1);
}
void Model::pwmStart()
{
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
}

