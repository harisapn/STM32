/* ###### INCLUDES ############## */

#include "stm32f10x.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

 /* ########### Var/ Defines ######### */
 
 #define DEBUG_UART     USART1 
 #define delay        for(int i=0; i<=500000;i++);
 int x=0;
 
 /* #########  Prototypes ########### */
 
 static void printMSg(char *msg, ...);
 
                
               
 int main (){
	  /* enabling alternate function, and usart1, and configuring port*/
	 RCC->APB2ENR |=RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN;
	 GPIOA-> CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1; //confgure pin as 10 - output pull -push at 50MHz
	 GPIOA -> CRH &= ~(GPIO_CRH_CNF9_0); // need to set first bit to zero, because reset state is 01
	 
	 
	 //setting baund rate
	 USART1->BRR = 0x1d4c; // 72 MHz dived by (9600 x 16)
	 USART1 ->CR1 |=USART_CR1_TE; // transmission enable
	 USART1 -> CR1 |=USART_CR1_UE; // usart enable
	 
	 while(1)
	 {
		 
		 printMSg("Hello I am %d years old", 65);
delay
		 
	 //x++;
		// if(x==20) x=0;
 }
	 }
 
  
	  static void printMSg(char *msg,...){
		 
		 char buff[80];
		 #ifdef DEBUG_UART
		 
		 va_list args;
		 va_start(args,msg);
		 vsprintf(buff, msg,args); // variable arguments in buffer
			
			
		 
		 for(int i=0; i<(strlen(buff)); i++){
			 
			 USART1->DR =buff[i];
			 while(!(USART1->SR & USART_SR_TXE));}
		 }
			 
			 #endif
		 