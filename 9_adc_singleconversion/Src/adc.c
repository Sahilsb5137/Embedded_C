/*
 * adc.c
 *
 *  Created on: May 3, 2023
 *      Author: 14699
 */
#include "stm32f4xx.h"
#include "adc.h"

#define ADC1EN		(1U<<8)
#define GPIOAEN		(1U<<0)
#define ADC_CH1		(1U<<0)
#define ADC_SEQ_LEN	0x00
#define CR2_ADON	(1U<<0)
#define CR2_SWSTART	(1U<<30)
#define SR_EOC		(1U<<1)


void adc_init(void)
{
	//***************** Configure ADC GPIO Pins *****************
	/*
	 * ADC1 has 16 channels and we can use any one channel. I chose ADC1_1
	 * ADC1_1 corresponds to GPIOA -> PA1
	 */

	//1. Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//2. Set the mode of PA1 to Analog Mode
	GPIOA-> MODER |= (1U<<2);
	GPIOA-> MODER |= (1U<<3);

	//***************** Configure ADC Module *****************
	//1. Enable clock access to ADC
	RCC->APB2ENR |= ADC1EN;

	//2.Conversion Sequence start (SQR3)
	ADC1-> SQR3 = ADC_CH1;

	//3.Conversion Sequence Length (SQR1)
	ADC1-> SQR1 = ADC_SEQ_LEN;

	//4.Enable ADC Module (CR1)
	ADC1-> CR2 |= CR2_ADON;

}

void start_conversion (void)
{
	ADC1-> CR2 |= CR2_SWSTART; // Starts Conversion
}

uint32_t adc_read(void)
{
	//1. Wait for conversion to complete
	while (!(ADC1->SR & SR_EOC));

	//2.Read converted result
	return (ADC1->DR);
}





