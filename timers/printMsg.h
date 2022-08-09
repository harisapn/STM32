#include <stdio.h>

#include "stm32f10x.h"

#ifndef print_Msg
#define print_Msg


void printMsg(char *msg,...);

typedef struct {
	
	GPIO_TypeDef *Tx_port;
	uint32_t tx_pinNumber;
	USART_TypeDef *Uart_instances;
} print_config_Type ;

static void config_Type(GPIO_TypeDef *tx_port, uint32_t tx_pinNumber);

static void config_usart(USART_TypeDef *Uart_instances);

static void printMsg_init(print_config_Type  mytype);

#endif 
	
