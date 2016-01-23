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
#include "Acquiring_AmmoSubHSM.h"
#include "Wall_Hugging_SubHSM.h"
#include "AA_LineFollowing_SubHSM.h"
#include "AlignCollect_SubHSM.h"
#include<stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define LIST_OF_Acquiring_Ammo_STATES(STATE) \
        STATE(InitPSubState) \
        STATE(Lost) /*Make sure state names are unique in their hierachy*/ \
        STATE(Wall_Hugging)       \
        STATE(Line_Following)  \
        STATE(Align_Collect)  \
        STATE(Find_Next_T)  \
        STATE(Missed_T) \

#define ENUM_FORM(STATE) STATE, //Enums are reprinted verbatim and comma'd

typedef enum {
    LIST_OF_Acquiring_Ammo_STATES(ENUM_FORM)
} SubAcquiring_AmmoState_t;

#define STRING_FORM(STATE) #STATE, //Strings are stringified and comma'd
static const char *StateNames[] = {
    LIST_OF_Acquiring_Ammo_STATES(STRING_FORM)
};


ES_Event getitdone;

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static SubAcquiring_AmmoState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitAcquiring_AmmoSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunAcquiring_AmmoSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTemplateSubHSM(ES_Event ThisEvent)
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
ES_Event RunAcquiring_AmmoSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    SubAcquiring_AmmoState_t nextState;

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                Init_AA_LineFollowing_SubHSM();
                InitWall_Hugging_SubHSM();
                InitAlignCollect_SubHSM();

                nextState = Lost; // now put the machine into the actual initial state
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case Lost:
            ThisEvent = Run_AA_LineFollowing_SubHSM(ThisEvent);
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {

                    case ES_ENTRY:
                        break;

                    case ES_EXIT:
                        break;

                    case BUMPED:
                        nextState = Wall_Hugging;
                        makeTransition = TRUE;
                        getitdone.EventType = BUMP_CHECK;
                        getitdone.EventParam = ThisEvent.EventParam;
                        ThisEvent.EventType = ES_NO_EVENT;
                        PostDagobotHSM(getitdone);
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

        case Wall_Hugging: // If current state is state OtherState
            ThisEvent = RunWall_Hugging_SubHSM(ThisEvent); // run sub-state machine for this state
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        break;

                    case T_JUNCTION:
                        nextState = Align_Collect;
                        makeTransition = TRUE;
                        getitdone.EventType = FORCED;
                        getitdone.EventParam = 0;
                        ThisEvent.EventType = ES_NO_EVENT;
                        PostDagobotHSM(getitdone);
                        break;


                    case MISSED_T:
                        nextState = Lost;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(wallhuggingtimer);
                        break;

                    case ES_TIMEOUT:
                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;

        case Line_Following:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        break;
                    case ES_EXIT:
                        break;

                    case ES_TIMEOUT:
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;

        case Align_Collect:
            ThisEvent = RunAlignCollect_SubHSM(ThisEvent);
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        break;

                    case ES_EXIT:
                        break;

                    case ES_TIMEOUT:
                        break;

                    case MISSED_T:
                        nextState = Lost;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunAcquiring_AmmoSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunAcquiring_AmmoSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}

