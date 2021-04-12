/**
  ******************************************************************************
  * @file    spi.h
  * @author  zns
  * @version V1.0.0
  * @date    10-April-2021
  * @brief   This file contains all the HAL for the spi module.
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SPI_H_
#define _SPI_H_


/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Exported functions ---------------------------------------------------------*/
void spi1Init(void);
void spi2Init(void);
void spi1Send(uint8_t data);
#endif
