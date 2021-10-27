#ifndef INC_STM32F103_SPI_H_
#define INC_STM32F103_SPI_H_

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
	uint8_t *pTxBuffer;  // to store the app. Tx buffer address
	uint8_t *pRxBuffer;	// to store the app. Tx buffer address
	uint32_t TxLen;		// to store Tx length
	uint32_t RxLen;   // to store Rx length
	uint8_t TxState;  // to store Tx state
	uint8_t RxState;	// to store Rx state
}SPI_Handle_t;


/* SPI BUSY */
#define SPI_READY							0
#define SPI_BUSY_IN_RX				1
#define SPI_BUSY_IN_TX				2

/* SPI DEVICE MODE */
#define SPI_MODE_MASTER				1
#define SPI_MODE_SLAVE				0

/* SPI BUS CONFIG */
#define SPI_BUS_CONFIG_FD				1   //FULL DUPLEX
#define SPI_BUS_CONFIG_HD				2   //HALF DUPLEX
#define SPI_BUS_CONFIG_RXONLY		3	

/* SPI BAUD RATE */
#define SPI_SPEED_DIV_2					0
#define SPI_SPEED_DIV_4					1
#define SPI_SPEED_DIV_8					2
#define SPI_SPEED_DIV_16				3
#define SPI_SPEED_DIV_32				4
#define SPI_SPEED_DIV_64				5
#define SPI_SPEED_DIV_128				6
#define SPI_SPEED_DIV_256				7


															/* Template Function */
void SPI_PeriCLKControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_Init(SPI_Handle_t *pSPIHandle);
//void SPI_Init_IT(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t TxBuffer[], uint32_t Length);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Length);
void SPI_IT_Enable(uint8_t IRQNumber, uint8_t EnorDi);
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t TxBuffer[], uint32_t Length);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Length);
void SPI_IT_PriConfig(uint8_t IRQNumber, uint8_t SPIPri, uint8_t SPISubPri);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);
		
#endif
