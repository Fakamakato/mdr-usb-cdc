/**
  ******************************************************************************
  * @file    usb_handlers.c
  * @author  zns
  * @version V1.0.0
  * @date    11-April-2021
  * @brief   This file contains prototypes for usb API
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_usb_handlers.h"
#include "usb_handlers.h"
#include "queue.h"
#define BUFFER_LENGTH        64
#define BUF_MASK 						(BUFFER_LENGTH-1)

/* Private variables ---------------------------------------------------------*/
 
static uint8_t idxIN = 0;
static uint8_t idxOUT = 0;
static volatile uint32_t PendingDataLength;
static uint8_t usb_tx_buf[BUFFER_LENGTH];


/**
 * @brief user receive handler for usb-cdc
 * @param Buffer  pointer to a buffer that contains data
 * @param Length  buffer length
 * @return status (USB_SUCCESS or USB_ERROR)
 */
USB_Result USB_CDC_RecieveData(uint8_t* Buffer, uint32_t Length)
{

	extern queue_t q_spi;

  /* Send back received data portion */
  //result = USB_CDC_SendData(Buffer, Length);
	
	while(Length--)
		qInsert(&q_spi,*(Buffer++));
	
  return USB_SUCCESS;
}




/**
 * @brief user transmit handler for usb-cdc
 * @param 
 * @return status (USB_SUCCESS or USB_ERROR)
 */
USB_Result USB_CDC_DataSent(void)
{
  USB_Result result = USB_SUCCESS;
	PendingDataLength = (idxIN - idxOUT)&BUF_MASK;
  if (PendingDataLength)
  {
    result = USB_CDC_SendData(usb_tx_buf, PendingDataLength);

    PendingDataLength = 0;
		idxIN = 0;  //assume that all data was sent
		idxOUT = 0;
    USB_CDC_ReceiveStart();
  }
  return USB_SUCCESS;
}

/**
 * @brief pushes data to usb transmit buffer
 * @param data  one byte of data
 * @return (void)
 */
void usbPush(uint8_t data)
{
	usb_tx_buf[idxIN++] = data;
	idxIN &= BUF_MASK;
}

/**
 * @brief checks if the transmit buffer is empty and there is nothing to send
 * @param 
 * @return true == empty\ false == not empty
 */
bool isUsbTxEmpty(void)
{
	return ((idxIN - idxOUT)&BUF_MASK) == 0;
}


