/*
 * File: BumpedSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Dagobot file to set up a Heirarchical State Machine to work with the Events and
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
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunDagobotHSM()
 * 10/23/11 18:20 jec      began conversion from SMDagobot.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "DagobotHSM.h"
#include "Acquiring_AmmoSubHSM.h"
#include "Wall_Hugging_SubHSM.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define LIST_OF_Wall_Hugging_STATES(STATE) \
        STATE(Init_Wall_Hugging) \
        STATE(Bump_Checking) \
        STATE(Pivoting_Right_WH) /*Make sure state names are unique in their hierachy*/ \
        STATE(Turning_Left_WH)       \
        STATE(Escape_Right)       \
        STATE(Stopping_WH)       \
        STATE(Reversing_WH)  \
        STATE(Reverse_Turning_Right) \
        STATE(Adjusting_Left_WH) \
        STATE(Forwarding_Parallel_Wall_WH) \
        STATE(Forwarding_Towards_Wall_WH) \
        STATE(Pivoting_Left_WH) \

#define ENUM_FORM(STATE) STATE, //Enums are reprinted verbatim and comma'd

typedef enum {
    LIST_OF_Wall_Hugging_STATES(ENUM_FORM)
} SubWall_Hugging_State_t;

#define STRING_FORM(STATE) #STATE, //Strings are stringified and comma'd
static const char *StateNames[] = {
    LIST_OF_Wall_Hugging_STATES(STRING_FORM)
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

static SubWall_Hugging_State_t CurrentState = Init_Wall_Hugging; // <- change name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitDagobotSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunDagobotFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitWall_Hugging_SubHSM(void) {
    ES_Event returnEvent;

    CurrentState = Init_Wall_Hugging;
    returnEvent = RunWall_Hugging_SubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunDagobotSubHSM(ES_Event ThisEvent)
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
ES_Event RunWall_Hugging_SubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    SubWall_Hugging_State_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack
    ES_Event wallhuggy;
    static int bumpcount = 0;

    switch (CurrentState) {
        case Init_Wall_Hugging: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                nextState = Bump_Checking;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                bumpcount++;
            }
            break;

        case Bump_Checking: // in the first state, replace this with correct names
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        FullStop();
                        break;

                    case ES_EXIT:
                        FullStop();
                        break;

                    case BUMP_CHECK:

                        ES_Timer_InitTimer(ammofindtimer, 1500);
                        if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) == FRONT_LEFT_BUMP) { // front left bump
                            nextState = Reversing_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & FRONT_RIGHT_BUMP) == FRONT_RIGHT_BUMP) { // front right bump
                            nextState = Reversing_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & FRONT_BUMPS) == FRONT_BUMPS) { // both front bumpers
                            nextState = Reversing_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case ES_KEYINPUT:
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    case ES_TIMEOUT:
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;

        case Reversing_WH: // example of a state without a sub-statemachine
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        ES_Timer_InitTimer(reversingtimer, reversingfromwallvalue); //fully charged is 200
                        StraightReverse(speed);
                        break;

                    case ES_EXIT:
                        FullStop();
                        ES_Timer_StopTimer(reversingtimer);
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == reversingtimer) {
                            nextState = Pivoting_Right_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;

        case Pivoting_Right_WH:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        ES_Timer_InitTimer(pivotingtimer, right90value); //fully charged value 270
                        PivotRight(speed);
                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(pivotingtimer);
                        break;
                    case ES_KEYINPUT:
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == pivotingtimer) {
                            nextState = Forwarding_Parallel_Wall_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;

        case Forwarding_Parallel_Wall_WH:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        if (bumpcount > 1) { // if long ammo dump wall
                            ES_Timer_InitTimer(turningtimer, forwardsparallellongwallvalue); //300
                            StraightForward(speed);
                        } else {
                            ES_Timer_InitTimer(turningtimer, forwardsparallelwallvalue); //300
                            StraightForward(speed);
                        }
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == turningtimer) {
                            nextState = Pivoting_Left_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case BUMPED:
                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(turningtimer);
                        break;
                }
            }
            break;

        case Pivoting_Left_WH:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        ES_Timer_InitTimer(pivotingtimer, left90value);
                        PivotLeft(speed);
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam = pivotingtimer) {
                            FullStop();
                            nextState = Forwarding_Towards_Wall_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(pivotingtimer);
                        break;
                }
            }
            break;

        case Forwarding_Towards_Wall_WH:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        StraightForward(speed);
                        break;

                    case ES_TIMEOUT:
                        break;

                    case TAPE:
                        //FullStop();
                        if ((ThisEvent.EventParam != 0x01) && IsTimerExpired(ammofindtimer)) { // ignore back tape, only get TAPE after 1500ms
                            wallhuggy.EventType = T_JUNCTION;
                            wallhuggy.EventParam = 0;
                            PostDagobotHSM(wallhuggy);
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case BUMPED:
                        bumpcount++;
                        if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) == FRONT_LEFT_BUMP) { // left front bump
                            nextState = Reversing_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & FRONT_RIGHT_BUMP) == FRONT_RIGHT_BUMP) { // left front bump
                            nextState = Reversing_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & FRONT_BUMPS) == FRONT_BUMPS) { // left front bump
                            nextState = Reversing_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(turningtimer);
                        ES_Timer_StopTimer(ammofindtimer);
                        break;
                }
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunWall_Hugging_SubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunWall_Hugging_SubHSM(ENTRY_EVENT); // <- rename to your own Run function
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

#ifdef BUMPEDSUBHSM_TEST // <-- change this name and define it in your MPLAB-X
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

#endif // BUMPEDSUBHSM_TEST
