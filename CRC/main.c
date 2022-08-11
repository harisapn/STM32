#include "stm32f10x.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


 int msTicks;
void delayMs(int ms);
 void printMsg(char *msg,...);
 
 
 void crc_init(void);
 
 
int main (void)
{
 /****************************| NON CRC CODE |*********************
 SysTick_Config(SystemCoreClock / 1000);
 printMsg_config_Type printer;
 printer.TX_pinNumber = 9;
 printer.Uart_instance = USART1;
 printer.tx_port = GPIOA;
 printMsg_init(printer);
 *****************************************************************/
 
	
	
// array data for CRC 
 uint8_t dummy_byte = 0xC1;
 uint8_t dummy_array[4] = { 0x41, 0x20, 0xff, 0x10 };


 //pin Rx and Tx configuration
 RCC->APB2ENR |=RCC_APB2ENR_AFIOEN|RCC_APB2ENR_IOPAEN|RCC_APB2ENR_USART1EN ;
 GPIOA ->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;
 GPIOA -> CRH &=~(GPIO_CRH_CNF9_0);
 
 
 while(1)
 {

  // Put 1 byte through CRC, print the CRC code , reset calculation
  CRC->CR = 1;
  CRC->DR = dummy_byte;
  printMsg("%x \n", CRC->DR);
  
  delayMs(500);

  //Put 4 bytes through CRC one by one, get the CRC code at end  
  uint8_t i;
  CRC->CR = 1;
  for (i = 0; i < 4; i++) {
   CRC->DR = dummy_array[i];
  }
  printMsg("%x \n", CRC->DR);

  delayMs(500);

  //Put 4 bytes in the 32bit Data register all at once, get CRC code   
  uint32_t all_bytes = 0x00000000;

  for (i = 3; i >= 1; i--) {
   all_bytes |= dummy_array[i] << (8 * i);
  }
  all_bytes |= dummy_array[0];
  CRC->DR = all_bytes;
  
  printMsg("%x \n", CRC->DR);
  
  delayMs(500);
 }
 
}

void crc_init(void) {

 RCC->AHBENR |= RCC_AHBENR_CRCEN;  // enable clock for CRC
 CRC->CR |= CRC_CR_RESET;   // Reset calculation
 
}

void printMsg(char *msg,...){
	
	char buff[80];

		 
		 va_list args;
		 va_start(args,msg);
		 vsprintf(buff, msg,args); // variable arguments in buffer
			
			
		 
		 for(uint32_t i=0; i<(strlen(buff)); i++){
			 
			 USART1->DR =buff[i];
			 while(!(USART1->SR & USART_SR_TXE));}
		 }
			 
		 
		 void SysTick_Handler(void){
			 msTicks++;
		 }
void delayMs(int ms){
	msTicks=0;
	while(msTicks<ms);}