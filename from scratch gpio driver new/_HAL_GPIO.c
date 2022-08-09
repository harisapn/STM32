#include "stm32f10x.h"
#include "_HAL_GPIO.h"
#include <stdint.h>



uint32_t PINPOS[16]={
	(0x00), // CRL pin 0
	(0x04),  //CRL pin 1
	(0x08),
	(0x0C),
	(0x10),
	(0x14),
	(0x18),
	(0x1C),
	(0x00), // CRH pin 0
	(0x04),  // CRH pin 1
	(0x08),
	(0x0C),
	(0x10),
	(0x14),
	(0x18),
	(0x1C)} ;
	
	static void config_pin(GPIO_TypeDef *port,uint32_t pinNumber, uint32_t mode_type){
		
		if(pinNumber>8){
		
		switch(mode_type){
			
			case INPUT_ANALOG | OUTPUT_GEN_PUSH_PULL:
				port ->CRH  &=~((1<<CNF_POS_BIT1)|(1<<CNF_POS_BIT2)); break;
			
			case INPUT_FLOAT | OUTPUT_GEN_OD :
				
			port -> CRH &= ~(1<<CNF_POS_BIT2);
			port->CRH |=(1<<CNF_POS_BIT2); break;
			
			case INPUT_PU_PD | OUTPUT_ALT_FUNC_PUSH_PULL:
				
			port -> CRH &= ~(1<<CNF_POS_BIT1);
			port->CRH |=(1<<CNF_POS_BIT2); break;
			
			case OUTPUT_ALT_FUN_OD:
				port -> CRH |=(1<<CNF_POS_BIT1);
			port -> CRH |= (1<<CNF_POS_BIT2); break;
			
			
		}
	}
		
	else {
		switch(mode_type){
			
			case INPUT_ANALOG | OUTPUT_GEN_PUSH_PULL:
				port ->CRL  &=~((1<<CNF_POS_BIT1)|(1<<CNF_POS_BIT2)); break;
			
			case INPUT_FLOAT | OUTPUT_GEN_OD :
				
			port -> CRL &= ~(1<<CNF_POS_BIT2);
			port->CRL |=(1<<CNF_POS_BIT2); break;
			
			case INPUT_PU_PD | OUTPUT_ALT_FUNC_PUSH_PULL:
				
			port -> CRL &= ~(1<<CNF_POS_BIT1);
			port->CRL |=(1<<CNF_POS_BIT2); break;
			
			case OUTPUT_ALT_FUN_OD:
				port -> CRL |=(1<<CNF_POS_BIT1);
			port -> CRL |= (1<<CNF_POS_BIT2); break;
		}}
	
	}
	
	static void config_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinspeed, uint32_t mode){
		
		if(pinNumber>=8){
			if (mode==INPUT_MODE){
				port ->CRH &=~((1<<PINPOS[pinNumber]) | (1<<PINPOS[pinNumber+1]));
				
			}
			
			else {
				port ->CRH |=(pinspeed<<PINPOS[pinNumber]); } }
		
				if(pinNumber<8){
			if (mode==INPUT_MODE){
				port ->CRL &=~((1<<PINPOS[pinNumber]) | (1<<PINPOS[pinNumber+1]));
				
			}
			
			else {
				port ->CRL |=(pinspeed<<PINPOS[pinNumber]); } }
				
				
			}
	
			void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t state) {
				
				if (state){
					port ->BSRR = 1<<pinNumber;
				}
				else{
					port->BSRR = 1<<(pinNumber+16);}
				
				}
			
				
		void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber) {
			
			port ->ODR ^= 1<<pinNumber;
		}
		
		void gpio_init(GPIO_TYPE gpio_type){
			
			if(gpio_type.port==PORTA) GPIO_CLOCK_ENABLE_PORTA; 
			if(gpio_type.port==PORTB) GPIO_CLOCK_ENABLE_PORTB;
			
			if(gpio_type.port==PORTC) GPIO_CLOCK_ENABLE_PORTC;
			if(gpio_type.port==PORTD) GPIO_CLOCK_ENABLE_PORTD;
			if(gpio_type.port==PORTE) GPIO_CLOCK_ENABLE_PORTE; 
			
			config_pin(gpio_type.port, gpio_type.pin, gpio_type.mode_type);
			config_speed(gpio_type.port, gpio_type.pin,gpio_type.speed,gpio_type.mode);
		}
		
		
			
				
		
				
		
				
			
		
		
			
			
			
			
		