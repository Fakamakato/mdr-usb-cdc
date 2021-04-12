/**
  ******************************************************************************
  * @file    main.c
  * @author  zns
  * @version V0.1.0
  * @date    11/04/2021
  * @brief   Main program body.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, ZNS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2021 ZNS</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32Fx.h"
#include "service.h"
#include "spi.h"
#include "queue.h"
#include "usb_setup.h"
#include "usb_handlers.h"
#include "MDR32F9Qx_usb_handlers.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

  static uint32_t led_delay = 0;
	static uint32_t data_exchange_delay = 0;
	static uint8_t q_spi_buf[Q_SIZE];
	static uint8_t q_usb_buf[Q_SIZE];
	
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
	queue_t q_usb = {.front = 0, .itemCount = 0, .rear = 0, .queue = q_usb_buf};
	queue_t q_spi = {.front = 0, .itemCount = 0, .rear = 0, .queue = q_spi_buf};
	extern uint32_t uwTick;
/* Main function - initialization and empty infinite loop */
#ifdef __CC_ARM
int main(void)
#else
#ifdef __CC_ARM
int main(void)
#else
int main(void)
#endif
#endif
{	
  periphInit();  
  /* Main loop */
  while (1)
  {

    if (led_delay < uwTick)
    {
      MDR_PORTB->RXTX ^= 1 << 7 ;
      led_delay = uwTick + 500;
    }
		if(data_exchange_delay < uwTick)
		{
			data_exchange_delay = uwTick + 10;
			
			if(!qIsEmpty(&q_spi))
			{
				spi1Send(qRetrieve(&q_spi));
			}
			
			if(!qIsEmpty(&q_usb))
			{
				usbPush( qRetrieve(&q_usb));
			}
			
			if(!isUsbTxEmpty())
			{	
				USB_CDC_DataSent();
			}
			
		}
		
		
		  
  }
}

/**
  * @brief  Reports the source file ID, the source line number
  *         and expression text (if USE_ASSERT_INFO == 2) where
  *         the assert_param error has occurred.
  * @param  file_id: pointer to the source file name
  * @param  line: assert_param error line source number
  * @param  expr:
  * @retval None
  */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint32_t file_id, uint32_t line)
{
  /* User can add his own implementation to report the source file ID and line number.
     Ex: printf("Wrong parameters value: file Id %d on line %d\r\n", file_id, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint32_t file_id, uint32_t line, const uint8_t *expr);
{
  /* User can add his own implementation to report the source file ID, line number and
     expression text.
     Ex: printf("Wrong parameters value (%s): file Id %d on line %d\r\n", expr, file_id, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_ASSERT_INFO */

/*
* END OF FILE main.c */
