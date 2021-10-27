#include "stm32f103_gpio.h"
#include "stm32f103_spi.h"
#include <string.h>
void Delay_Timer2_Config(void);
void delay_ms(uint32_t time);
void SPI_GPIOConfig();
/* 
		SPI1
* PA4 - NSS
	PA5 - SCK
	PA6 - MISO
	PA7 - MOSI
*/

int main(void)
{
	char data[] = "From SEEE-HUST with love";
	
	SPI_Handle_t pSPI1;
	
	pSPI1.pSPIx = SPI1;
	pSPI1.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	pSPI1.SPIConfig.SPI_DeviceMode = 1;
	pSPI1.SPIConfig.SPI_SclkSpeed = SPI_SPEED_DIV_64;
	pSPI1.SPIConfig.SPI_DFF = 0;
	pSPI1.SPIConfig.SPI_CPHA = 0;
	pSPI1.SPIConfig.SPI_CPOL = 0;
	pSPI1.SPIConfig.SPI_SSM = 1;
	
	SPI_GPIOConfig();
	SPI_PeriCLKControl(SPI1, ENABLE);
	SPI_Init(&pSPI1);
	SPI_SendData(SPI1, data, strlen(data));
	Delay_Timer2_Config();
  while(1)
  {
				
  }
  return 0;
}

void Delay_Timer2_Config(void)
{
	RCC ->APB1ENR |= (1 << 0);    // enable clock for timer2
	TIM2 ->ARR = 0xFFFF;      // TIMx auto-reload register TIMx_ARR
	TIM2 ->PSC = 72 - 1;      // PSC[15:0]: prescaler value
	TIM2 ->CR1 = 0x01;        // bit 0 CEN: counter enable and 0: counter used as upcounter
	TIM2 ->EGR = 0x01;        // generate an update event to reload the Prescaler and repetition counter value immediately
}

void delay_ms(uint32_t time)
{
	while(time)
	{
		TIM2 ->CNT = 0U;
		while((TIM2 ->CNT) < 1000);
		time--;
	}
}

void SPI_GPIOConfig()
{
	GPIO_PeriCLKControl(GPIOA, ENABLE);
	GPIO_PinConfig_t SPIpin;
	GPIO_Handle_t pSPI;
	
	SPIpin.GPIO_PinMode = 3;
	SPIpin.GPIO_PinCNF = 2;
	pSPI.pGPIOx = GPIOA;
	pSPI.GPIO_PinConfig = SPIpin;
	//NSS
	pSPI.GPIO_PinConfig.GPIO_PinNumber = 4;
	GPIO_Init(&pSPI);
	//SCK
	pSPI.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_Init(&pSPI);
	//MISO
	pSPI.GPIO_PinConfig.GPIO_PinNumber = 6;
	GPIO_Init(&pSPI);
	//MOSI
	pSPI.GPIO_PinConfig.GPIO_PinNumber = 7;
	GPIO_Init(&pSPI);
}
