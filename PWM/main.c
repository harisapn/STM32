#include "printMsg.h"
#include "stm32f10x.h"

int main(){
	
	RCC->APB2ENR |=RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN |RCC_APB2ENR_USART1EN;
	
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	GPIOA-> CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1; //confgure pin as 10 - output pull -push at 50MHz
	 GPIOA -> CRH &= ~(GPIO_CRH_CNF9_0); // need to set first bit to zero, because reset state is 01
	
	
GPIOB-> CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1; //confgure pin as 10 - output pull -push at 50MHz
	 GPIOB -> CRH &= ~(GPIO_CRH_CNF9_0); // need to set first bit to zero, because reset state is 01
	
	//setting baund rate
	 USART1->BRR = 0x1d4c; // 72 MHz dived by (9600 x 16)
	 USART1 ->CR1 |=USART_CR1_TE; // transmission enable
	 USART1 -> CR1 |=USART_CR1_UE; // usart enable
	
	// PWM freq=Fclk/PSC/ARR
	// PWM duty=CCR4/ARR
	
	
	TIM3 -> CCER |= TIM_CCER_CC4E; // channel 4 of TIM3 capture*compare enable
	TIM3->CR1 |= TIM_CR1_ARPE; // auto-reload preload enable
	
	TIM3->CCMR2 =TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE; //enabling timer PWM mode 1 -110
	
	
	
	

	TIM3 ->PSC = 72; // 72mhy/1000=72000 --> PSC=72 and ARR = 1000
	TIM3->ARR= 1000;
	TIM3->CCR4 =250; // 25% duty cyle - active state till 250
	
	
	TIM3->EGR |= TIM_EGR_UG;
	TIM3 -> CR1 |= TIM_CR1_CEN; // enabling timer 
	
	
	
	
	
	
	printMsg("UART connection established /n");
	while (1)
	{
		
		printMsg(" %d", TIM3->CNT); 
	}
	
	
}
