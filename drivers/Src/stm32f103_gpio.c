#include "..\Inc\stm32f103_gpio.h"

/**************************************************************
 * @FN                - GPIO_PeriCLKControl
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
        //TODO
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
    // kiểm tra PinNumber
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 7)
    {
        // Chọn mode Input hoặc Output cho PinNumber
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber * 4));
        pGPIOHandle->pGPIOx->CRL |= temp;
        // Chọn trạng thái cho PinNumber
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinCNF << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber * 4 + 2));
        pGPIOHandle->pGPIOx->CRL |= temp;
    }
    else
    {
        // Chọn mode Input hoặc Output cho PinNumber
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber - 8) * 4));
        pGPIOHandle->pGPIOx->CRH |= temp;
        // Chọn trạng thái cho PinNumber
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinCNF << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber - 8) * 4 + 2));
        pGPIOHandle->pGPIOx->CRH |= temp;
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
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void mdelaym(void);

int main(void)
{
	GPIO_PinConfig_t a;
	GPIO_Handle_t gpioLed;
	a.GPIO_PinMode = 3;
	a.GPIO_PinNumber = 13;
	a.GPIO_PinCNF = 0;
	gpioLed.pGPIOx = GPIOC;
	gpioLed.GPIO_PinConfig = a;
	GPIO_PeriCLKControl(GPIOC, ENABLE);
	GPIO_Init(&gpioLed);
    while(1)
    {
    	GPIO_WriteToOutputPin(GPIOC, 13, 1);
    	mdelaym();
    	GPIO_WriteToOutputPin(GPIOC, 13, 0);
    	mdelaym();
    }
}

void mdelaym(void)
{
	for(int i = 0; i < 500; i++)
		for(int j = 0; j < 1000; j++)
		{

		}
}
