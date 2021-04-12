/**
  ******************************************************************************
  * @file    uart.c
  * @author  zns
  * @version V1.0.0
  * @date    10-April-2021
  * @brief   This file contains functions for uart management.
  ******************************************************************************
  *@warning remember thar clocks and gpio initialization must be performed in 
  * separate file
*/

/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "MDR32F9Qx_uart.h"


/**
 * @brief initalize uart1 hardware
 * @param 
 * @return (void)
 */
void uart1Init(void)
{
	UART_InitTypeDef UART_InitStructure;
	UART_StructInit(&UART_InitStructure);
	
  UART_BRGInit(MDR_UART1, UART_HCLKdiv1);

  UART_InitStructure.UART_BaudRate             = 115200;              
  UART_InitStructure.UART_WordLength           = UART_WordLength8b;   
  UART_InitStructure.UART_StopBits             = UART_StopBits2;      
  UART_InitStructure.UART_Parity               = UART_Parity_No;      
  UART_InitStructure.UART_FIFOMode             = UART_FIFO_OFF;

  /* Configure UART1 parameters*/
  UART_Init(MDR_UART1, &UART_InitStructure);
	
  /* Enables UART1 peripheral */
  UART_Cmd(MDR_UART1, ENABLE);
}

/**
 * @brief initalize uart2 hardware
 * @param 
 * @return (void)
 */
void uart2Init(void)
{
	UART_InitTypeDef UART_InitStructure;
	UART_StructInit(&UART_InitStructure);
	
  UART_BRGInit(MDR_UART2, UART_HCLKdiv1);

  UART_InitStructure.UART_BaudRate             = 115200;              
  UART_InitStructure.UART_WordLength           = UART_WordLength8b;   
  UART_InitStructure.UART_StopBits             = UART_StopBits2;      
  UART_InitStructure.UART_Parity               = UART_Parity_No;      
  UART_InitStructure.UART_FIFOMode             = UART_FIFO_OFF;       

  /* Configure UART2 parameters*/
  UART_Init(MDR_UART2, &UART_InitStructure);
	
	UART_ITConfig (MDR_UART2, UART_IT_RX, ENABLE);
  
  NVIC_EnableIRQ (UART2_IRQn); 		

  /* Enables UART2 peripheral */
  UART_Cmd(MDR_UART2, ENABLE);
}
