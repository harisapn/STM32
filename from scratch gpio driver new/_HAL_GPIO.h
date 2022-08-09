#include <stm32f10x.h>
#ifndef _HAL_GPIO
#define _HAL_GPIO





/*PORT names */

#define PORTA GPIOA
#define PORTB GPIOB
#define PORTC GPIOC
#define PORTD GPIOD
#define PORTE GPIOE
#define PORTF GPIOF
#define PORTG GPIOG


/******** pinModes********/

#define INPUT_MODE ((uint32_t) 0x01)
#define OUTPUT_MODE ((uint32_t) 0x02)

/*****input mode types ***/

#define INPUT_ANALOG ((uint32_t) 0x01)
#define INPUT_FLOAT  ((uint32_t) 0x02)
#define INPUT_PU_PD   ((uint32_t) 0x03)

/******output mode types*****/

#define OUTPUT_GEN_PUSH_PULL  ((uint32_t) 0x01)
#define OUTPUT_GEN_OD       ((uint32_t) 0x02)
#define OUTPUT_ALT_FUNC_PUSH_PULL ((uint32_t) 0x03)
#define OUTPUT_ALT_FUN_OD       ((uint32_t) 0x04)

/******* speed ******/

#define speed_10mhz  ((uint32_t) 0x01)
#define speed_2mhz    ((uint32_t) 0x02)
#define speed_50mhz    ((uint32_t) 0x03)

/***** clock enable *******/

#define GPIO_CLOCK_ENABLE_ALT_FUN  (RCC ->APB2ENR |= (1<<0))
#define GPIO_CLOCK_ENABLE_PORTA  (RCC ->APB2ENR |= (1<<2))
#define GPIO_CLOCK_ENABLE_PORTB  (RCC ->APB2ENR |= (1<<3))
#define GPIO_CLOCK_ENABLE_PORTC  (RCC ->APB2ENR |= (1<<4))
#define GPIO_CLOCK_ENABLE_PORTD  (RCC ->APB2ENR |= (1<<5))
#define GPIO_CLOCK_ENABLE_PORTE  (RCC ->APB2ENR |= (1<<6))

/***** high bit position for CRH registe, CNF and MODE ****/

/******* Define high bit position for  CRH register, CNF and MODE ****/

extern uint32_t PINPOS[];

#define CNF_POS_BIT1  (PINPOS[pinNumber]+2)
#define CNF_POS_BIT2   (PINPOS[pinNumber]+4)

/********configuration structure ******/

typedef struct {
	
	GPIO_TypeDef *port;
	uint32_t pin;
	uint32_t mode;
	uint32_t mode_type;
	uint32_t pull;
	uint32_t speed;
	uint32_t alt_func;
} GPIO_TYPE;

/****** function prototypes******/
/*** gpio configuration ****/

static void config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type);
	
static void config_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinspeed, uint32_t mode);

void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t state);

void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber);

void gpio_init(GPIO_TYPE gpio_type);
	
















#endif




