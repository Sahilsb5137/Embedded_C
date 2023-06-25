//STM32F411 Nucleo Board

//PA2 -> USART2 Tx
//PA3 -> USART2 Rx
//PA2 & PA3 -> AF07 (GPIO Alternate Function)

#include <stdint.h>
#include <stm32f4xx.h>

#define GPIOAEN		(1U<<0)
#define USART2EN	(1U<<17)

#define CR1_TE		(1U<<3)
#define CR1_UE		(1U<<13)

#define SR_TXE		(1U<<7)

#define SYS_FREQ	16000000
#define APB1_CLK	SYS_FREQ
#define UART_BAUDRATE	115200



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);


void uart2_tx_init(void);
void UART2_sendChar(int ch);


int main(void)
{
	uart2_tx_init();

	while(1)
	{
		UART2_sendChar('S');
	}

}


void uart2_tx_init(void)
{
	//************Configure UART GPIO Pins************
	//1. Enable Clock Access to GPIOA
	RCC-> AHB1ENR |= GPIOAEN;

	//2. Set PA2 mode to Alternate Function Mode
	GPIOA-> MODER &=~(1U<<4);
	GPIOA -> MODER |= (1U<<5);

	//3.Set PA2 Alternate Function Type to UART_Tx (AF7). AFRL -> [0]
	GPIOA-> AFR[0] |= (1<<8);
	GPIOA-> AFR[0] |= (1<<9);
	GPIOA-> AFR[0] |= (1<<10);
	GPIOA-> AFR[0] &=~ (1<<11);

	//************Configure UART Module************
	//1. Clock Access to UART
	RCC-> APB1ENR |= USART2EN;

	//2. Configure the BaudRate
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	//3.Configure Transfer Direction
	USART2->CR1 = CR1_TE;

	//4.Enable UART Module
	USART2->CR1 |= CR1_UE;

}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + BaudRate/2U)/BaudRate);

}

void UART2_sendChar(int ch)
	{
		//1. Make sure the Transmit Data Register is Empty
		while(!(USART2->SR & SR_TXE)){}

		// To make sure the Tx DR is Empty, we have to make sure that USART2 SR reads the SR TXE. To read a bit '&' operator is used.
		//As long as the TXE is false, it will loop and once the condition gets true, it will write to transmit the data

		//2. Write to transmit data register
		USART2->DR = (ch & 0xFF); //Load the data in the USART2 Data Register
	}

