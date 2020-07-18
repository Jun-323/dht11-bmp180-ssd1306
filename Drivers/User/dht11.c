#include "dht11.h"


void delay_us(uint16_t us)
{
	uint8_t i;
	while(us--)
	{
		i = 4;
		while(i--);
	}
}

void dht11_gpio_input(void)
{
//    GPIO_InitTypeDef g;
//    
//    g.Pin = DHT11_GPIO_PIN;
//    g.Speed = GPIO_Speed_50MHz;
//    g.Mode = GPIO_Mode_IN_FLOATING; //????
//    
//    GPIO_Init(DHT11_GPIO_TYPE, &g);
}

void dht11_gpio_output(void)
{
//    GPIO_InitTypeDef g;
//    
//    g.GPIO_Pin = DHT11_GPIO_PIN;
//    g.GPIO_Speed = GPIO_Speed_50MHz;
//    g.GPIO_Mode = GPIO_Mode_Out_PP; //????

//    GPIO_Init(DHT11_GPIO_TYPE, &g);
}

void dht11_reset(void)
{
    // ??DHT11????
    dht11_gpio_output();
    DHT11_OUT_L;
    delay_us(19000);
    DHT11_OUT_H;
    delay_us(30);
    dht11_gpio_input();
}

uint16_t dht11_scan(void)
{
    return DHT11_IN;
}

uint16_t dht11_read_bit(void)
{
    while (DHT11_IN == RESET);
    delay_us(40);
    if (DHT11_IN == SET)
    {
        while (DHT11_IN == SET);
        return 1;
    }
    else
    {
        return 0;
    }
}

uint16_t dht11_read_byte(void)
{
    uint16_t i;
    uint16_t data = 0;
    for (i = 0; i < 8; i++)
    {
        data <<= 1;
        data |= dht11_read_bit();
    }
    return data;
}

uint16_t dht11_read_data(uint8_t buffer[5])
{
    uint16_t i = 0;
    
    dht11_reset();
    if (dht11_scan() == RESET)
    {
        //???DHT11??
        while (dht11_scan() == RESET);
        while (dht11_scan() == SET);
        for (i = 0; i < 5; i++)
        {
            buffer[i] = dht11_read_byte();
        }
        
        while (dht11_scan() == RESET);
        dht11_gpio_output();
        DHT11_OUT_H;
        
        uint8_t checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
        if (checksum != buffer[4])
        {
            // checksum error
            return 1;
        }
    }
    
    return 0;
}

