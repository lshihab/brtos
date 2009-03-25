
/*********************************************************************************************************
*                                               BRTOS
*                                Brazilian Real-Time Operating System
*                            Acronymous of Basic Real-Time Operating System
*
*                              
*                                  Open Source RTOS under MIT License
*
*
*
*                                          BRTOS Kernel Header
*
*
*   Author:   Gustavo Weber Denardin
*   Revision: 1.0
*   Date:     20/03/2009
*
*********************************************************************************************************/

#ifndef OS_BRTOS_H
#define OS_BRTOS_H

#include "OS_types.h"
#include "HAL.h"





////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      OS Defines                                  /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// Define if simulation or DEBUG
#define DEBUG 1

// Define if whatchdog active
#define COP 1

// Define CPU Stack Pointer Size
#define SP_SIZE 16

// Define the number of Task to be Installed
// must always be equal or higher to NumberOfInstalledTasks
#define NUMBER_OF_TASKS 2


//#define FALSE (INT8U)0
//#define TRUE  (INT8U)1
#define READY (INT8U)2

#define OK                           (INT8U)0
#define NO_MEMORY                    (INT8U)1
#define END_OF_AVAILABLE_PRIORITIES  (INT8U)2
#define BUSY_PRIORITY                (INT8U)3
#define INVALID_TIME                 (INT8U)4

#define TRUE 1
#define FALSE 0


// Suspended Types
#define DELAY     0
#define SEMAPHORE 1
#define MAILBOX   2
#define QUEUE     3
#define MUTEX     4


// TickTimer Defines
#define configCPU_CLOCK_HZ          (INT32U)12000
#define configTICK_RATE_HZ          (INT32U)1000
#define configTIMER_PRE_SCALER      0
#define TickCountOverFlow           (INT16U)32000
#define configRTC_CRISTAL_HZ        (INT32U)1000
#define configRTC_PRE_SCALER        10
#define OSRTCEN                     0


//Stack Defines
// P/ Coldfire com 8KB de RAM, limite de 5KB p/ STACK Virtual
#define HEAP_SIZE 512


// Others Defines
#define configMAX_TASK_NAME_LEN 16
#define configMAX_TASK_INSTALL 32

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Context Tasks Structure Prototypes          /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

typedef struct ContextTag                                                 
{
   //INT8S Name[configMAX_TASK_NAME_LEN];
   INT16U StackPoint;
   INT16U StackInit;
   INT16U TimeToWait;
   INT8U  Suspended;        // Substituir por state - running, suspended, etc
   INT8U  SuspendedType;
   INT8U  Priority;         // adicionar funcionalidades
} ContextType;

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Functions Prototypes                        /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

INT8U  TaskStartScheduler(void);
void DelayTask(INT16U time);
INT8U DelayTaskHMSM(INT8U hours, INT8U minutes, INT8U seconds, INT16U miliseconds);
void OS_INT_EXIT_CF(void);
void PreInstallTasks(void);

void OSSchedule(void);


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      OS Variables Extern Declarations            /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

extern INT8U iNesting;
extern INT8U currentTask;
extern ContextType ContextTask[NUMBER_OF_TASKS + 2];
extern INT16U iStackAddress;
extern INT8U NumberOfInstalledTasks;
extern INT16U counter;
extern INT16U OSDuty;
extern INT8U PriorityVector[configMAX_TASK_INSTALL];
extern INT16U OSDutyTmp;
extern INT16U OSWaitLimit;
extern INT8U STACK[HEAP_SIZE];
extern INT8U maxPriority;
extern INT32U TaskAlloc;
extern const char *version;

#if (SP_SIZE == 32)
  extern INT32U StackAddress;
#endif

#if (SP_SIZE == 16)
  extern INT16U StackAddress;
#endif

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


#endif
