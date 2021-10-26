#include "stm32f103_gpio.h"
void mdelaym(void);
void EXTI0_IRQHandler(void);


int main(void)
{
	// khai bao bien
	GPIO_PinConfig_t pA, pC;
	GPIO_Handle_t led, it;
	
	pA.GPIO_ITMode = IT_MODE_FT; // ngat suon xuong
	pA.GPIO_PinNumber = 0;       // ngat line 0
	pA.GPIO_PinMode = 0;				 // mode input pullup/pulldown
	pA.GPIO_PinCNF = 2;
	it.GPIO_PinConfig = pA;
	it.pGPIOx = GPIOA;					 // chon chan A0 lam chan ngat
	GPIO_PeriCLKControl(GPIOA, ENABLE); // enable clock GPIOA
	GPIO_Init(&it);					//khoi tao GPIO
	GPIO_Init_IT(&it);			// khoi tao ngat ngoai
	GPIO_EXTI_Enable(6, ENABLE);		// enable ngat
	
	// configure pin PC13 as output, push/pull
	pC.GPIO_PinNumber = 13;
	pC.GPIO_PinMode = 3;
	pC.GPIO_PinCNF = 0;
	led.GPIO_PinConfig = pC;
	led.pGPIOx = GPIOC;
	GPIO_PeriCLKControl(GPIOC, ENABLE);
	GPIO_Init(&led);
	GPIO_WriteToOutputPin(GPIOC, 13, RESET);  // reset pin PC13
    while(1)
    {
				
    }
    return 0;
}

void mdelaym(void)
{
	for(int i = 0; i < 1000; i++)
		for(int j = 0; j < 1000; j++)
		{

		}
}

void EXTI0_IRQHandler(void)
{
	if(EXTI ->PR & (1 << 0))   
	{
		EXTI ->PR |= (1 << 0); // xoa co pending bang cach ghi 1 vao
		GPIOC ->ODR ^= 0xFFFF;
	}
}
