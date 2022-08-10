#include "stm32f10x.h"  // Device header


 //******** Defines Variable ***************/
 
int msTicks=0;
 
 int val=0;
 int val2=0;
 
 /********** Prototypes ******************/
 void initDebug(void);
 void delayMs(int ms);
  void ADC1_2_IRQHandler(void);
	void Systick_Handler(void);
	
;


int main(){
	
	SysTick_Config(SystemCoreClock/1000);
	
	// change prescalar for ADC not to exceed 14 Mhz in RCC CFGR register
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
	// RCC clocks for ADC1 and ALT functions GPIOA
	
	RCC->APB2ENR |=RCC_APB2ENR_ADC1EN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;
	
	//set port as input push pull
	GPIOA ->CRL |=GPIO_CRL_CNF5_1;
	GPIOA ->CRL &=~(GPIO_CRL_CNF5_0);
	
	//enable the conversion interrupt
	
	ADC1 ->CR1 =ADC_CR1_EOCIE;
	
	// enable that interrupt in NVIC
	NVIC_EnableIRQ(ADC1_2_IRQHandler);
	
	// set the sampling rate, highest 111 in SMP5 --channel 5 register SMPR2
	
	ADC1->SMPR2 |=ADC_SMPR2_SMP5_2 | ADC_SMPR2_SMP5_1 | ADC_SMPR2_SMP5_0;
	
	//sequence register, set the sequance of channel conversion
	
	ADC1 ->SQR3 |= ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_2;
	
	//enable the ADC for the first time and set it to cont mode
	
	ADC1 -> CR2 |=ADC_CR2_ADON | ADC_CR2_CONT;
	
	delayMs(1);
	
	ADC1->CR2 |= ADC_CR2_ADON;
	
	delayMs(1);
	
	ADC1 ->CR2 |=ADC_CR2_CAL;
	
	delayMs(1);
	
	
	while(1){
		
		printMsg("ADC1 at Channel[5] is: %d",val);
	}
}
	
	void ADC1_2_IRQHandler(void){ // check if we are here, if end of conversion flag is set
		
		if(ADC1->SR & ADC_SR_EOC) {
			
			val=ADC1 -> DR; // reading from Data register cleans the ADC_SR_EOC flag which is set by hardware
		}}
	
void delayMs(int ms){

msTicks=0;
	while(msTicks<ms);}
void Systick_Handler(void){
	msTicks++;}
	
	

float map(float FROM_MAX, float FROM_MIN, float TO_MAX, float TO_MIN, float VAL_TO_MAP){
	
	float MAPED_VAL=0;
	MAPED_VAL= ((VAL_TO_MAP -FROM_MIN)*((TO_MAX-TO_MIN)/(FROM_MAX-FROM_MIN))+TO_MIN);
	
	return MAPED_VAL;
	
}


	
	
	
	
	
	
	
	
	
	
	
	