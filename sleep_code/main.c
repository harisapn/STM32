#include "stm32f10x.h"
#include "printMsg.h"

void gotosleep(void);

int main(){
	
	
	if((PWR->CR)&(PWR_CSR_SBF)) {
		
		PWR->CR |=PWR_CR_CWUF;
		PWR->CR |=PWR_CR_CSBF;
		
		printMSg("I have awaken from standby mode");
		
	}
	
	else{
		printMSg("I have awaken from power cycle");}
	
		
	
	while(1){
		
		gotosleep();
	}
	






}


void gotosleep(void){
	
	RCC->APB1ENR |=RCC_APB1ENR_PWREN;
	SCB->SCR |=SCB_SCR_SLEEPDEEP_Msk;
	PWR->CR |=PWR_CR_PDDS;
	PWR->CR |=PWR_CR_CWUF;
	PWR->CSR |=PWR_CSR_EWUP;
 __WFI();
	
}

	
	
	
	