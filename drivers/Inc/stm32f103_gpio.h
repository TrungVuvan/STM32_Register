#ifndef INC_STM32F103_GPIO_H_
#define INC_STM32F103_GPIO_H_

#include "stm32f103.h"



// GPIO_RegDef_t
typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinCNF;
    uint8_t GPIO_ITMode;
} GPIO_PinConfig_t;

#define INPUT_MODE              0
#define OUTPUT_MODE_MS_10MHZ   	1
#define OUTPUT_MODE_MS_2MHZ     2
#define OUTPUT_MODE_MS_50MHZ    3
#define IT_MODE_FT							0
#define IT_MODE_RT							1

//GPIO_Handle_t
typedef struct
{
    GPIO_RegDef_t *pGPIOx;
    GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

void GPIO_PeriCLKControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_Init_EXTI(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

void GPIO_EXTI_Enable(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_EXTI_PriConfig(uint8_t IRQNumber, uint8_t EXTIPri, uint8_t EXTISubPri);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif

