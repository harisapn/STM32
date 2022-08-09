 /* printMsg.h */

#define _PRINTMSG_H
#include <stdio.h>
#include <stdarg.h>

#define USART1  USART1
 
 void printMSg(char *msg,...);
 
 void printMSg(char *msg,...){
		 
		 char buff[80];
		 
		 
		 va_list args;
		 va_start(args,msg);
		 vsprintf(buff, msg,args); // variable arguments in buffer
			
			
		 
		 for(int i=0; i<(strlen(buff)); i++){
			 
			 USART1->DR =buff[i];
			 while(!(USART1->SR & USART_SR_TXE));}
		 }
			 
			
		