/**
  ******************************************************************************
  * @file    spi.c
  * @author  ZNS
  * @version V1.0.0
  * @date    10-April-2021
  * @brief   This file provides HAL for spi hardware.
  *          
  *  
*/

/* Includes ------------------------------------------------------------------*/
#include "spi.h"
#include "MDR32F9Qx_ssp.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Global functions ---------------------------------------------------------*/

/**
 * @brief initialize spi1 hardware
 * @param 
 * @return (void)
 */
void spi1Init(void)
{
	SSP_InitTypeDef SPIinitStr;

	SSP_DeInit(MDR_SSP1);

	SSP_StructInit(&SPIinitStr);

	SSP_BRGInit(MDR_SSP1, SSP_HCLKdiv8);

	SPIinitStr.SSP_Mode = SSP_ModeMaster;
	SPIinitStr.SSP_WordLength = SSP_WordLength8b;
	SPIinitStr.SSP_SPH = SSP_SPH_2Edge;
	SPIinitStr.SSP_SPO = SSP_SPO_Low;
	SPIinitStr.SSP_FRF = SSP_FRF_SPI_Motorola;
	SPIinitStr.SSP_CPSDVSR = 2;
	SPIinitStr.SSP_SCR = 0xA0;
	SPIinitStr.SSP_HardwareFlowControl = SSP_HardwareFlowControl_SSE;
	SSP_Init(MDR_SSP1, &SPIinitStr);

	NVIC_EnableIRQ(SSP1_IRQn);
	SSP_ITConfig(MDR_SSP1, SSP_IT_RT, ENABLE);

	SSP_Cmd(MDR_SSP1, ENABLE);
}

/**
 * @brief initialize spi2 harware
 * @param 
 * @return (void)
 */
void spi2Init(void)
{
	SSP_InitTypeDef SPIinitStr;
	SSP_DeInit(MDR_SSP2);

	SSP_StructInit(&SPIinitStr);

	SSP_BRGInit(MDR_SSP2, SSP_HCLKdiv8);

	SPIinitStr.SSP_Mode = SSP_ModeSlave;
	SPIinitStr.SSP_WordLength = SSP_WordLength8b;
	SPIinitStr.SSP_SPH = SSP_SPH_2Edge;
	SPIinitStr.SSP_SPO = SSP_SPO_Low;
	SPIinitStr.SSP_FRF = SSP_FRF_SPI_Motorola;
	SPIinitStr.SSP_CPSDVSR = 2;
	SPIinitStr.SSP_SCR = 0x0A;
	SPIinitStr.SSP_HardwareFlowControl = SSP_HardwareFlowControl_SSE;
	SSP_Init(MDR_SSP2, &SPIinitStr);

	NVIC_EnableIRQ(SSP2_IRQn);
	SSP_ITConfig(MDR_SSP2, SSP_IT_RT, ENABLE);

	SSP_Cmd(MDR_SSP2, ENABLE);
}

/**
 * @brief send data via spi1 in blocking mode
 * @param data	byte of data to be sent
 * @return (void)
 */
void spi1Send(uint8_t data)
{
	while (SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_TFE) == RESET)
	{
	}
	MDR_PORTF->RXTX &= ~(1 << 2);
	MDR_SSP1->DR = (data++);
}
