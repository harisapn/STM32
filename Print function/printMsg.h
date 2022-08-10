#ifndef printMsg_H_
#define printMsg_H_

#include "stm32f10x.h"
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MODE_BIT_0_CRL (4*config.Tx_pinNumber)
#define MODE_BIT_1_CRL (4*config.Tx_pinNumber+1)
#define MODE_BIT_0_CRH (4*(config.Tx_pinNumber-8))
#define MODE_BIT_1_CRH ((4*(config.Tx_pinNumber-8)+1))

#define CNF_BIT_0_CRL  (4*config.Tx_pinNumber+2)
#define CNF_BIT_1_CRL  (4*config.Tx_pinNumber+3)
#define CNF_BIT_0_CRH ((4*(config.Tx_pinNumber-8))+2)
#define CNF_BIT_1_CRH ((4*config.Tx_pinNumber-8)+3)

typedef struct 
{
	USART_TypeDef *Uart_instances;
	int Tx_pinNumber;
	
	GPIO_TypeDef *Tx_port;

} print_Msg_config_type;

void printMsg_init(print_Msg_config_type config);
void printMsg(char *msg,...);

void printMsg_init(print_Msg_config_type config){
	
//enable clock
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	//tx pin port enable
	
	if(config.Tx_port == GPIOA) RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;
		if(config.Tx_port == GPIOB) RCC->APB2ENR |=RCC_APB2ENR_IOPBEN;
		if(config.Tx_port == GPIOC) RCC->APB2ENR |=RCC_APB2ENR_IOPCEN;
	
	

	// enable USART clock
	if(config.Uart_instances==USART1) RCC ->APB2ENR |=RCC_APB2ENR_USART1EN;
	if(config.Uart_instances==USART2) RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	
	// config the pin number as 50Mhz output push pull -----  mode 11 cnf 10
	
	if(config.Tx_pinNumber>7){
		config.Tx_port ->CRH |=(1<< MODE_BIT_0_CRH) | (1<<MODE_BIT_1_CRH) | (1<<CNF_BIT_1_CRH);
		config.Tx_port -> CRH &= ~(1<<CNF_BIT_0_CRH);
	}
	else {
		config.Tx_port ->CRL |=(1<< MODE_BIT_0_CRL) | (1<<MODE_BIT_1_CRL) | (1<<CNF_BIT_1_CRL);
		config.Tx_port -> CRL &= ~(1<<CNF_BIT_0_CRL);}
	
		
		//config USART baund rate 72MHz/(9600 *16)
		
		
		config.Uart_instances ->BRR = 0x1d4c;
		config.Uart_instances -> CR1 |= USART_CR1_TE;
		config.Uart_instances -> CR1 |= USART_CR1_UE;
		
		
	}

	void printMsg(char *msg,...){
		
		char buff[80];
		 
		 
		 va_list args;
		 va_start(args,msg);
		 vsprintf(buff, msg,args); // variable arguments in buffer
			
			
		 
		 for(int i=0; i<(strlen(buff)); i++){
			 
		USART1 ->DR =buff[i];
			 while(!(USART1->SR & USART_SR_TXE));}
	

		 }
	

#endif
