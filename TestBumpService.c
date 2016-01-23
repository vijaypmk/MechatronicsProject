/*
 * File: TemplateService.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a simple service to work with the Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "TestBumpService.h"
#include "Dagobot.h"
#include "DagobotHSM.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */


static uint8_t MyPriority;
static uint8_t count = 0;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTestBumpService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTestBumpService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunTestBumpService(ES_Event ThisEvent)
{
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    static unsigned int bumperArray[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, LastbumpState = 0x00,  currentLoadTapeState[] = {0, 0, 0, 0, 0}, lastLoadTapeState = 0;

//     static unsigned int bumperArray2[] = {0x00,0x00,0x00,0x00,0x00,0x00}, LastbumpState2 = 0x00;
    static uint8_t index = 0, loadindex = 0;
    int count = 0, loadcount = 0;
     ES_Event LoaderEvent;

    /********************************************
     in here you write your service code
     *******************************************/
    
    if (ThisEvent.EventType == ES_TIMEOUT)// only respond to ES_Init
    {
      ES_Timer_SetTimer(bumptimer, bumptimervalue); // Bump sensor check every 5ms
      ES_Timer_StartTimer(bumptimervalue);
        // No hardware initialization or single time setups, those
        // go in the init function above.
        //
        // This section is used to reset service for some reason
       
      bumperArray[index] = Dagobot_ReadBumpers();
      currentLoadTapeState[index] = Dagobot_ReadLoaderTape();
      int i;
      for(i=1; i<10; i++){
          if(bumperArray[i-1] != bumperArray[index] ){
              LastbumpState = bumperArray[index];
              count++;
          }
          else
              count--;
      }
            for (i = 1; i < 5; i++) {
                 if (currentLoadTapeState[i - 1] != currentLoadTapeState[index]) {
            loadcount ++;
            lastLoadTapeState = currentLoadTapeState[loadindex];
        }
                else
                    loadcount --;
            }
      if(count > 0) {
          ThisEvent.EventType = BUMPED;
          ThisEvent.EventParam = bumperArray[index];
          PostDagobotHSM(ThisEvent);
      }
       if(loadcount > 0) {
          LoaderEvent.EventType = AMMO;
          LoaderEvent.EventParam = currentLoadTapeState[loadindex];
          PostDagobotHSM(LoaderEvent);
      }
    }
    index++;
    if(index == 10)  index = 0;
    if (loadindex == 5) loadindex = 0;

    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/


/*******************************************************************************
 * TEST HARNESS                                                                *
 ******************************************************************************/

#ifdef TestBumpSERVICE_TEST // <-- change this name and define it in your MPLAB-X
//     project to run the test harness
#include <stdio.h>

void main(void)
{
    ES_Return_t ErrorType;
    BOARD_Init();
    // When doing testing, it is useful to annouce just which program
    // is running.

    printf("Starting the Simple Service Test Harness \r\n");
    printf("using the 2nd Generation Events & Services Framework\n\r");

    // Your hardware initialization function calls go here

    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    if (ErrorType == Success) {

        ErrorType = ES_Run();

    }

    //
    //if we got to here, there was an error
    //

    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer");
        break;
    case FailedInit:
        printf("Failed Initialization");
        break;
    default:
        printf("Other Failure");
        break;
    }

    while (1) {
        ;
    }
}

#endif // TEMPLATESERVICE_TEST