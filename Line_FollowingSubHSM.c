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
#include "Line_FollowingSubHSM.h"
#include<stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define LIST_OF_LINE_FOLLOWING_STATES(STATE) \
        STATE(InitPSubState) \
        STATE(Tape) \
        STATE(Forward) \
        STATE(Turning_Left) /*Make sure state names are unique in their hierachy*/ \
        STATE(Pivot_Left)       \
        STATE(Turning_Right)  \
        STATE(Pivot_Right)  \

#define ENUM_FORM(STATE) STATE, //Enums are reprinted verbatim and comma'd
typedef enum {
    LIST_OF_LINE_FOLLOWING_STATES(ENUM_FORM)
} AA_LineFollowing_subHSM_t;


#define STRING_FORM(STATE) #STATE, //Strings are stringified and comma'd
static const char *StateNames[] = {
    LIST_OF_LINE_FOLLOWING_STATES(STRING_FORM)
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

static AA_LineFollowing_subHSM_t CurrentState = InitPSubState;   // <- change name to match ENUM
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
uint8_t Init_AA_LineFollowing_SubHSM(void)
{
     ES_Event returnEvent;

    CurrentState = InitPSubState;
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
ES_Event Run_AA_LineFollowing_SubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    AA_LineFollowing_subHSM_t nextState;      // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
    case InitPSubState: // If current state is initial Psedudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state

            // now put the machine into the actual initial state
            nextState = Tape;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case Tape: // in the first state, replace this with correct names
        if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
            switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // this is where you would put any actions associated with the
                // entry to this state
                break;
                
            case TAPE:
                //printf("jj");
                if ((ThisEvent.EventParam & Forwarding1) == Forwarding1) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Forwarding2) == Forwarding2) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Forwarding3) == Forwarding3) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Turning_Left1) == Turning_Left1) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Left2) == Turning_Left2) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Turning_Left3) == Turning_Left3) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Turning_Left4) == Turning_Left4) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Left5) == Turning_Left5) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Left6) == Turning_Left6) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Pivoting_Left) == Pivoting_Left) {
                nextState = Pivot_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Turning_Right1) == Turning_Right1) {
                nextState = Turning_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Right2) == Turning_Right2) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Turning_Right3) == Turning_Right3) {
                nextState = Turning_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Right4) == Turning_Right4) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Right5) == Turning_Right5) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Right6) == Turning_Right6) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Pivoting_Right1) == Pivoting_Right1) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Pivoting_Right2) == Pivoting_Right2) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Right_Corner) == Right_Corner) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Left_Corner == Left_Corner)) {
                nextState = Pivot_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Corner) == Corner) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

            case ES_EXIT:
                // this is where you would put any actions associated with the
                // exit from this state
                break;

            case ES_KEYINPUT:
                // this is an example where the state does NOT transition
                // do things you need to do in this state
                // event consumed
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_TIMEOUT:
                // create the case statement for all other events that you are
                // interested in responding to.
                nextState = TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            default: // all unhandled events pass the event back up to the next level
                break;
            }
        }
        break;

    case Forward: // If current state is state OtherState
        if (ThisEvent.EventType != ES_NO_EVENT) { // An event is active
            switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // this is where you would put any actions associated with the
                // entry to this state
                StraightForward(speed);
                ES_Timer_InitTimer(forwardtimer, forwardtimervalue);
                break;

            case TAPE:
                //printf("jj");
                if ((ThisEvent.EventParam & Forwarding1) == Forwarding1) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Forwarding2) == Forwarding2) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Forwarding3) == Forwarding3) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Turning_Left1) == Turning_Left1) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Left2) == Turning_Left2) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Turning_Left3) == Turning_Left3) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Turning_Left4) == Turning_Left4) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Left5) == Turning_Left5) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Left6) == Turning_Left6) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Pivoting_Left) == Pivoting_Left) {
                nextState = Pivot_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Turning_Right1) == Turning_Right1) {
                nextState = Turning_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Right2) == Turning_Right2) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Turning_Right3) == Turning_Right3) {
                nextState = Turning_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Right4) == Turning_Right4) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Right5) == Turning_Right5) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Right6) == Turning_Right6) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Pivoting_Right1) == Pivoting_Right1) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Pivoting_Right2) == Pivoting_Right2) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Right_Corner) == Right_Corner) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Left_Corner == Left_Corner)) {
                nextState = Pivot_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Corner) == Corner) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

            case ES_EXIT:
                // this is where you would put any actions associated with the
                // exit from this state
                break;

            case ES_TIMEOUT:
                // create the case statement for all other events that you are
                // interested in responding to. This does a transition
                //nextState = Tape;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            default: // all unhandled events pass the event back up to the next level
                break;
            }
        }
        break;

    case Pivot_Left: // example of a state without a sub-statemachine
        switch (ThisEvent.EventType) {
        case ES_ENTRY:
            // this is where you would put any actions associated with the
            // entry to this state
            //ES_Timer_InitTimer(pivotingtimer, pivotingtimervalue);
            PivotLeft(speed);
            break;

        case ES_EXIT:
            // this is where you would put any actions associated with the
            // exit from this state
            break;

        case ES_TIMEOUT:
            // create the case statement for all other events that you are
            // interested in responding to. This one does a transition
            //nextState = Tape;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            break;

        default: // all unhandled events pass the event back up to the next level
            break;
        }
        break;
        
    case Pivot_Right: // example of a state without a sub-statemachine
        switch (ThisEvent.EventType) {
        case ES_ENTRY:
            // this is where you would put any actions associated with the
            // entry to this state
            PivotRight(speed);
            //ES_Timer_InitTimer(pivotingtimer, pivotingtimervalue);
            break;

        case ES_EXIT:
            // this is where you would put any actions associated with the
            // exit from this state
            break;

            case TAPE:
                //printf("jj");
                if ((ThisEvent.EventParam & Forwarding1) == Forwarding1) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Forwarding2) == Forwarding2) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Forwarding3) == Forwarding3) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Turning_Left1) == Turning_Left1) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Left2) == Turning_Left2) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Turning_Left3) == Turning_Left3) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Turning_Left4) == Turning_Left4) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Left5) == Turning_Left5) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Left6) == Turning_Left6) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Pivoting_Left) == Pivoting_Left) {
                nextState = Pivot_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Turning_Right1) == Turning_Right1) {
                nextState = Turning_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Right2) == Turning_Right2) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Turning_Right3) == Turning_Right3) {
                nextState = Turning_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Right4) == Turning_Right4) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Right5) == Turning_Right5) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Right6) == Turning_Right6) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Pivoting_Right1) == Pivoting_Right1) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Pivoting_Right2) == Pivoting_Right2) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Right_Corner) == Right_Corner) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Left_Corner == Left_Corner)) {
                nextState = Pivot_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Corner) == Corner) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case ES_TIMEOUT:
            // create the case statement for all other events that you are
            // interested in responding to. This one does a transition
            //nextState = Tape;
            //makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            break;

        default: // all unhandled events pass the event back up to the next level
            break;
        break;
    }

    case Turning_Left: // example of a state without a sub-statemachine
        switch (ThisEvent.EventType) {
        case ES_ENTRY:
            // this is where you would put any actions associated with the
            // entry to this state
            TurnLeft(speed);
            //ES_Timer_InitTimer(turningtimer, turningtimervalue);
            break;

        case ES_EXIT:
            // this is where you would put any actions associated with the
            // exit from this state
            break;

            case TAPE:
                //printf("jj");
                if ((ThisEvent.EventParam & Forwarding1) == Forwarding1) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Forwarding2) == Forwarding2) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Forwarding3) == Forwarding3) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Turning_Left1) == Turning_Left1) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Left2) == Turning_Left2) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Turning_Left3) == Turning_Left3) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Turning_Left4) == Turning_Left4) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Left5) == Turning_Left5) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Left6) == Turning_Left6) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Pivoting_Left) == Pivoting_Left) {
                nextState = Pivot_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Turning_Right1) == Turning_Right1) {
                nextState = Turning_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Right2) == Turning_Right2) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Turning_Right3) == Turning_Right3) {
                nextState = Turning_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Right4) == Turning_Right4) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Right5) == Turning_Right5) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Right6) == Turning_Right6) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Pivoting_Right1) == Pivoting_Right1) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Pivoting_Right2) == Pivoting_Right2) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Right_Corner) == Right_Corner) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Left_Corner == Left_Corner)) {
                nextState = Pivot_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Corner) == Corner) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case ES_TIMEOUT:
            // create the case statement for all other events that you are
            // interested in responding to. This one does a transition
            //nextState = Tape;
            //makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            break;

        default: // all unhandled events pass the event back up to the next level
            break;
        }
        break;
        
    case Turning_Right: // example of a state without a sub-statemachine
        switch (ThisEvent.EventType) {
        case ES_ENTRY:
            // this is where you would put any actions associated with the
            // entry to this state
            TurnRight(speed);
            //ES_Timer_InitTimer(turningtimer, turningtimervalue);
            break;

        case ES_EXIT:
            // this is where you would put any actions associated with the
            // exit from this state
            break;

            case TAPE:
                //printf("jj");
                if ((ThisEvent.EventParam & Forwarding1) == Forwarding1) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Forwarding2) == Forwarding2) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Forwarding3) == Forwarding3) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Turning_Left1) == Turning_Left1) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Left2) == Turning_Left2) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Turning_Left3) == Turning_Left3) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
                else if ((ThisEvent.EventParam & Turning_Left4) == Turning_Left4) {
                nextState = Turning_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Left5) == Turning_Left5) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Left6) == Turning_Left6) {
//                nextState = Turning_Left;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Pivoting_Left) == Pivoting_Left) {
                nextState = Pivot_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Turning_Right1) == Turning_Right1) {
                nextState = Turning_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Right2) == Turning_Right2) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Turning_Right3) == Turning_Right3) {
                nextState = Turning_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
//                else if ((ThisEvent.EventParam & Turning_Right4) == Turning_Right4) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Right5) == Turning_Right5) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//                else if ((ThisEvent.EventParam & Turning_Right6) == Turning_Right6) {
//                nextState = Turning_Right;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
                else if ((ThisEvent.EventParam & Pivoting_Right1) == Pivoting_Right1) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Pivoting_Right2) == Pivoting_Right2) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Right_Corner) == Right_Corner) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Left_Corner == Left_Corner)) {
                nextState = Pivot_Left;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if ((ThisEvent.EventParam & Corner) == Corner) {
                nextState = Pivot_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case ES_TIMEOUT:
            // create the case statement for all other events that you are
            // interested in responding to. This one does a transition
            //nextState = Tape;
           // makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            break;

        default: // all unhandled events pass the event back up to the next level
            break;
        }
        break;

    default: // all unhandled states fall into here
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        Run_AA_LineFollowing_SubHSM(EXIT_EVENT);   // <- rename to your own Run function
        CurrentState = nextState;
        Run_AA_LineFollowing_SubHSM(ENTRY_EVENT);  // <- rename to your own Run function
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

#ifdef LINE_FOLLOWINGSUBHSM_TEST // <-- change this name and define it in your MPLAB-X
                        //     project to run the test harness
#include <stdio.h>

void main(void)
{
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

#endif // LINE_FOLLOWINGSUBHSM_TEST
