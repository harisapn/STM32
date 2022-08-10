/* ###### INCLUDES ############## */

#include "stm32f10x.h"

#include "printMsg.h"



 /* ########### Var/ Defines ######### */
 
 #define DEBUG_UART     USART1 
 #define delay        for(int i=0; i<=500000;i++);
 
 
 /* #########  Prototypes ########### */
 

                
               
 int main (){
	  /* enabling alternate function, and usart1, and configuring port*/
	 /* RCC->APB2ENR |=RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN;
	 GPIOA-> CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1; //confgure pin as 10 - output pull -push at 50MHz
	 GPIOA -> CRH &= ~(GPIO_CRH_CNF9_0); // need to set first bit to zero, because reset state is 01
	 
	 
	 //setting baund rate
	 USART1->BRR = 0x1d4c; // 72 MHz dived by (9600 x 16)
	 USART1 ->CR1 |=USART_CR1_TE; // transmission enable
	 USART1 -> CR1 |=USART_CR1_UE; // usart enable */ 
	 
	 print_Msg_config_type mychoice;
	 mychoice.Tx_port=GPIOA;
	 mychoice.Tx_pinNumber=9;
	 mychoice.Uart_instances =USART1;
	print_init(mychoice);
	 
	 while(1)
	 {
		 
		 printMSg("Hello I am %d years old", 65);
delay
		 
	 //x++;
		// if(x==20) x=0;
 }
	 }
 
  
	  
		 