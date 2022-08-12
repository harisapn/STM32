#include "stm32f10x.h"
#include "stdint.h"

//global 
#define bufflen 20
// i2C states
#define I2C_WRITING 0x05
#define I2C_READING 0x08
#define I2C_INTERRUPTED 0x09
#define I2C_FREE 0x07
#define I2C_BUSY 0x10
#define EEPROM_ADDRESS 0x1010000;

void i2c_init(void);
void i2c_write(uint8_t device_address, uint8_t mem_address, uint8_t data);
void i2c_read(uint8_t device_address, uint8_t len);
void delayMS(int ms);
uint32_t msTicks=0;
uint16_t buffcount=0;

uint8_t i2c_buff[bufflen];


uint8_t buff[bufflen];



void SysTick_Handler(void);
int temp;


int main(){
	SysTick_Config(SystemCoreClock/1000);
	i2c_init();
	int x=0;
	while(1){
		
		if(!(GPIOA->IDR & GPIO_IDR_IDR2)){ // check if button is pressed
			
			if (x>0){}
		else {
			
			i2c_write(EEPROM_ADDRESS,0x04,0x60);
			delayMS(2);
			i2c_write(EEPROM_ADDRESS,0x05,0x61);
			delayMS(2);
		i2c_write(EEPROM_ADDRESS,0x06,0x62);
			delayMS(2);
		i2c_write(EEPROM_ADDRESS,0x07,0x63);
			delayMS(2);
		i2c_read(EEPROM_ADDRESS, 4)	
			
			x++;
	}
	
	
	
	
	
	
} } }

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
			
	
	void i2c_read(uint8_t device_address, uint8_t len){
		
		temp=0;
		
		i2c_buff[0]=0x00;
		
		RCC->APB1ENR|=RCC_AHBENR_DMA1EN; //enable DMa
		I2C1->CR2 |=I2C_CR2_DMAEN;
		
		I2C1->CR1 |=I2C_CR1_ACK; //enable ACK bit
		DMA1_Channel5->CMAR =(uint32_t)i2c_buff; // take the address of buff -memory
		DMA1_Channel5->CPAR=(uint32_t)&I2C1->DR; // take the address of data register
		DMA1_Channel5->CNDTR=len; // givwe the length of data to be transmitted
		
		DMA1_Channel5->CCR |= DMA_CCR1_MINC | DMA_CCR1_TCIE | DMA_CCR1_EN; //memory incremen mode, tTC interrupt, 
		
		I2C1->CR1 |=I2C_CR1_START; // start bit
		while(!(I2C1->SR1 & I2C_SR1_SB)){} // check strat bit
		
		I2C1->DR = device_address +1 ; // adding one because of reading
			
			while(!(I2C1->SR1 & I2C_SR1_ADDR))
			{}
				
			temp=I2C1->SR2;
			
				while(!(DMA1->ISR & DMA_ISR_TCIF5)){
				}
				
				I2C1->CR1 |=I2C_CR1_STOP;
				
			}
			
		
		
		
		
		
			
		
		
		
		
	
	