#include "stm32f10x.h"
#include <stdint.h>

//------------------- |GLOBAL VAR| ---------------
uint32_t msTicks=0;


// -------------------|PROTOTYPES| ---------------
void setupDevice(void);
void setClockto32Mhz(void);
void delayMs(uint32_t ms);

void setupISP(void);
void spi_send(uint8_t data);

int main(){
	
	setupDevice();
	
	while(1){
		
	}
	
}


void setupDevice(){
	
	setClockto32Mhz();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
}

void delayMs(uint32_t ms){
	msTicks=0;
	while(msTicks<ms);}

	void SysTick_Handler(void){
		msTicks++; }
	
		
		
	void setupISP(void){
		
		// enable clocks and altrenate functions
		
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
		
		// configure pins as alternate functions push pull
		GPIOA->CRL |= GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1 |GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1;
		GPIOA->CRL &= ~(GPIO_CRL_CNF5_0);
		GPIOA->CRL &= ~(GPIO_CRL_CNF7_0);
		
		SPI1 ->CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_SSM |SPI_CR1_BR_1 |SPI_CR1_BR_0 | SPI_CR1_MSTR | SPI_CR1_CPHA | SPI_CR1_CPOL | SPI_CR1_BIDIOE;
		
	SPI1->CR2 |=SPI_CR2_SSOE;
		
		SPI1->CR1|=SPI_CR1_SPE;
	}
	
	void spi_send(uint8_t data){
		
		SPI1->DR=data;
		while(!(SPI1->SR & SPI_SR_TXE));
		
	}
		
		
		
		
		void setClockto32Mhz(){
			
			RCC->CR |= RCC_CR_HSEON; // turn on external crystal
			while(!(RCC->CR & RCC_CR_HSERDY)); // wait for HSE to be ready
			
			/*"The implementation of this prefetch buffer makes a faster CPU execution possible as the
CPU fetches one word at a time with the next word readily available in the prefetch buffer.
This implies that the acceleration ratio will be of the order of 2 assuming that the code is
aligned at a 64-bit boundary for the jumps.  */
			FLASH->ACR|=FLASH_ACR_PRFTBE;
			
			
				FLASH->ACR &= ~(FLASH_ACR_LATENCY); //add latency for 28Mhz
			FLASH->ACR |=FLASH_ACR_LATENCY_0;
			
			// configure RCC and PLL settigns while PLL is of
			// this is the heart of changing the clock
			
			RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC); //reset all bits
			
			// PLLMULL bit is PLL multiplier
			//PLLXTPRE bit is PREDIV1 (is it divided by 1 or 2), HSE clock
			//PLLSRC bit is for source, PREDIV1
			
			
			RCC->CFGR |= RCC_CFGR_PLLMULL7 | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC;
			
			//for peripherals
			
			//AHB not divided
			
			RCC->CFGR &= ~(RCC_CFGR_HPRE); //AHB not divided
			RCC->CFGR &= ~(RCC_CFGR_PPRE1); //APB1 not divided
			RCC-> CFGR &= ~(RCC_CFGR_PPRE2); // APB2 nor divided
			
			// turn on PLL and check if it is ready
			
			RCC->CR |= RCC_CR_PLLON;
			while(!(RCC->CR & RCC_CR_PLLRDY));
			
			// set PLL as system clock and check status SWS
			RCC->CFGR |=RCC_CFGR_SW_1;
			
			while(!(RCC->CFGR & RCC_CFGR_SWS_1)); 
			
			
			
			
			
			
	}
		