/**
  ******************************************************************************
  * @file    service.c
  * @author  ZNS
  * @version V1.0.0
  * @date    10-April-2021
  * @brief   This file provides unites different libraries for better code organization.
  *          
  *  
*/

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_bkp.h"
#include "service.h"
#include "gpio.h"
#include "spi.h"
#include "uart.h"
#include "usb_setup.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void periphClcInit(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief initialize all peripheral clocks
 * @param 
 * @return (void)
 */
static void periphClcInit(void)
{
	  RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_SSP2 | RST_CLK_PCLK_SSP1),ENABLE);
		RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTF | RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD), ENABLE);
		RST_CLK_PCLKcmd( (RST_CLK_PCLK_UART1 |RST_CLK_PCLK_UART2 |RST_CLK_PCLK_BKP), ENABLE);
		RST_CLK_PCLKcmd(RST_CLK_PCLK_USB,ENABLE);
}

/* Global functions ---------------------------------------------------------*/


/**
 * @brief initialize all peripheral units
 * @param 
 * @return (void)
 */
void periphInit(void)
{
	  /* Init NVIC */
  SCB->AIRCR = 0x05FA0000 | ((uint32_t)0x500);
  SCB->VTOR = 0x08000000;
  /* Disable all interrupt */
  NVIC->ICPR[0] = 0xFFFFFFFF;
  NVIC->ICER[0] = 0xFFFFFFFF;
  periphClcInit();
	BKP_JTAGA_CMD(DISABLE);
  gpioInit();
	//uart1Init();
	//uart2Init();
	spi1Init();
	spi2Init();	
	
	vcomConfig();
	sysClockInit();
	setupUSB();
	SysTick_Config(SystemCoreClock / 1000);
}


/**
 * @brief initialize sys clock to 80 MHz
 * @param 
 * @return (void)
 */
void sysClockInit(void)
{
	__disable_irq();
  // HSE on
  RST_CLK_HSEconfig (RST_CLK_HSE_ON); 
  while (RST_CLK_HSEstatus () != SUCCESS);

  // Tune PLL (CPU_C1_SEL = HSE / 1 * 10 =  8MHz / 1 * 10 = 80MHz)
  RST_CLK_CPU_PLLconfig (RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul10); 
 
  // Enable pll
  RST_CLK_CPU_PLLcmd (ENABLE); 
  while (RST_CLK_CPU_PLLstatus () != SUCCESS);

  // Tune §³3 ( CPU_C3_SEL = CPU_C2_SEL )
  RST_CLK_CPUclkPrescaler (RST_CLK_CPUclkDIV1); 
  
  // §³2 = PLL
  RST_CLK_CPU_PLLuse (ENABLE); 
  
  // CPU C3 (HCLK_SEL = CPU_C3_SEL = 80MHz)
  RST_CLK_CPUclkSelection (RST_CLK_CPUclkCPU_C3); 
	SystemCoreClockUpdate();
	__enable_irq();
}


