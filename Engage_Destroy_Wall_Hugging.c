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
#include "Portal_DashSubHSM.h"
#include "Engage_Destroy_Wall_Hugging_SubHSM.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define LIST_OF_Engage_Destroy_Wall_Hugging_STATES(STATE) \
        STATE(Init_Engage_Destroy_Wall_Hugging) \
        STATE(Engage_Destroy_Bump_Checking) \
        STATE(Pivoting_Right_Engage_Destroy_WH) /*Make sure state names are unique in their hierachy*/ \
        STATE(Turning_Left_Engage_Destroy_WH)       \
        STATE(Stopping_Engage_Destroy_WH)       \
        STATE(Reversing_Engage_Destroy_WH)  \
        STATE(Reverse_Turning_Left_Engage_Destroy) \
        STATE(Adjusting_Left_Engage_Destroy_WH) \
        STATE(Sweep_Reverse_Turning_Left_Engage_Destroy) \
 

#define ENUM_FORM(STATE) STATE, //Enums are reprinted verbatim and comma'd

typedef enum {
    LIST_OF_Engage_Destroy_Wall_Hugging_STATES(ENUM_FORM)
} SubEngage_Destroy_Wall_Hugging_State_t;

#define STRING_FORM(STATE) #STATE, //Strings are stringified and comma'd
static const char *StateNames[] = {
    LIST_OF_Engage_Destroy_Wall_Hugging_STATES(STRING_FORM)
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

static SubEngage_Destroy_Wall_Hugging_State_t CurrentState = Init_Engage_Destroy_Wall_Hugging; // <- change name to match ENUM
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
uint8_t InitEngage_Destroy_Wall_Hugging_SubHSM(void) {
    ES_Event returnEvent;

    CurrentState = Init_Engage_Destroy_Wall_Hugging;
    returnEvent = RunEngage_Destroy_Wall_Hugging_SubHSM(INIT_EVENT);
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
ES_Event RunEngage_Destroy_Wall_Hugging_SubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    SubEngage_Destroy_Wall_Hugging_State_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack
    static int bump_count = 0, max_bump_count = 6;

    switch (CurrentState) {
        case Init_Engage_Destroy_Wall_Hugging: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                nextState = Engage_Destroy_Bump_Checking;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case Engage_Destroy_Bump_Checking: // in the first state, replace this with correct names
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        //                        debug("Here");
                        break;

                    case ES_EXIT:
                        // this is where you would put any actions associated with the
                        // exit from this state
                        break;

                    case BUMP_CHECK:
                        bump_count = bump_count + 1;
                        if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) == FRONT_LEFT_BUMP) {
                            //hit left front bump
                            nextState = Reversing_Engage_Destroy_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & FRONT_RIGHT_BUMP) == FRONT_RIGHT_BUMP) {
                            //hit left front bump
                            nextState = Reversing_Engage_Destroy_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if ((ThisEvent.EventParam & FRONT_BUMPS) == FRONT_BUMPS) {
                            //hit left front bump
                            nextState = Reversing_Engage_Destroy_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
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
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;


        case Reversing_Engage_Destroy_WH:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // this is where you would put any actions associated with the
                    // entry to this state
                    //                    ReverseLeft(speed * 1.2); //reverse right to fiz
                    StraightReverse(speed);
                    //                    debug("Reversing Left");
                    ES_Timer_InitTimer(turningreversingtimer, 700);  //375
                    break;

                case ES_EXIT:
                    // this is where you would put any actions associated with the
                    // exit from this state
                    ES_Timer_StopTimer(turningreversingtimer);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == turningreversingtimer) {
                        nextState = Pivoting_Right_Engage_Destroy_WH;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;


        case Pivoting_Right_Engage_Destroy_WH: // in the first state, replace this with correct names
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        // this is where you would put any actions associated with the
                        // entry to this state
                        PivotRight(speed);
                        //                        debug("Pivoting Right");
                        //                        StraightForward(bumpspeed);
                        ES_Timer_InitTimer(pivotingtimer, 800);   //1200 //800 //400//300
                        break;

                    case ES_EXIT:
                        // this is where you would put any actions associated with the
                        // exit from this state
                        ES_Timer_StopTimer(pivotingtimer);
                        break;


                    case ES_KEYINPUT:
                        // this is an example where the state does NOT transition
                        // do things you need to do in this state
                        // event consumed
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == pivotingtimer) {
                            nextState = Turning_Left_Engage_Destroy_WH;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            ES_Timer_StopTimer(pivotingtimer);
                        }
                        // create the case statement for all other events that you are
                        // interested in responding to.

                        break;

                    default: // all unhandled events pass the event back up to the next level
                        break;
                }
            }
            break;


        case Turning_Left_Engage_Destroy_WH: // example of a state without a sub-statemachine

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(wallhuggingtimer, 1200); //800 // oh shit missed the corner
                    // this is where you would put any actions associated with the
                    // entry to this state
                    //                    GentleLeft(speed * 1.2);
//                    TurnLeft(speed);
                    ArcLeft(10);
                    break;

                case ES_TIMEOUT:
                    if(ThisEvent.EventParam == wallhuggingtimer){
                        BloodyHellTurnLeft(speed);
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case BUMPED:
                    bump_count = bump_count + 1;
                    if (((ThisEvent.EventParam & FRONT_LEFT_BUMP) == FRONT_LEFT_BUMP) && bump_count < max_bump_count) {
                        //hit left front bump
                        nextState = Reversing_Engage_Destroy_WH;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (((ThisEvent.EventParam & FRONT_BUMPS) == FRONT_BUMPS) && bump_count < max_bump_count) {
                        //hit left front bump
                        nextState = Reversing_Engage_Destroy_WH;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (((ThisEvent.EventParam & FRONT_RIGHT_BUMP) == FRONT_RIGHT_BUMP) && bump_count < max_bump_count) {
                        //hit left front bump
                        nextState = Reversing_Engage_Destroy_WH;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (((ThisEvent.EventParam & FRONT_LEFT_BUMP) == FRONT_LEFT_BUMP) && bump_count >= max_bump_count) {
                        //hit left front bump
                        bump_count = 0;
                        nextState = Sweep_Reverse_Turning_Left_Engage_Destroy;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (((ThisEvent.EventParam & FRONT_BUMPS) == FRONT_BUMPS) && bump_count >= max_bump_count) {
                        //hit left front bump
                        bump_count = 0;
                        nextState = Sweep_Reverse_Turning_Left_Engage_Destroy;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (((ThisEvent.EventParam & FRONT_RIGHT_BUMP) == FRONT_RIGHT_BUMP) && bump_count >= max_bump_count) {
                        //hit left front bump
                        bump_count = 0;
                        nextState = Sweep_Reverse_Turning_Left_Engage_Destroy;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_EXIT:

                    break;

                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;


        case Sweep_Reverse_Turning_Left_Engage_Destroy:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // this is where you would put any actions associated with the
                    // entry to this state
                    TurnLeft(-(speed));
                    ES_Timer_InitTimer(turningreversingtimer, 5000); //3000
                    break;

                case ES_EXIT:
                    // this is where you would put any actions associated with the
                    // exit from this state
                    ES_Timer_StopTimer(turningreversingtimer);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == turningreversingtimer) {
                        nextState = Turning_Left_Engage_Destroy_WH;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
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
        RunEngage_Destroy_Wall_Hugging_SubHSM(EXIT_EVENT);
        CurrentState = nextState;
        RunEngage_Destroy_Wall_Hugging_SubHSM(ENTRY_EVENT);
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/