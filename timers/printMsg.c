#include <stdio.h>
#include "printMsg.h"
#include <stdarg.h>
#include "stm32f10x.h"
#include <stdlib.h>
#include <string.h>




void printMsg(char *msg,...){
	
	char buff[80];

		 
		 va_list args;
		 va_start(args,msg);
		 vsprintf(buff, msg,args); // variable arguments in buffer
			
			
		 
		 for(uint32_t i=0; i<(strlen(buff)); i++){
			 
			 USART1->DR =buff[i];
			 while(!(USART1->SR & USART_SR_TXE));}
		 }
			 
			 	
		 static void config_Type(GPIO_TypeDef *tx_port, uint32_t tx_pinNumber){
	
	if(tx_pinNumber<8){
		
		switch(tx_pinNumber){
			
			case 0:
				tx_port ->CRL|= GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1;
			tx_port -> CRL &=~(GPIO_CRL_CNF0_0); break;
			
			case 1:
				tx_port ->CRL|= GPIO_CRL_CNF1_1 | GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1;
			tx_port -> CRL &=~(GPIO_CRL_CNF1_0); break;
			
			case 2:
				
			tx_port ->CRL|= GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1;
			tx_port -> CRL &=~(GPIO_CRL_CNF2_0); break;
			
			case 3:
				tx_port ->CRL|= GPIO_CRL_CNF3_1 | GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1;
			tx_port -> CRL &=~(GPIO_CRL_CNF3_0); break;
			
			case 4:
				tx_port ->CRL|= GPIO_CRL_CNF4_1 | GPIO_CRL_MODE4_0 | GPIO_CRL_MODE4_1;
			tx_port -> CRL &=~(GPIO_CRL_CNF4_0); break;
			
			case 5:
				tx_port ->CRL|= GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1;
			tx_port -> CRL &=~(GPIO_CRL_CNF5_0); break;
			
			case 6:
				tx_port ->CRL|= GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1;
			tx_port -> CRL &=~(GPIO_CRL_CNF6_0); break;
			
			case 7:
				tx_port ->CRL|= GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1;
			tx_port -> CRL &=~(GPIO_CRL_CNF6_0); break;
		}}
		
		else {
			
			switch(tx_pinNumber){ 
				
	case 8:
				tx_port ->CRH|= GPIO_CRH_CNF8_0 | GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1;
			tx_port -> CRH &=~(GPIO_CRH_CNF8_0); break;
			
			case 9:
				tx_port ->CRH|= GPIO_CRH_CNF9_0 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1;
			tx_port -> CRH &=~(GPIO_CRH_CNF9_0); break;
			
			case 10:
				
			tx_port ->CRH|= GPIO_CRH_CNF10_0 | GPIO_CRH_MODE10_0 | GPIO_CRH_MODE10_1;
			tx_port -> CRH &=~(GPIO_CRH_CNF10_0); break;
			
			case 11:
				tx_port ->CRH|= GPIO_CRH_CNF11_0 | GPIO_CRH_MODE11_0 | GPIO_CRH_MODE11_1;
			tx_port -> CRH &=~(GPIO_CRH_CNF11_0); break;
			
			case 12:
				tx_port ->CRH|= GPIO_CRH_CNF12_0 | GPIO_CRH_MODE12_0 | GPIO_CRH_MODE12_1;
			tx_port -> CRH &=~(GPIO_CRH_CNF12_0); break;
			
			case 13:
				tx_port ->CRH|= GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1;
			tx_port -> CRH &=~(GPIO_CRH_CNF13_0); break;
			
			case 14:
				tx_port ->CRH|= GPIO_CRH_CNF14_0 | GPIO_CRH_MODE14_0 | GPIO_CRH_MODE14_1;
			tx_port -> CRH &=~(GPIO_CRH_CNF14_0); break;
			
			case 15:
				tx_port ->CRH|= GPIO_CRH_CNF15_0 | GPIO_CRH_MODE15_0 | GPIO_CRH_MODE15_1;
			tx_port -> CRH &=~(GPIO_CRH_CNF15_0); break;
		}
	
	}}

	static void config_usart(USART_TypeDef *Uart_instances){
		
	Uart_instances ->BRR = 0x1d4c; // 72 MHz dived by (9600 x 16)
	 Uart_instances ->CR1 |=USART_CR1_TE; // transmission enable
	 Uart_instances -> CR1 |=USART_CR1_UE; // usart enable
		
	}
	
	static void printMsg_init(print_config_Type  mytype) {
		
	config_Type(mytype.Tx_port,mytype.tx_pinNumber);
		config_usart(mytype.Uart_instances);}
	

		 