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
#include "AlignCollect_SubHSM.h"
#include<stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define LIST_OF_AlignCollect_SubHSM_STATES(STATE) \
        STATE(InitPSubState) \
        STATE(Buffer_State) \
        STATE(Forwarding_Entry_AC) \
        STATE(Pivoting_Right_AC) \
        STATE(Reversing_AC) \
        STATE(Forwarding_AC) \
        STATE(Stopping_AC) \
       
#define ENUM_FORM(STATE) STATE, //Enums are reprinted verbatim and comma'd

static int plungecount = 0;

typedef enum {
    LIST_OF_AlignCollect_SubHSM_STATES(ENUM_FORM)
} SubAlignCollect_SubHSMState_t;

#define STRING_FORM(STATE) #STATE, //Strings are stringified and comma'd
static const char *StateNames[] = {
    LIST_OF_AlignCollect_SubHSM_STATES(STRING_FORM)
};

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static SubAlignCollect_SubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
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
uint8_t InitAlignCollect_SubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunAlignCollect_SubHSM(INIT_EVENT);
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
ES_Event RunAlignCollect_SubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    SubAlignCollect_SubHSMState_t nextState; // <- change type to correct enum

    static int plungecount = 0;
    ES_Event Lost;
    ES_Tattle(); // trace call stack
    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                nextState = Buffer_State;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case Buffer_State:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {

                    case ES_ENTRY:
                        FullStop();
                        break;

                    case ES_EXIT:
                        break;

                    case FORCED:
                        nextState = Forwarding_AC;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case Forwarding_Entry_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        StraightForward(speed);
                        break;

                    case ES_EXIT:
                        FullStop();
                        break;

                    case TAPE:
                        if ((ThisEvent.EventParam & 0b000001) == 0b000001) { // back on
                            nextState = Pivoting_Right_AC;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;
                }
            }
            break;

        case Pivoting_Right_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        ES_Timer_InitTimer(replungetimer, 110); //100 //115 //150//200
                        PivotRight(speed);
                        break;

                    case ES_EXIT:
                        FullStop();
                        ES_Timer_StopTimer(replungetimer);
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == replungetimer) {
                            nextState = Reversing_AC;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;
                }
            }
            break;

        case Reversing_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        ES_Timer_InitTimer(replungetimer, 800); //1200 //1000 //800
                        StraightReverse(speed);
                        break;

                    case ES_EXIT:
                        FullStop();
                        ES_Timer_StopTimer(replungetimer);
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == replungetimer) {
                            nextState = Stopping_AC;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                }
            }
            break;

        case Stopping_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        plungecount++;
                        ES_Timer_InitTimer(replungetimer, 1000); //500
                        FullStop();
                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(replungetimer);
                        break;

                    case ES_TIMEOUT:
                        if ((ThisEvent.EventParam == replungetimer) && plungecount < 8) {
                            nextState = Forwarding_AC;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam == replungetimer) && plungecount > 7) {
                            Lost.EventType = MISSED_T;
                            Lost.EventParam = 0;
                            PostDagobotHSM(Lost);
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                }
            }
            break;

        case Forwarding_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        ES_Timer_InitTimer(replungetimer, 800);
                        StraightForward(speed);
                        break;

                    case ES_EXIT:
                        FullStop();
                        ES_Timer_StopTimer(replungetimer);
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == replungetimer) {
                            nextState = Pivoting_Right_AC;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;
                }
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) {
        RunAlignCollect_SubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunAlignCollect_SubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}