#include "stm32f10x.h"
#include <string.h>
#include "stdint.h"
#include <stdio.h>



void delayMs(int ms);
int msTicks;

int main(){
	
	// enable clocks 
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
  RCC ->APB1ENR |=RCC_APB1ENR_USART2EN;
	USART2->CR3 |= USART_CR3_DMAT;
	
	
	RCC->APB2ENR |=RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN; // na GPIOA2 je USART2
  
	// button pin input push pull
	
	RCC->APB2ENR|= RCC_APB2ENR_IOPCEN ;
	
	GPIOC-> CRL |= GPIO_CRL_CNF2_1;
	GPIOC-> CRL &= ~(GPIO_CRL_CNF2_0);
	GPIOC->ODR |= 1<<2;
	
	// GPIOA as input pull up push down mode 11
	
	GPIOA->CRL |= GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1;
	
	// GPIOA CNF na 10
	GPIOA->CRL |=GPIO_CRL_CNF2_1;
	GPIOA->CRL &=~(GPIO_CRL_CNF2_0);
	
	char myString[]="Hello World"; // string to be transmitted
	uint8_t len=strlen(myString);
	uint8_t count=0;
	
	USART2 ->BRR =0xEA6; // APB1 peripheral is 36MHz
	USART2->CR1 |=USART_CR1_UE;
	USART2->CR1 |=USART_CR1_TE;
	
	
	// DMA setting 
	
	DMA1_Channel7 ->CNDTR= len;
	DMA1_Channel7 ->CCR |=DMA_CCR7_MINC |DMA_CCR7_DIR | DMA_CCR7_TCIE | DMA_CCR7_CIRC; // memory increment, direction from memory, transmit interrupt enable and circular mode
	
	
	DMA1_Channel7->CPAR = (uint32_t)(&USART2->DR);
	DMA1_Channel7->CMAR =(uint32_t)(&myString);
	
	
	
	while (1){
		
		if(!(GPIOA->IDR & GPIO_IDR_IDR2)){ //button press
			
		/*	for (count=0;count<len;count++){
				USART2->DR=myString[count];
				
				while(!(USART2->SR & USART_SR_TC));}}  this is when done without DMA,manually */
		
			DMA1_Channel7 ->CCR |= DMA_CCR7_EN;//enable channel, when enabled it starts transmission
			
			while(!(DMA1->ISR & DMA_ISR_TCIF7)); // wait for the transfer to be completed
			
			DMA1 ->IFCR |= DMA_IFCR_CTCIF7; // clear the flag
			DMA1_Channel7->CCR &=~DMA_CCR7_EN; // disable channel
			
			
			
			
			}
		}
			
			
			
			
	
	
	

	}

	
