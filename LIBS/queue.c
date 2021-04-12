/**
  ******************************************************************************
  * @file    queue.c
  * @author  ZNS
  * @version V1.0.0
  * @date    11-April-2021
  * @brief   This file provides API for using queue entity.
  *          
  *  
*/

/* Includes ------------------------------------------------------------------*/
#include "queue.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* maximum amount of elements in queue */
#define Q_SIZE 32
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Global functions ---------------------------------------------------------*/


/**
 * @brief peek the element in queue
 * @param q pointer to the queue
 * @return first element in the queue
 */
uint8_t qPeek(queue_t *q)
{
   return q->queue[q->front];
}

/**
 * @brief check if queue is empty
 * @param q pointer to the queue
 * @return true == empty \ false == not empty
 */
bool qIsEmpty(queue_t *q)
{
   return (q->itemCount == 0);
}

/**
 * @brief check if queue is full
 * @param q pointer to the queue
 * @return true == full \ false == not full yet
 */
bool qIsFull(queue_t *q)
{
   return (q->itemCount == Q_SIZE);
}

/**
 * @brief get number of elements in the queue
 * @param q pointer to the queue
 * @return number of elements
 */
int qSize(queue_t *q)
{
   return q->itemCount;
}

/**
 * @brief insert element in the queue if it is not full
 *          otherwise element is skipped
 * @param q pointer to the queue
 * @param item
 * @return (void)
 */
void qInsert(queue_t *q,uint8_t item)
{
   if (!qIsFull(q))
   {

      if (q->rear == Q_SIZE)
      {
         q->rear = 0;
      }
      q->queue[q->rear++] = item;
      q->itemCount++;
   }
}

/**
 * @brief remove first element from the queue and get it's value
 *         you should check if queue is not empty first
 * @param q pointer to the queue
 * @return element
 */
uint8_t qRetrieve(queue_t *q)
{
   uint8_t item = q->queue[q->front++];
   if (q->front == Q_SIZE)
   {
      q->front = 0;
   }
   q->itemCount--;
   return item;
}
