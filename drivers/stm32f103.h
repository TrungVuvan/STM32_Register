#ifndef STM32F103_H_
#define STM32F103_H_

#include <stdint.h>

#define ENABLE                  1
#define DISABLE                 0
#define SET                     ENABLE
#define RESET                   DISABLE
#define GPIO_PIN_SET            SET
#define GPIO_PIN_RESET          RESET
#define __vo                    volatile

/* base address of Flash and SRAM memories */

#define FLASH_BASEADDR          0x08000000U
#define SRAM1_BASEADDR          0x20000000U
//#define SRAM2_BASEADDR
//#define ROM_BASEADDR
#define SRAM                    SRAM1_BASEADDR

/* AHB and APBx Bus Peripheral base address */
#define NVIC_BASEADDR           	0xE000E100
#define PERIPH_BASEADDR             0x40000000U
#define APB1PERIPH_BASEADDR         PERIPH_BASE
#define APB2PERIPH_BASEADDR         0x40010000U
#define AHBPERIPH_BASEADDR          0x40018000U

/* base address of peripheral which are hanging on APB1 bus */

#define TIM2_BASEADDR           (APB1PERIPH_BASEADDR + 0x0000)
#define TIM3_BASEADDR           (APB1PERIPH_BASEADDR + 0x0400)
#define TIM4_BASEADDR           (APB1PERIPH_BASEADDR + 0x0800)
#define TIM5_BASEADDR           (APB1PERIPH_BASEADDR + 0x0C00)
#define TIM6_BASEADDR           (APB1PERIPH_BASEADDR + 0x1000)
#define TIM7_BASEADDR           (APB1PERIPH_BASEADDR + 0x1400)
#define TIM12_BASEADDR          (APB1PERIPH_BASEADDR + 0x1800)
#define TIM13_BASEADDR          (APB1PERIPH_BASEADDR + 0x1C00)
#define TIM14_BASEADDR          (APB1PERIPH_BASEADDR + 0x2000)
#define RTC_BASEADDR            (APB1PERIPH_BASEADDR + 0x2800)
#define WWDG_BASEADDR           (APB1PERIPH_BASEADDR + 0x2C00)
#define IWDG_BASEADDR           (APB1PERIPH_BASEADDR + 0x3000)
#define SPI2_BASEADDR           (APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR           (APB1PERIPH_BASEADDR + 0x3C00)
#define USART2_BASEADDR         (APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR         (APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR          (APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR          (APB1PERIPH_BASEADDR + 0x5000)
#define I2C1_BASEADDR           (APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR           (APB1PERIPH_BASEADDR + 0x5800)
#define USB_FS_BASEADDR         (APB1PERIPH_BASEADDR + 0x5C00)
#define bxCAN1_BASEADDR         (APB1PERIPH_BASEADDR + 0x6400)
#define bxCAN2_BASEADDR         (APB1PERIPH_BASEADDR + 0x6800)
#define BKP_BASEADDR            (APB1PERIPH_BASEADDR + 0x6C00)
#define PWR_BASEADDR            (APB1PERIPH_BASEADDR + 0x7000)
#define DAC_BASEADDR            (APB1PERIPH_BASEADDR + 0x7400)

/* BASEADDRaddress of peripheral which are hanging on APB2 bus */

#define AFIO_BASEADDR           (APB2PERIPH_BASEADDR + 0x0000)
#define EXTI_BASEADDR           (APB2PERIPH_BASEADDR + 0x0400)
#define GPIOA_BASEADDR          (APB2PERIPH_BASEADDR + 0x0800)
#define GPIOB_BASEADDR          (APB2PERIPH_BASEADDR + 0x0C00)
#define GPIOC_BASEADDR          (APB2PERIPH_BASEADDR + 0x1000)
#define ADC1_BASEADDR           (APB2PERIPH_BASEADDR + 0x2400)
#define ADC2_BASEADDR           (APB2PERIPH_BASEADDR+ 0x2800)
#define TIM1_BASEADDR           (APB2PERIPH_BASEADDR+ 0x2C00)
#define SPI1_BASEADDR           (APB2PERIPH_BASEADDR+ 0x3000)
#define TIM8_BASEADDR           (APB2PERIPH_BASEADDR+ 0x3400)
#define USART1_BASEADDR         (APB2PERIPH_BASEADDR+ 0x3800)
#define ADC3_BASEADDR           (APB2PERIPH_BASEADDR+ 0x3C00)
#define TIM9_BASEADDR           (APB2PERIPH_BASEADDR+ 0x4C00)
#define TIM10_BASEADDR          (APB2PERIPH_BASEADDR+ 0x5000)
#define TIM11_BASEADDR          (APB2PERIPH_BASEADDR+ 0x5400)

/* base address of peripheral which are hanging on AHB bus */

#define SDIO_BASEADDR           (AHBPERIPH_BASEADDR+ 0x0000)
#define DMA1_BASEADDR           (AHBPERIPH_BASEADDR+ 0x8000)
#define DMA2_BASEADDR           (AHBPERIPH_BASEADDR+ 0x8400)
#define RCC_BASEADDR            (AHBPERIPH_BASEADDR+ 0x9000)
#define CRC_BASEADDR            (AHBPERIPH_BASEADDR+ 0xB000)
#define Ethernet_BASEADDR       (AHBPERIPH_BASEADDR+ 0x10000)
#define USB_OTD_FS_BASEADDR     (AHBPERIPH_BASEADDR+ 0x0FFE8000)
#define FSMC_BASEADDR           (AHBPERIPH_BASEADDR+ 0x5FFE8000)

                            /* PERIPHERAL STRUCTURE */

                                /* GPIO structure */
typedef struct 
{
    __vo uint32_t CRL;
    __vo uint32_t CRH;
    __vo uint32_t IDR;
    __vo uint32_t ODR;
    __vo uint32_t BSRR;
    __vo uint32_t BRR;
    __vo uint32_t LCKR;
}GPIO_RegDef_t;

								/* GPIO structure */
typedef struct
{
	__vo uint32_t EVCR;
	__vo uint32_t MAPR;
	__vo uint32_t EXTICR[4];
	__vo uint32_t MAPR2;
}AFIO_RegDef_t;
                                /* RCC structure */
typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t APB1RSTR;
	__vo uint32_t AHBENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t APB1ENR;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
}RCC_RegDef_t;
								/* RCC structure */
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;

typedef struct
{
	__vo uint32_t ISER[2];
	uint32_t RESERVE0[29];
	__vo uint32_t ICER[2];
	uint32_t RESERVE1[29];
	__vo uint32_t ISPR[2];
	uint32_t RESERVE2[29];
	__vo uint32_t ICPR[2];
	uint32_t RESERVE3[29];
	__vo uint32_t IABR[2];
	uint32_t RESERVE4[61];
	__vo uint8_t IPR[84];
	uint32_t RESERVE5[695];
	__vo uint32_t STIR;
}NVIC_RegDef_t;

//////////////////////////////////////////////////////////////////////////////////
                                /* peripheral definitions */
//////////////////////////////////////////////////////////////////////////////////

								/* GPIO definitions */
GPIO_RegDef_t * GPIOA = (GPIO_RegDef_t *)GPIOA_BASEADDR;
GPIO_RegDef_t * GPIOB = (GPIO_RegDef_t *)GPIOB_BASEADDR;
GPIO_RegDef_t * GPIOC = (GPIO_RegDef_t *)GPIOC_BASEADDR;

AFIO_RegDef_t * AFIO = (AFIO_RegDef_t *)AFIO_BASEADDR;

								/* RCC definitions */
EXTI_RegDef_t * EXTI = (EXTI_RegDef_t *)EXTI_BASEADDR;

                                /* RCC definitions */
RCC_RegDef_t * RCC = (RCC_RegDef_t *)RCC_BASEADDR;

								/* NVIC definitions */
NVIC_RegDef_t * NVIC = (NVIC_RegDef_t *)NVIC_BASEADDR;

#endif
