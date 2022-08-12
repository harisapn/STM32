#include "stm32f10x.h"

void i2c_init();
void i2c_write(uint8_t device_address, uint8_t mem_address, uint8_t data);
void i2c_read();
void delayMS(int ms);
int msTicks=0;
void SysTick_Handler(void);
int temp;


int main(){
	SysTick_Config(SystemCoreClock/1000);
}

void i2c_init(){
	
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; //enable I2C1
	RCC->APB2ENR |=RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPBEN; //enable port for I2C, B port and alt func
	
	NVIC_EnableIRQ(I2C1_EV_IRQn); //enable interrupt line
	
	I2C1->CR2 |=36; // set the frequency for APB1
	
	/*  T=1/36mhz= 27.7 ns
	Now pick the frequency you want the I2C run at (100kHz). Get the period of that freq (1/100kHz= 10mikros). Then divide this by 2 to get Htime.
	*/
	
	I2C1->CCR = 180;
	I2C1 ->TRISE = 37; // 1000ns/(1/36Mhz)=36 and add 1
	
	I2C1->CR1 |= I2C_CR1_ACK; //enable acknowledge bit
	//stretch mode enabled by default
	//7 bit addressing by default
	
	// gpio stuffs, configuration
	//alt function will be output open drain, i2c1 is on B6 and B7, sCL and SDA
	
	GPIOB ->CRL |= GPIO_CRL_CNF6 |GPIO_CRL_MODE6 | GPIO_CRL_CNF7 |GPIO_CRL_MODE7;
	
	GPIOB->ODR |=GPIO_ODR_ODR6 | GPIO_ODR_ODR7 ;
	
	// enable corresponding interrupts - buffer interrupt and event interrupts
	
	I2C1->CR2 |=I2C_CR2_ITBUFEN | I2C_CR2_ITEVTEN;
	
	I2C1 -> CR1 |= I2C_CR1_PE; //enable peripheral
	
}

	
	
void delayMS(int ms){
	msTicks=0;
	while(msTicks<ms);}

void SysTick_Handler(void){
	msTicks++;}

	void i2c_write(uint8_t device_address, uint8_t mem_address, uint8_t data){
		
		I2C1->CR1 |=I2C_CR1_START; // send start bit
		
		while(!(I2C1->SR1 & I2C_SR1_SB)){  // check the flag of SB in status registar
		} 
		
		I2C1->DR = device_address; // transmit the chip address to data register
		
		while(!(I2C1->SR1 & I2C_SR1_ADDR)) { // check the flag in status register for ADDR -address match
			
		}
		
		temp = I2C1->SR2 ; // read the SR2, reading clears the flag in SR1 of ADDR
		
		I2C1->DR=mem_address; // read the internal address of device where data will be stored
		
			while(!(I2C1->SR1 & I2C_SR1_TXE)) { // check the flag in transfer bit TXE, wait for byte transfer complete
			
		}
			
		I2C1->DR=data; // send data to be transmitted
		while(!(I2C1->SR1 & I2C_SR1_TXE)) { // check the flag in transfer bit TXE, wait for byte transfer complete
			
		}
		
		I2C1->CR1 |= I2C_CR1_STOP; // generate the stop bit
		
		//if you wann send more then 1 byte just write the for loop
		
	}
			
		
			
		
		
		
		
	
	