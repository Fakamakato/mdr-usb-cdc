/**
  ******************************************************************************
  * @file    PORT_InitStructure.c
  * @author  ZNS
  * @version V1.0.0
  * @date    10-April-2021
  * @brief   This file provides HAL for PORT_InitStructure hardware.
  *          
  *  
*/

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_bkp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Global functions ---------------------------------------------------------*/

/**
 * @brief Initialize PORT_InitStructure for your needs
 * @return (void)
 */

void gpioInit(void)
{
  PORT_InitTypeDef PORT_InitStructure;

  PORT_InitStructure.PORT_Pin = PORT_Pin_7;
  PORT_InitStructure.PORT_OE = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

  PORT_Init(MDR_PORTB, &PORT_InitStructure);

  //SSP1 pins

  PORT_InitStructure.PORT_FUNC = PORT_FUNC_ALTER;
  PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;
  PORT_InitStructure.PORT_Pin = (PORT_Pin_0 | PORT_Pin_1);
  PORT_InitStructure.PORT_OE = PORT_OE_OUT;
  PORT_Init(MDR_PORTF, &PORT_InitStructure);
	
	//Manual FSS control
  PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_Pin = (PORT_Pin_2);
  PORT_Init(MDR_PORTF, &PORT_InitStructure);
	MDR_PORTF->RXTX = 1 << 2; //FSS inactive

  //SSP2 pins

  PORT_InitStructure.PORT_FUNC = PORT_FUNC_OVERRID;
  PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_PD = PORT_PD_DRIVER;
  PORT_InitStructure.PORT_PD_SHM = PORT_PD_SHM_OFF;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
  PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
  PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
  PORT_InitStructure.PORT_GFEN = PORT_GFEN_OFF;

  PORT_InitStructure.PORT_Pin = PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2;
  PORT_InitStructure.PORT_OE = PORT_OE_IN;
  PORT_Init(MDR_PORTC, &PORT_InitStructure);

  /* Configure PORTB pin 0  (UART1_TX) as output */
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_OVERRID;
  PORT_InitStructure.PORT_OE = PORT_OE_OUT;
  PORT_InitStructure.PORT_Pin = PORT_Pin_0;
  PORT_Init(MDR_PORTB, &PORT_InitStructure);

  /* Configure PORTB pins 1 (UART1_RX) as input */
  //PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_ON;
  PORT_InitStructure.PORT_OE = PORT_OE_IN;
  PORT_InitStructure.PORT_Pin = PORT_Pin_1;
  PORT_Init(MDR_PORTB, &PORT_InitStructure);
}
