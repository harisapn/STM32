#include "stm32f10x.h"
#include "printtt.h"
#include <stdarg.h>
#include <stdio.h>


void printMsg(char *msg,...){
	
	char buff[80];

		 
		 va_list args;
		 va_start(args,msg);
		 vsprintf(buff, msg,args); // variable arguments in buffer
			
			
		 
		 for(uint32_t i=0; i<(strlen(buff)); i++){
			 
			 USART1->DR =buff[i];
			 while(!(USART1->SR & USART_SR_TXE));}
		 }
			 