#include "_HAL_GPIO.c"
#include <stdio.h>


int main(){
	
	
	GPIO_TYPE mojulaz;
	mojulaz.port=GPIOA;
	mojulaz.pin=9;
	mojulaz.mode=INPUT_MODE;
	mojulaz.mode_type=INPUT_ANALOG;
	
	mojulaz.speed=50;
	
	config_init(mojulaz);
}

	
	
