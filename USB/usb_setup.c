/**
  ******************************************************************************
  * @file    usb_setup.c
  * @author  zns
  * @version V1.0.0
  * @date    11-April-2021
  * @brief   This file contains prototypes for usb setup routine
  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "MDR32Fx.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32F9Qx_rst_clk.h"
#include "usb_setup.h"
/* USB tx\rx buffer length */
#define BUFFER_LENGTH 64

#ifdef USB_DEBUG_PROTO

#define USB_DEBUG_NUM_PACKETS   100

typedef struct {
  USB_SetupPacket_TypeDef packet;
  uint32_t address;
} TDebugInfo;

static TDebugInfo SetupPackets[USB_DEBUG_NUM_PACKETS];
static uint32_t SPIndex;

#endif /* USB_DEBUG_PROTO */
/* Private variables ---------------------------------------------------------*/
static USB_CDC_LineCoding_TypeDef LineCoding;
static uint8_t usb_rx_buf[BUFFER_LENGTH];

/**
 * @brief basic usb setup including clock configuration
 * @param 
 * @return (void)
 */
void setupUSB(void)
{
  /* Enables the CPU_CLK clock on USB */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_USB, ENABLE);
	USB_Clock_TypeDef USB_Clock_InitStruct;
	USB_DeviceBUSParam_TypeDef USB_DeviceBUSParam;
  /* Device layer initialization */
  USB_Clock_InitStruct.USB_USBC1_Source = USB_C1HSEdiv2;
  USB_Clock_InitStruct.USB_PLLUSBMUL    = USB_PLLUSBMUL12;

  USB_DeviceBUSParam.MODE  = USB_SC_SCFSP_Full;
  USB_DeviceBUSParam.SPEED = USB_SC_SCFSR_12Mb;
  USB_DeviceBUSParam.PULL  = USB_HSCR_DP_PULLUP_Set;

  USB_DeviceInit(&USB_Clock_InitStruct, &USB_DeviceBUSParam);

  /* Enable all USB interrupts */
  USB_SetSIM(USB_SIS_Msk);

  USB_DevicePowerOn();

  /* Enable interrupt on USB */
#ifdef USB_INT_HANDLE_REQUIRED
  NVIC_EnableIRQ(USB_IRQn);
#endif /* USB_INT_HANDLE_REQUIRED */

  USB_DEVICE_HANDLE_RESET;
}



/**
 * @brief virtual com port initialization
 * @param 
 * @return (void)
 */
void vcomConfig(void)
{
	

#ifdef USB_CDC_LINE_CODING_SUPPORTED
  LineCoding.dwDTERate = 115200;
  LineCoding.bCharFormat = 0;
  LineCoding.bParityType = 0;
  LineCoding.bDataBits = 8;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */
	
	USB_CDC_Init((uint8_t *)usb_rx_buf, 1, SET);
}

#ifdef USB_CDC_LINE_CODING_SUPPORTED

/* USB_CDC_HANDLE_GET_LINE_CODING implementation example */
USB_Result USB_CDC_GetLineCoding(uint16_t wINDEX, USB_CDC_LineCoding_TypeDef* DATA)
{
  assert_param(DATA);
  if (wINDEX != 0)
  {
    /* Invalid interface */
    return USB_ERR_INV_REQ;
  }

  /* Just store received settings */
  *DATA = LineCoding;
  return USB_SUCCESS;
}

/* USB_CDC_HANDLE_SET_LINE_CODING implementation example */
USB_Result USB_CDC_SetLineCoding(uint16_t wINDEX, const USB_CDC_LineCoding_TypeDef* DATA)
{
  assert_param(DATA);
  if (wINDEX != 0)
  {
    /* Invalid interface */
    return USB_ERR_INV_REQ;
  }

  /* Just send back settings stored earlier */
  LineCoding = *DATA;
  return USB_SUCCESS;
}

#endif /* USB_CDC_LINE_CODING_SUPPORTED */

#ifdef USB_DEBUG_PROTO

/* Overwritten USB_DEVICE_HANDLE_SETUP default handler - to dump received setup packets */
USB_Result USB_DeviceSetupPacket_Debug(USB_EP_TypeDef EPx, const USB_SetupPacket_TypeDef* USB_SetupPacket)
{

#ifdef USB_DEBUG_PROTO
  SetupPackets[SPIndex].packet = *USB_SetupPacket;
  SetupPackets[SPIndex].address = USB_GetSA();
  SPIndex = (SPIndex < USB_DEBUG_NUM_PACKETS ? SPIndex + 1 : 0);
#endif /* USB_DEBUG_PROTO */

  return USB_DeviceSetupPacket(EPx, USB_SetupPacket);
}

#endif /* USB_DEBUG_PROTO */
