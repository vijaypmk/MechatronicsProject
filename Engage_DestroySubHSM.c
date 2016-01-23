/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "DagobotHSM.h"
#include "Dagobot.h"
#include "Engage_DestroySubHSM.h"
#include "Engage_Destroy_Wall_Hugging_SubHSM.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define LIST_OF_Engage_Destroy_STATES(STATE) \
        STATE(Init_ED) \
        STATE(Engage_Destroy_Searching) /*Make sure state names are unique in their hierachy*/ \
        STATE(Firing)       \
        STATE(Engage_Destroy_Wall_Hugging)  \
        STATE(Redirecting)  \

#define ENUM_FORM(STATE) STATE, //Enums are reprinted verbatim and comma'd

typedef enum {
    LIST_OF_Engage_Destroy_STATES(ENUM_FORM)
} SubEngage_DestroyState_t;

#define STRING_FORM(STATE) #STATE, //Strings are stringified and comma'd
static const char *StateNames[] = {
    LIST_OF_Engage_Destroy_STATES(STRING_FORM)
};


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static SubEngage_DestroyState_t CurrentState = Init_ED;
static uint8_t MyPriority;
uint8_t makeTransition = FALSE; // use to flag transition
SubEngage_DestroyState_t nextState; //

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitEngage_DestroySubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitEngage_DestroySubHSM(void) {
    ES_Event returnEvent;

    CurrentState = Init_ED;
    returnEvent = RunEngage_DestroySubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}


/**
 * @Function RunEngage_DestroySubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunEngage_DestroySubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    SubEngage_DestroyState_t nextState;

    ES_Event eventtopost, donefiring;
    ES_Tattle(); // trace call stack


    switch (CurrentState) {
        case Init_ED: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT) {// only respond to ES_Init

                //call all substate run functions here
                InitEngage_Destroy_Wall_Hugging_SubHSM();

                nextState = Engage_Destroy_Searching;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case Engage_Destroy_Searching:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {

                    case ES_ENTRY:
//                        ES_Timer_InitTimer(15, 2500); //TODO: Move to exit from acquiring_ammo
//                        PivotRight(speed);
//                        PivotRight(speed);
                        StraightForward(speed); //speed // move forwards away from the ammo dump
                        //pivot timer
                        // start pivoting
                        Dagobot_SetLoaderServo(1200);
                        ThisEvent.EventType = ES_NO_EVENT;
//                        ThisEvent.EventParam = 0;
//                        PostDagobotHSM(ThisEvent);
                        //TODO: Add flag to only go forwards if just from Acquiring_Ammo?

                        break;

//                    case AMMO:
//                        ThisEvent.EventType = ES_NO_EVENT;
//                        break;

                    case ES_EXIT:
                        FullStop(); // aimed at the enemy: stop and fire
                        ES_Timer_StopTimer(15);
                       // ES_Timer_StopTimer(forwardtimer);
                        break;

                    case SNIPED:
//                        debug("check event");
                         FullStop();
                        nextState = Firing;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    case BUMPED:
                        nextState = Engage_Destroy_Wall_Hugging;
                        makeTransition = TRUE;
                        eventtopost.EventType = BUMP_CHECK;
                        eventtopost.EventParam = ThisEvent.EventParam;
//                          ThisEvent.EventType = BUMP_CHECK;
//                        ThisEvent.EventParam = ThisEvent.EventParam;
                        PostDagobotHSM(eventtopost);
                        break;
//
//                    case TAPE:
//                        nextState = Redirecting;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                        break;

                    case ES_TIMEOUT:
                        //if (ThisEvent.EventParam == forwardtimer) {
                        //    ES_Timer_InitTimer(pivotingtimer, 800);
                        //    PivotRight(newspeed);
                        //}
//                        if (ThisEvent.EventParam == 15) {
//                            FullStop(); // stop after spinning
//                            StraightForward(speed*1.25); // didn't find enemy, head towards obstacle (or at least forwards)
//                        }

//                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;

        case Firing:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
//                        int AmmoState = Dagobot_ReadLoaderTape();
//                        if (AmmoState == 1) { // have ammo!
//                        debug("check");
                            FullStop();
                            ES_Timer_InitTimer(ammofindtimer, 2000); // head towards deadbot
                            StraightForward(speed);
//                        }
                        break;
                        
//                    case SNIPED:
//                        if(ThisEvent.EventParam == 0)
//                        {
//                            
//                        }

//                    case BUMPED:
//                        if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) == FRONT_LEFT_BUMP) { // front left bump
//
//                                ThisEvent.EventType = ES_NO_EVENT;
//                            } else if ((ThisEvent.EventParam & FRONT_RIGHT_BUMP) == FRONT_RIGHT_BUMP) { // front right bump
//                                nextState = Reversing_WH;
//                                makeTransition = TRUE;
//                                ThisEvent.EventType = ES_NO_EVENT;
//                            } else if ((ThisEvent.EventParam & FRONT_BUMPS) == FRONT_BUMPS) { // both front bumpers
//                                nextState = Reversing_WH;
//                                makeTransition = TRUE;
//                                ThisEvent.EventType = ES_NO_EVENT;
//                            }
//                        else {
//                            ThisEvent.EventType = ES_NO_EVENT;
//                        }
//                        break;

                    case ES_EXIT:
//                        ES_TIMER_StopTimer(motortimer);
                        Dagobot_SetLoaderServo(1200);
                        ES_Timer_StopTimer(shootingtimer);
                        ES_Timer_StopTimer(ammofindtimer);
//                        ThisEvent.EventType = ES_NO_EVENT; //TODO: remove??
                        break;

                    case ES_TIMEOUT:
                        if(ThisEvent.EventParam == ammofindtimer){
                            FullStop();
                            int i;
                            for(i = 0; i < 30000; i++)
                            {
                                asm("nop");
                            }
                            Dagobot_SetLoaderServo(2000); // start running up motor
                            ES_Timer_InitTimer(shootingtimer, shootingtimervalue);
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
//                        if (ThisEvent.EventParam == motortimervalue) {//done spinning up motor
//                            Dagobot_SetLoaderServo(servorelease); // drop balls into shooter
//                            ES_Timer_InitTimer(shootingtimer, shootingtimervalue);
//                        }
                        if (ThisEvent.EventParam == shootingtimer) {
                            donefiring.EventType = DONE_FIRING; // upper level deal with getting to portal
                            donefiring.EventParam = 0;
                            PostDagobotHSM(donefiring);
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;

        case Engage_Destroy_Wall_Hugging:
            ThisEvent = RunEngage_Destroy_Wall_Hugging_SubHSM(ThisEvent); // run sub-state machine for this state
            //TODO: make new wall_hugging file/fn?
            // and/or deal with entry from differet events
            
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        // this is where you would put any actions associated with the
                        // entry to this state
//                        ES_Timer_InitTimer(wallhuggingtimer, 8000);
                        break;

                    case SNIPED:
                         FullStop();
                        nextState = Firing;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

//                    case TAPE:
//                        if((ThisEvent.EventParam & 0x000010) != 0x000010) {
//                        nextState = Redirecting;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                        }
//                        break;

                    case ES_EXIT:
                        // this is where you would put any actions associated with the
                        // exit from this state
//                        ES_Timer_StopTimer(wallhuggingtimer);
                        FullStop();
                        break;

                    case ES_TIMEOUT:
//                        if (ThisEvent.EventParam == wallhuggingtimer) { // timer to check for enemy every once in a while while bumping around
//                            //TODO: make new checkin timer?
//                            nextState = Engage_Destroy_Searching; // search
//                            makeTransition = TRUE;
//                            ThisEvent.EventType = ES_NO_EVENT;
//
//                        }
                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;

        case Redirecting:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        PivotRight(speed);
                        ES_Timer_InitTimer(pivotingtimer, pivotingtimervalue);
                        break;



                    case ES_EXIT:
                        ES_Timer_StopTimer(pivotingtimer);
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam = pivotingtimer) {
                            nextState = Engage_Destroy_Searching; // search
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT; // head for whatever's in the future
                        }

                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;


        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunEngage_DestroySubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunEngage_DestroySubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/


/*******************************************************************************
 * TEST HARNESS                                                                *
 ******************************************************************************/

#ifdef ENGAGE_DESTROYSUBHSM_TEST // <-- change this name and define it in your MPLAB-X
//     project to run the test harness
#include <stdio.h>

void main(void) {
    ES_Return_t ErrorType;
    BOARD_Init();
    // When doing testing, it is useful to annouce just which program
    // is running.

    printf("Starting the Hierarchical State Machine Test Harness \r\n");
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

#endif // ENGAGE_DESTROYSUBHSM_TEST