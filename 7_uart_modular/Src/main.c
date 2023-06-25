//STM32F411 Nucleo Board

//PA2 -> USART2 Tx
//PA3 -> USART2 Rx
//PA2 & PA3 -> AF07 (GPIO Alternate Function)
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include <uart.h>






int main(void)
{
	uart2_tx_init();

	while(1)
	{
		printf("Hello From STm32F411 Nucleo board.\n\r");
	}

}

