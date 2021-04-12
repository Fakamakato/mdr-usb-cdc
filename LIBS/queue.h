/**
  ******************************************************************************
  * @file    queue.h
  * @author  zns
  * @version V1.0.0
  * @date    11-April-2021
  * @brief   This file contains all the HAL for the spi module.
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef QUEUE_H
#define QUEUE_H


/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdbool.h"
#include "stdint.h"

#define Q_SIZE 32
/* data type to work with queue */
typedef struct queue_s
{
    uint8_t *queue;
    uint8_t front;
    uint8_t rear;
    uint8_t itemCount;

} queue_t;
/* Exported functions ---------------------------------------------------------*/


uint8_t qPeek(queue_t *q);
bool qIsEmpty(queue_t *q);
bool qIsFull(queue_t *q);
int qSize(queue_t *q);
void qInsert(queue_t *q,uint8_t item);
uint8_t qRetrieve(queue_t *q);

#endif