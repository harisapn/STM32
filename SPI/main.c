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
	
		void setClockto32Mhz(){
			
		}
		
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
		
		
		
		
		
		