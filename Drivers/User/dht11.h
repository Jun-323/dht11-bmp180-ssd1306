#ifndef __DHT11_H__
#define __DHT11_H__

//#include "timer.h"
#include "stm32f0xx_hal.h"

#define DHT11_GPIO_TYPE  GPIOB
#define DHT11_GPIO_PIN   GPIO_PIN_12
#define DHT11_RCC        RCC_APB2Periph_GPIOB


#define DHT11_OUT_H  HAL_GPIO_WritePin(DHT11_GPIO_TYPE, DHT11_GPIO_PIN, 1)
#define DHT11_OUT_L  HAL_GPIO_WritePin(DHT11_GPIO_TYPE, DHT11_GPIO_PIN, 0)
#define DHT11_IN     HAL_GPIO_ReadPin(DHT11_GPIO_TYPE, DHT11_GPIO_PIN)


void delay_us(uint16_t us);
void dht11_gpio_input(void);
void dht11_gpio_output(void);
uint16_t dht11_scan(void);
uint16_t dht11_read_bit(void);
uint16_t dht11_read_byte(void);
uint16_t dht11_read_data(uint8_t buffer[4]);

#endif
