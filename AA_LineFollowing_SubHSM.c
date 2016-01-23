/*
 * File: Line_FollowingSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Line_Following file to set up a Heirarchical State Machine to work with the Events and
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
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunLine_FollowingSM()
 * 10/23/11 18:20 jec      began conversion from SMLine_Following.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "DagobotHSM.h"
#include "Acquiring_AmmoSubHSM.h"
#include "AA_LineFollowing_SubHSM.h"
#include "IO_Ports.h"
#include<stdio.h>
#include "LED.h"
#include "AD.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define LIST_OF_AA_LINE_FOLLOWING_subHSM_STATES(STATE) \
        STATE(Init_AA_LineFollowing) \
        STATE(EntryLineFollowing) \
        STATE(Adjusting_Right) \
        STATE(Adjusting_Left) \
        STATE(Pivoting_Right)  \
        STATE(Reversing_Left) \

#define ENUM_FORM(STATE) STATE, //Enums are reprinted verbatim and comma'd

typedef enum {
    LIST_OF_AA_LINE_FOLLOWING_subHSM_STATES(ENUM_FORM)
} AA_LineFollowing_subHSM_t;


#define STRING_FORM(STATE) #STATE, //Strings are stringified and comma'd
static const char *StateNames[] = {
    LIST_OF_AA_LINE_FOLLOWING_subHSM_STATES(STRING_FORM)
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

static AA_LineFollowing_subHSM_t CurrentState = Init_AA_LineFollowing; // <- change name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitLine_FollowingSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunLine_FollowingFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t Init_AA_LineFollowing_SubHSM(void) {
    ES_Event returnEvent;
    CurrentState = Init_AA_LineFollowing;
    returnEvent = Run_AA_LineFollowing_SubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunLine_FollowingSubHSM(ES_Event ThisEvent)
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
ES_Event Run_AA_LineFollowing_SubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    AA_LineFollowing_subHSM_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case Init_AA_LineFollowing: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                nextState = EntryLineFollowing;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case EntryLineFollowing:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        StraightForward(speed);
                        break;

                    case ES_EXIT:
                        break;

                    case TAPE:
                        if (ThisEvent.EventParam == 0b100000) { // LL: 20, 100000
                            FullStop();
                            nextState = Adjusting_Left;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if (ThisEvent.EventParam == 0b000010) { // RR: 02
                            FullStop();
                            nextState = Pivoting_Right;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & 0b110010) == 0b110010) { // LL, L,  RR
                            FullStop();
                            nextState = Reversing_Left;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & 0b001001) == 0b001001) { // F, B
                            FullStop();
                            nextState = Adjusting_Right;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;
                }
            }
            break;

        case Adjusting_Left:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        TurnLeft(speed * 1);
                        break;

                    case TAPE:
                        if ((ThisEvent.EventParam & 0b000010) == 0b000010) { // RR (corner)
                            nextState = Pivoting_Right;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & 0b001000) == 0b001000) { //F
                            FullStop();
                            nextState = Adjusting_Right; //Adjusting_Right
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case ES_EXIT:
                        break;
                }
            }
            break;

        case Adjusting_Right:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        TurnRight(speed * 1);
                        break;

                    case TAPE:
                        if ((ThisEvent.EventParam & 0b010000) == 0b010000) { // L
                            FullStop();
                            nextState = Adjusting_Left;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & 0b100000) == 0b100000) { // LL
                            FullStop();
                            nextState = Adjusting_Left;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & 0b000010) == 0b000010) { // RR (corner)
                            nextState = Pivoting_Right;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & 0b000110) == 0b000110) { //R, RR (corner)
                            nextState = Pivoting_Right;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case ES_EXIT:
                        break;
                }
            }
            break;

        case Pivoting_Right:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        ES_Timer_InitTimer(ammofindtimer, 2000);
                        PivotRight(speed);
                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(ammofindtimer);
                        break;

                    case TAPE:

                        if ((ThisEvent.EventParam & 0b110010) == 0b110010) { // LL, L, RR
                            nextState = Reversing_Left;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & 0b010000) == 0b010000) { // L
                            FullStop();
                            nextState = Adjusting_Left;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & 0b100001) == 0b100001) { // LL, B
                            nextState = Adjusting_Left;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & 0b100000) == 0b100000) { // LL
                            nextState = Adjusting_Left;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == ammofindtimer) {
                            nextState = EntryLineFollowing;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;
                }
            }
            break;

        case Reversing_Left:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        ES_Timer_InitTimer(turningtimer, turningtimervalue);
                        TurnLeft(-(speed));
                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(turningtimer);
                        break;

                    case ES_TIMEOUT:
                        nextState = Adjusting_Left;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;


                    case TAPE:
                        if ((ThisEvent.EventParam & 0b100000) == 0b100000) { // LL
                            nextState = Adjusting_Left;
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


    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        Run_AA_LineFollowing_SubHSM(EXIT_EVENT);
        CurrentState = nextState;
        Run_AA_LineFollowing_SubHSM(ENTRY_EVENT);
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}