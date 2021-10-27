#include "stm32f103_spi.h"

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
				pSPIx ->CR1 |= (1 << 6);
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
				pSPIx ->CR1 &= ~(1 << 6);
    }
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	// first let's configure the CR1 register
	uint32_t temp = 0;
	// 1. configure the device mode
	temp |= pSPIHandle ->SPIConfig.SPI_DeviceMode << 2;
	// 2. configure the bus config
	if(pSPIHandle ->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// bidi mode should be cleared
		temp &= ~(1 << 15);
	}
	else if(pSPIHandle ->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		// bidi mode should be set
		temp |= (1 << 15);
	}
	else if(pSPIHandle ->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_RXONLY)
	{
		// bidi mode should be cleared
		temp &= ~(1 << 15);
		// RXONLY bit must be set
		temp |= (1 << 10);
	}
	
	// 3. confiugre the spi serial clock speed (baud rate)
	temp |= pSPIHandle ->SPIConfig.SPI_SclkSpeed << 3;
	// 4. configure the DFF
	temp |= pSPIHandle ->SPIConfig.SPI_DFF << 11;
	// 5. configure the CPOL
	temp |= pSPIHandle ->SPIConfig.SPI_CPOL << 1;
	// 6. configure the CPHA
	temp |= pSPIHandle ->SPIConfig.SPI_CPHA << 0;
	// 7. configure the SSM
	temp |= pSPIHandle ->SPIConfig.SPI_SSM << 9;
	
	pSPIHandle ->pSPIx ->CR1 |= temp;
}

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t TxBuffer[], uint32_t Length)
{
	uint32_t i = 0;
	while(i < Length)
	{
		// wait for the TXE flag is set
		while(!(pSPIx ->SR & (1 << 1)));
		if(pSPIx ->CR1 & (1 << 11))
		{
			// 16 bit DFF
			// 1. load data into the DR
			pSPIx ->DR = (uint16_t)((TxBuffer[i] << 8) | TxBuffer[i + 1]);
			i += 2;
		}
		else
		{
			// 8 bit DFF
			// 1. load data into the DR
			pSPIx ->DR = (uint8_t)(TxBuffer[i]);
			i += 1;
		}
	}
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Length)
{
	uint32_t i = 0;
	while(i < Length)
	{
		// wait for the RXNE flag is set
		while(!(pSPIx ->SR & (1 << 0)));
		if(pSPIx ->CR1 & (1 << 11))
		{
			// 16 bit DFF
			// 1. load data from DR to Rxbuffer address
			*((uint16_t *)(pRxBuffer)) = pSPIx ->DR;
			Length -= 2;
			(uint16_t *)pRxBuffer ++;
		}
		else
		{
			// 8 bit DFF
			// 1. load data from DR to Rxbuffer address
			*(pRxBuffer) = pSPIx ->DR;
			Length --;
			pRxBuffer ++;
		}
	}
}

void SPI_IT_Enable(uint8_t IRQNumber, uint8_t EnorDi)
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

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t TxBuffer[], uint32_t Length)
{
	uint8_t state = pSPIHandle ->TxState;
	if(state != SPI_BUSY_IN_TX)
	{
		//1. save the Tx buffer address and Length information in some global variables
		pSPIHandle ->pTxBuffer = &TxBuffer[0];
		pSPIHandle ->TxLen = Length;
		//2. mark the SPI state as busy in transmission so that
		// no other code can take over same SPI peripheral until transmission is over
		pSPIHandle ->TxState = SPI_BUSY_IN_TX;
		//3. enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle ->pSPIx ->CR2 |= (1 << 7);
	}
	
	return state;
}
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Length)
{
	uint8_t state = pSPIHandle ->RxState;
	if(state != SPI_BUSY_IN_RX)
	{
		//1. save the Rx buffer address and Length information in some global variables
		pSPIHandle ->pRxBuffer = pRxBuffer;
		pSPIHandle ->RxLen = Length;
		//2. mark the SPI state as busy in transmission so that
		// no other code can take over same SPI peripheral until transmission is over
		pSPIHandle ->RxState = SPI_BUSY_IN_RX;
		//3. enable the RXNEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle ->pSPIx ->CR2 |= (1 << 6);
	}
	
	return state;
}

void SPI_IT_PriConfig(uint8_t IRQNumber, uint8_t SPIPri, uint8_t SPISubPri)
{
	NVIC ->IPR[IRQNumber / 4] |= ((uint8_t)(SPIPri << 4 | SPISubPri)) << (IRQNumber % 4);
}
/*
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
	uint8_t flag, flagIT;
	// first let's check for TXE
	flag = pSPIHandle ->pSPIx ->SR & (1 << 1);
	flagIT = pSPIHandle ->pSPIx ->CR2 & (1 << 7);
	if(flag && flagIT)
	{
		SPI1_TXE_Interrupt_Handle();
	}
	
	// check for RXNE
	flag = pSPIHandle ->pSPIx ->SR & (1 << 0);
	flagIT = pSPIHandle ->pSPIx ->CR2 & (1 << 6);
	if(flag && flagIT)
	{
		SPI1_RXNE_Interrupt_Handle();
	}
	
	// check for OVR Error
		flag = pSPIHandle ->pSPIx ->SR & (1 << 6);
	flagIT = pSPIHandle ->pSPIx ->CR2 & (1 << 5);
	if(flag && flagIT)
	{
		SPI1_OVREr_Interrupt_Handle();
	}
	
}
*/
