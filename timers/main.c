#include "printMsg.h"
#include "stm32f10x.h"

int main(){
	
	RCC->APB2ENR |=RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN |RCC_APB2ENR_USART1EN;
	
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;

	
	
GPIOB-> CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1; //confgure pin as 10 - output pull -push at 50MHz
	 GPIOB -> CRH &= ~(GPIO_CRH_CNF9_0); // need to set first bit to zero, because reset state is 01
	
	//setting baund rate
	 USART1->BRR = 0x1d4c; // 72 MHz dived by (9600 x 16)
	 USART1 ->CR1 |=USART_CR1_TE; // transmission enable
	 USART1 -> CR1 |=USART_CR1_UE; // usart enable
	
	TIM3 ->PSC = 65535;
	TIM3->ARR= 6000;
	TIM3 -> CR1 |= TIM_CR1_CEN;
	
	
	print_config_Type printer;
	printer.Tx_port=GPIOA;
	printer.tx_pinNumber=9;
	printer.Uart_instances=USART1;
	
	printMsg_init(printer);
	
	printMsg("UART connection established /n");
	while (1)
	{
		
		printMsg(" %d", TIM3->CNT); 
	}
	
	
}
