//STM32F411 Nucleo Board

//PA2 -> USART2 Tx
//PA3 -> USART2 Rx
//PA2 & PA3 -> AF07 (GPIO Alternate Function)
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include <uart.h>

#define GPIOAEN		(1U<<0)
#define GPIOA_5		(1U<<5) //User LED
#define LED_PIN		GPIOA_5


char key;

int main(void)
{
	//1. Enable Clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//2. Set PA5 as output pin
	GPIOA->MODER &=~ (1U<<11);
	GPIOA->MODER |= (1U<<10);


	uart2_rxtx_init();

	while(1)
	{
		key = UART2_readChar();
		if(key == '1')
		{
			GPIOA->ODR |= LED_PIN;
		}
		else
		{
			GPIOA->ODR &= ~LED_PIN;
		}
	}

}

