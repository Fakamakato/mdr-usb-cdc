#include "MDR32F9Qx_it.h"
#include "MDR32F9Qx_uart.h"
#include <stdint.h>
#include "queue.h"

extern queue_t q_usb;
extern queue_t q_spi;

void NMI_Handler(void)
{
}
void HardFault_Handler(void)
{
}
void MemManage_Handler(void)
{
}
void BusFault_Handler(void)
{
}
void UsageFault_Handler(void)
{
}
void SVC_Handler(void)
{
}
void DebugMon_Handler(void)
{
}
void PendSV_Handler(void)
{
}

volatile uint32_t uwTick;
void SysTick_Handler(void)
{
	uwTick++;
	
}
void SSP1_IRQHandler(void)
{
	(void)MDR_SSP1->DR;
	MDR_PORTF->RXTX = 1 << 2;
}


void SSP2_IRQHandler(void)
{
	qInsert(&q_usb,MDR_SSP2->DR);
}


void UART2_IRQHandler()
{
	if (UART_GetITStatusMasked(MDR_UART2, UART_IT_RX) == SET)
  {
    UART_ClearITPendingBit(MDR_UART2,UART_IT_RX);

		//qInsert(&q_spi,(0x00FF & MDR_UART2->DR));
	}
}

