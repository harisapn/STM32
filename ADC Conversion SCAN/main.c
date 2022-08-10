 
#include "stm32f10x.h"



 /******** Defines Variable ***************/
 
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
	
	//enable DMA on AHBENR
	
	RCC->AHBENR |=RCC_AHBENR_DMA1EN;
	// RCC clocks for ADC1 and ALT functions GPIOA
	
	RCC->APB2ENR |=RCC_APB2ENR_ADC1EN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;
	
	//set port as input push pull, pin 5 and 7
	GPIOA ->CRL |=GPIO_CRL_CNF5_1;
	GPIOA ->CRL &=~(GPIO_CRL_CNF5_0);
	GPIOA ->CRL |=GPIO_CRL_CNF7_1;
	GPIOA ->CRL &=~(GPIO_CRL_CNF7_0);
	
	
	// no need for interrupt DMA will be doing everything
	
	// set the sampling rate, highest 111 in SMP5 --channel 5 register SMPR2
	
	ADC1->SMPR2 |=ADC_SMPR2_SMP5_2 | ADC_SMPR2_SMP5_1 | ADC_SMPR2_SMP5_0;
	ADC1->SMPR2 |=ADC_SMPR2_SMP7_2 | ADC_SMPR2_SMP7_1 | ADC_SMPR2_SMP7_0;
	
	
	//define the lenght of conversions -two conversions, L bit to 0001
ADC1 ->SQR1 |= ADC_SQR1_L_0;

	
	//sequence register, set the sequance of channel conversion. First is channel 5 in SQ1, second is channel 7 in SQ2
	
	ADC1 ->SQR3 |= ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_2;
	ADC1 ->SQR3 |= ADC_SQR3_SQ2_0 | ADC_SQR3_SQ2_2 | ADC_SQR3_SQ2_1; // 7<<5
	
	//enable SCAN in ADC 
	
	ADC1->CR1|=ADC_CR1_SCAN;
	
	//enable DMA in CR2
	
	ADC1->CR2 |=ADC_CR2_DMA;
	
	// DMA settings in CPAR,CMAR, CNTD,CCR
	
	// take the peripheral adress register to DMA Channel 1 -- pass the Data register of ADC1
	
	DMA1_Channel1 ->CPAR = (uint32_t)(&(ADC1->DR));  // takes the adress of data register
	
	// where to pass it
	
	uint16_t samples[2]={0,0};
	
	DMA1_Channel1 ->CMAR=(uint32_t)samples;
	
	// how many transfers is it going to do
	
	DMA1_Channel1->CNDTR=2;
	
	// circular mode, peripheral size 01 16-bit, memory size 01 16-bit, memory increment mode
	DMA1_Channel1 ->CCR |=DMA_CCR1_CIRC | DMA_CCR1_MINC | DMA_CCR1_MSIZE_0 | DMA_CCR1_PSIZE_0;
	DMA1_Channel1 ->CCR |= DMA_CCR1_EN;
	
	
	 
	
	
	//enable the ADC for the first time and set it to cont mode
	
	ADC1 -> CR2 |=ADC_CR2_ADON | ADC_CR2_CONT;
	
	delayMs(1);
	
	ADC1->CR2 |= ADC_CR2_ADON;
	
	delayMs(1);
	
	ADC1 ->CR2 |=ADC_CR2_CAL;
	
	delayMs(1);
	
	
	while(1){
		
		printMsg("ADC1 at Channel[5] is %d  and Channel[7] is %d",samples[0],samples[1]);
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
