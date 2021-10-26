#include "..\drivers\stm32f103_gpio.h"

void GPIO_PeriCLKControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pGPIOx == GPIOA)
        {
            RCC->APB2ENR |= (1 << 2);
        }
        else if (pGPIOx == GPIOB)
        {
            RCC->APB2ENR |= (1 << 3);
        }
        else if (pGPIOx == GPIOC)
        {
            RCC->APB2ENR |= (1 << 4);
        }
    }
    else
    {
			if (pGPIOx == GPIOA)
        {
            RCC->APB2ENR &= ~(1 << 2);
        }
        else if (pGPIOx == GPIOB)
        {
            RCC->APB2ENR &= ~(1 << 3);
        }
        else if (pGPIOx == GPIOC)
        {
            RCC->APB2ENR &= ~(1 << 4);
        }
    }
}

/**************************************************************
 * @FN                - GPIO_Init
 *
 * @BRIEF             - enable or disable peripheral clock for the given GPIO port
 *
 * @FIRST PARAM       - base address of the gpio peripheral
 * @SECOND PARAM      - ENABLE OR DISABLE
 * @THIRD PARAM       -
 *
 * @RETURN            - NONE
 *
 * @NOTE              - NONE
 * */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp;
    // ki?m tra PinNumber
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 7)
    {
        // Ch?n mode Input ho?c Output cho PinNumber
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber * 4));
        pGPIOHandle->pGPIOx->CRL |= temp;
        // Ch?n tr?ng thái cho PinNumber
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinCNF << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber * 4 + 2));
        pGPIOHandle->pGPIOx->CRL |= temp;
    }
    else
    {
        // Ch?n mode Input ho?c Output cho PinNumber
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber - 8) * 4));
        pGPIOHandle->pGPIOx->CRH |= temp;
        // Ch?n tr?ng thái cho PinNumber
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinCNF << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber - 8) * 4 + 2));
        pGPIOHandle->pGPIOx->CRH |= temp;
    }
}

void GPIO_Init_IT(GPIO_Handle_t *pGPIOHandle) {
	// enable clk AFIO
	RCC->APB2ENR |= 0x01;
	// select EXTI line
	uint8_t pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	// tim STT thanh ghi can ghi vao
	uint8_t EXTICRi = pin / 4;
	// tim so bit can phai dich
	uint8_t bit = (pin - 4 * EXTICRi) * 4;
	if (pGPIOHandle->pGPIOx == GPIOA)
	{
		AFIO->EXTICR[EXTICRi + 1] |= (0x00 << bit);

	}
	else if (pGPIOHandle->pGPIOx == GPIOB)
	{
		AFIO->EXTICR[EXTICRi + 1] |= (0x01 << bit);
	}
	//interrupt request from line "pin" is not masked
	EXTI ->IMR |= (1 << pin);
	uint8_t mode = pGPIOHandle ->GPIO_PinConfig.GPIO_ITMode;
	if(mode == IT_MODE_FT)
	{
		// enable falling edge
		EXTI ->FTSR |= (1 << pin);
		// disable rising edge
		EXTI ->RTSR &= ~(1 << pin);
	}
	else if(mode == IT_MODE_RT)
	{
		// disable falling edge
		EXTI ->FTSR &= ~(1 << pin);
		// enable rising edge
		EXTI ->RTSR |= (1 << pin);
	}
}

/**************************************************************
 * @FN                - GPIO_DeInit
 *
 * @BRIEF             - enable or disable peripheral clock for the given GPIO port
 *
 * @FIRST PARAM       - base address of the gpio peripheral
 * @SECOND PARAM      - ENABLE OR DISABLE
 * @THIRD PARAM       -
 *
 * @RETURN            - NONE
 *
 * @NOTE              - NONE
 * */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    if (pGPIOx == GPIOA)
    {
        RCC->APB2RSTR |= (1 << 2);
        RCC->APB2RSTR &= ~(1 << 2);
    }
    else if (pGPIOx == GPIOB)
    {
        RCC->APB2RSTR |= (1 << 3);
        RCC->APB2RSTR &= ~(1 << 3);
    }
    else if (pGPIOx == GPIOC)
    {
        RCC->APB2RSTR |= (1 << 4);
        RCC->APB2RSTR &= ~(1 << 4);
    }
}
/**************************************************************
 * @FN                - GPIO_ReadFromInputPin
 *
 * @BRIEF             -
 *
 * @FIRST PARAM       -
 * @SECOND PARAM      -
 * @THIRD PARAM       -
 *
 * @RETURN            -0 or 1
 *
 * @NOTE              - NONE
 * */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;
    value = (uint8_t)((pGPIOx ->IDR >> PinNumber) & 0x01);
    return value;
}


uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    return (uint16_t)(pGPIOx ->IDR);
}


void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(Value == 0)
    {
        pGPIOx ->ODR &= ~(1 << PinNumber);
    }
    else
    {
        pGPIOx ->ODR |= (1 << PinNumber);
    }
}


void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
    pGPIOx ->ODR = (uint16_t)Value;
}


void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    pGPIOx ->ODR = pGPIOx ->ODR ^ (1 << PinNumber);
}


void GPIO_EXTI_Enable(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		// tim chi so cua mang thanh ghi ISER
		uint8_t ISERi = IRQNumber / 32;
		// tim so bit can phai dich
		uint8_t bit = IRQNumber % 32;
		NVIC ->ISER[ISERi] |= (1 << bit);
	}
	else
	{
		uint8_t ICERi = IRQNumber / 32;
		uint8_t bit = IRQNumber %32;
		NVIC ->ICER[ICERi] |= (1 << bit);
	}
}

void GPIO_EXTI_PriConfig(uint8_t IRQNumber, uint8_t EXTIPri, uint8_t EXTISubPri)
{
	NVIC ->IPR[IRQNumber / 4] |= ((uint8_t)(EXTIPri << 4 | EXTISubPri)) << (IRQNumber % 4);
}