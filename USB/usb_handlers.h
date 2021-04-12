/**
  ******************************************************************************
  * @file    usb_handlers.h
  * @author  zns
  * @version V1.0.0
  * @date    11-April-2021
  * @brief   This file contains prototypes for usb API
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USB_HANDLERS_H_
#define _USB_HANDLERS_H_


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Exported functions ---------------------------------------------------------*/
void usbPush(uint8_t data);
bool isUsbTxEmpty(void);
#endif
