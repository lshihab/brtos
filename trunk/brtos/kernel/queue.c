#include <hidef.h> /* for EnableInterrupts macro */
#include "BRTOS.h"
#include "queue.h"
#include <stdlib.h>
#include "event.h"


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Create Queue Function                       /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

INT8U OSQCreate(OS_QUEUE *cqueue, INT16U size, OS_EVENT **event)
{
  int i=0;
  OS_EVENT *pont_event;

  
  // Verifica se ainda h� blocos de controle de eventos dispon�veis
  if (iOS_Event < OS_MAX_EVENTS)
  {
      iOS_Event++;
      pont_event = OSEventFreeList;
      
      // Posiciona a lista de blocos de controle de eventos livre no pr�ximo bloco dispon�vel
      OSEventFreeList = &OSEventTbl[iOS_Event];
  } else
  {
    // Caso n�o haja mais blocos dispon�veis, retorna exce��o
    return(NO_AVAILABLE_EVENT);
  }
  
  // Configura dados de evento de lista
  cqueue->OSQPtr = (INT8U *) calloc(size,sizeof(INT8U));
  cqueue->OSQSize =  size;
  cqueue->OSQEntries =  0;
  cqueue->OSQStart = cqueue->OSQPtr;
  cqueue->OSQEnd =   cqueue->OSQPtr + cqueue->OSQSize;
  cqueue->OSQIn =    cqueue->OSQPtr;
  cqueue->OSQOut =   cqueue->OSQPtr;
  
  // Aloca tipo de evento e dados do evento
  pont_event->OSEventType = OS_EVENT_TYPE_Q;
  pont_event->OSEventPtr = cqueue;
  pont_event->OSEventGrp = 0;
  
  
  for(i=0;i<OS_EVENT_TABLE_SIZE;i++)
  {
    pont_event->OSEventTbl[i]=0;  
  }
  
  *event = pont_event;
  
  return(ALLOC_EVENT_OK);
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Write Queue Function                        /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

INT8U OSWQueue(OS_QUEUE *cqueue,INT8U data)
{
  OSEnterCritical;
  if (cqueue->OSQEntries < cqueue->OSQSize)
    cqueue->OSQEntries++;
  else
    return BUFFER_UNDERRUN;  
  
  if (cqueue->OSQIn == cqueue->OSQEnd)
    cqueue->OSQIn = cqueue->OSQStart;
  
  *cqueue->OSQIn = data;
  cqueue->OSQIn++;
  OSExitCritical;
  return READ_BUFFER_OK;
  
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Read Queue Function                         /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

INT8U OSRQueue(OS_QUEUE *cqueue)
{
  INT8U data;
  
  OSEnterCritical;
  if(cqueue->OSQEntries > 0)
  {
      
    if (cqueue->OSQOut == cqueue->OSQEnd)
      cqueue->OSQOut = cqueue->OSQStart;
  
    data = *cqueue->OSQOut;
  
    cqueue->OSQOut++;
    cqueue->OSQEntries--;
    OSExitCritical;
    return data;
  }
  else
  {
    OSExitCritical;
    return NULL;
  }
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Clean Queue Function                        /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

INT8U OSCleanQueue(OS_QUEUE *cqueue)
{
  cqueue->OSQEntries = 0;
  cqueue->OSQIn = cqueue->OSQStart;
  cqueue->OSQOut = cqueue->OSQStart;

  return CLEAN_BUFFER_OK;
  
}


