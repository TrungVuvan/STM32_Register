#ifndef STM32F103_SPI_H_
#define STM32F103_SPI_H_


#include "stm32f103.h"

typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;

typedef struct
{
	SPI_RegDef_t * pSPIx;
	SPI_Config_t SPIConfig;
}SPI_Handle_t;


/* SPI DEVICE MODE */
#define SPI_MODE_MASTER				1
#define SPI_MODE_SLAVE				0

/* SPI BUS CONFIG */
#define SPI_BUS_CONFIG_FD				1   //FULL DUPLEX
#define SPI_BUS_CONFIG_HD				2   //HALF DUPLEX
#define SPI_BUS_CONFIG_RXONLY		3	


															/* Template Function */
void SPI_PeriCLKControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_Init_IT(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);
void SPI_SendData(SPI_RegDef_t *pSPIx, uint16_t *pTxBuffer, uint32_t Length);
uint16_t SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint16_t *pRxBuffer, uint32_t Length);
void SPI_IT_Enable(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IT_PriConfig(uint8_t IRQNumber, uint8_t SPIPri, uint8_t SPISubPri);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

															/* Detail Function */

void SPI_PeriCLKControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pSPIx == SPI1)
        {
            RCC->APB2ENR |= (1 << 12);
        }
        else if (pSPIx == SPI2)
        {
            RCC->APB1ENR |= (1 << 14);
        }
        else if (pSPIx == SPI3)
        {
            RCC->APB1ENR |= (1 << 15);
        }
    }
    else
    {
        if (pSPIx == SPI1)
        {
            RCC->APB2ENR &= ~(1 << 12);
        }
        else if (pSPIx == SPI2)
        {
            RCC->APB1ENR &= ~(1 << 14);
        }
        else if (pSPIx == SPI3)
        {
            RCC->APB1ENR &= ~(1 << 15);
        }
    }
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	
	

#endif