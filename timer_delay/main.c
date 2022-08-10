#include "stm32f10x.h"
#include "printtt.c"


void TIM3_IRQHandler(void);
void dUm(int mikros);
void dms(int ms);

int myTicks=0;
int main(){
	
	// clock enable
	RCC ->APB1ENR |=RCC_APB1ENR_TIM3EN;
	TIM3->ARR=144; // desired freq 1Mhz -- 72Mhz/1Mhz*2 =144
	TIM3->PSC=0;
	TIM3-> CR1 |=TIM_CR1_URS;
	TIM3 ->DIER |=TIM_DIER_UIE;
	TIM3->CR1 |=TIM_EGR_UG;
	
	NVIC_EnableIRQ(TIM3_IRQn);
	
	while (1)
	{
		
		printMsg("hello \n");
		
		dUm(2000);
		
	}
}

void TIM3_IRQHandler(void){
	/*if(TIM3->SR& TIM_SR_UIF){
	myTicks++; }  if we dont know if an interrupt happened; */
	
	myTicks++; // when interrupts happens variable will increment
	TIM3->SR &=TIM_SR_UIF; // clears the flag which is set after interrupt happened
	
}

void dUm(int mikros){
	
	TIM3->CR1 |=TIM_CR1_CEN;
	myTicks=0;
	while(myTicks<mikros); }

	void dms(int ms){
		TIM3->CR1 |=TIM_CR1_CEN;
	myTicks=0;
	while(myTicks<(ms*1000));
	}
	
	
	
	

