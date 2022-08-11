#include "stm32f10x.h"


int main(){
	
	//enable clock USART1EN, alt functions, and GPIOA
	
	RCC->APB2ENR |=RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
	
	// if needed remap USART1
	
	// pin configuration PA9 is default Tx and PA10 is Rx
	
	GPIOA ->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;
	GPIOA-> CRH &=~( GPIO_CRH_CNF9_0);
	
	// PA10 is input Rx and is by default 00 - input floating
	
	// setting baud rate --- 72Mhz/(16*9600)= 468.75 in HEX it is 1D4C
	
	USART1->BRR = 0x1D4C;
	
	//enable UART Interrupts
	
	USART1->CR1 |=USART_CR1_RXNEIE | USART_CR1_TXEIE;
	// enable Rx Tx Uart
	
	USART1->CR1 |=USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
	
	// enable interrupt on NVIC side
	
	NVIC_EnableIRQ(USART1_IRQn);
	
	while(1){
		
		if(USART1->SR & USART_SR_RXNE){ // if Rx is not empty
			
			char temp=USART1-> DR; // fetch the data from Data register
			USART1->DR = temp; // send it bck to DR - physicaly not same place
			while(!(USART1->SR & USART_SR_TC));} // wait for Tx to be completed 
		
		}
	
	}

	void USART1_IRQHandler(void){
		
		//check if we are here because of RXNEIE flag
		if(USART1->SR & USART_SR_RXNE){ // if Rx is not empty
			
			char temp=USART1-> DR; // fetch the data from Data register
			USART1->DR = temp; // send it bck to DR - physicaly not same place
			while(!(USART1->SR & USART_SR_TC));} // wait for Tx to be completed 
		
	
		//check if we are here because of TXIE flag
		
		if(USART1->SR & USART_SR_TXE){ // check if transmission is not empty
			//hnadle transmitt completion here
		}
		
	}

