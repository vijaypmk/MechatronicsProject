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
        STATE(Checking) /*Make sure state names are unique in their hierachy*/ \
        STATE(Reversing)       \
        STATE(Turning_Right_AC)  \
        STATE(Turning_Left_AC)  \
        STATE(Find_Next_T)  \
        STATE(Stopping_AC) \
        STATE(Reverse_Adjusting_Right) \
        STATE(Adjusting_Right_AC) \
        STATE(Reverse_Turning_Left) \
        STATE(Pivoting_Right_AC) \
        STATE(Pivoting_Left_AC) \
        STATE(Reversing_AC) \
        STATE(Forwarding_AC) \

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
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

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

    ES_Tattle(); // trace call stack
    ES_Event Tcontrol;

    static int aligning_start_time, aligning_end_time;
    static int aligning_difference_time = 0;
    static int  back_tape_flag = 0;

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
                        //PivotRight(newspeed);
                        break;

                    case ES_EXIT:
                        break;

                    case FORCED:
                        nextState = Checking;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        //                        ThisEvent.EventParam = ThisEvent.EventParam;
                        break;


                    case ES_TIMEOUT:
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case Checking:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {

                    case ES_ENTRY:
                         PivotRight(speed*1.2);//(speed*.5);
                        //                        TurnRight(speed);
                        //                        StraightForward(speed);
                        //                        ES_Timer_InitTimer(replungetimer, 300);
                        break;

                    case ES_EXIT:
                        break;

                    case TAPE:
                        if ((ThisEvent.EventParam & 0x01) == 0x01) { // B
                            printf("\nback on\n");
                            aligning_start_time = ES_Timer_GetTime();
                            back_tape_flag = 1;
                            int i;
                            for(i = 0; i < 100000; i++)
                            {
                                asm("nop");
                            }
                            //                            nextState = Pivoting_Right_AC;
                            //                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if (((ThisEvent.EventParam & 0b000001) == 0b000000) && back_tape_flag)   { // Back tape off T

                            aligning_end_time = ES_Timer_GetTime();
                            FullStop();
                            printf("\nback tape off\n");
                            int i;
                            for(i = 0; i < 100000; i++)
                            {
                                asm("nop");
                            }
                            aligning_difference_time = aligning_end_time - aligning_start_time;
//                            printf("\n\naligning_diff_time %d\n", aligning_difference_time);
                            nextState = Pivoting_Left_AC;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }//                        if ((ThisEvent.EventParam & 0b110000) == 0b110000) { // LL, L: if miss most of the stem/land on T top
                            //                            nextState = Pivoting_Right_AC;
                            //                            makeTransition = TRUE;
                            //                            ThisEvent.EventType = ES_NO_EVENT;
                            //                        }
                            //                        else if ((ThisEvent.EventParam & 0b111100) == 0b111100) { // LL, L,F, R: if hit T stem head-on
                            //                            nextState = Turning_Right_AC;
                            //                            makeTransition = TRUE;
                            //                            ThisEvent.EventType = ES_NO_EVENT;
                            //                        } else if ((ThisEvent.EventParam & 0b100000) == 0b100000) { // LL entry
                            //                            nextState = Turning_Left_AC;
                            //                            makeTransition = TRUE;
                            //                            ThisEvent.EventType = ES_NO_EVENT;
                            //                        }
                        else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        //                        else if ((ThisEvent.EventParam & T_Left) == T_Left) {
                        //                            nextState = Pivoting_Right;
                        //                            makeTransition = TRUE;
                        //                            ThisEvent.EventType = ES_NO_EVENT;
                        //                        } else if ((ThisEvent.EventParam & T_Right) == T_Right) {
                        //                            nextState = Pivoting_Left;
                        //                            makeTransition = TRUE;
                        //                            ThisEvent.EventType = ES_NO_EVENT;
                        //                        }
                        break;
                    case ES_TIMEOUT:
                        //                         nextState = Pivoting_Right_AC;
                        //                            makeTransition = TRUE;
                        //                            ThisEvent.EventType = ES_NO_EVENT;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case Pivoting_Right_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        PivotRight(tspeed * 1);
                        ES_Timer_InitTimer(replungetimer, 900);
                        break;

                        //                    case TAPE:
                        //                        if ((ThisEvent.EventParam & 0x01) == 0x01) { // B
                        //                            nextState = Reverse_Adjusting_Right;
                        //                            makeTransition = TRUE;
                        //                            ThisEvent.EventType = ES_NO_EVENT;
                        //                        }
                        //                        else {
                        //                            ThisEvent.EventType = ES_NO_EVENT;
                        //                        }
                        //                        break;


                    case ES_EXIT:
                        FullStop();
                        break;

                    case ES_TIMEOUT:
                        //                        nextState = Lost;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        if (ThisEvent.EventParam == replungetimer) {
                            nextState = Reverse_Adjusting_Right;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    default:
                        break;
                }
            }
            break;

        case Pivoting_Left_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        PivotLeft_WH(speed * .7);
                        int spintime = aligning_difference_time / 2;
                        //                        printf("\n\n%dcheck spin time\n", spintime);
                        ES_Timer_InitTimer(replungetimer, spintime);
                        break;

                    case ES_EXIT:
                        FullStop();
                        break;

                    case ES_TIMEOUT:
                        //                        nextState = Lost;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        if (ThisEvent.EventParam == replungetimer) {
                            FullStop();
                            //                            printf("\n\ncheck\n");
                            nextState = Reverse_Adjusting_Right;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    default:
                        break;
                }
            }
            break;

        case Turning_Left_AC:
            //ThisEvent = Run_AA_LineFollowing_SubHSM(ThisEvent); // run sub-state machine for this state
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        TurnLeft(speed);
                        break;

                    case TAPE:
                        if ((ThisEvent.EventParam & 0b000100) == 0b000100) { // R
                            nextState = Turning_Right_AC; //TODO: straight on
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case ES_EXIT:
                        FullStop();
                        break;

                    case ES_TIMEOUT:
                        //                        ThisEvent.EventType = ES_NO_EVENT;

                    default: break;
                }
            }
            break;

        case Turning_Right_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        TurnRight(speed);
                        break;
                        //        case BUMPED:
                        //                nextState = Wall_Hugging;
                        //                makeTransition = TRUE;
                        //                ThisEvent.EventType = ES_NO_EVENT;
                        //                break;

                    case TAPE:
                        if ((ThisEvent.EventParam & 0x01) == 0x01) { // B
                            nextState = Reverse_Adjusting_Right;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;


                    case ES_EXIT:
                        FullStop();
                        break;

                    case ES_TIMEOUT:
                        //                        nextState = Lost;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default: break;
                }
            }
            break;

        case Stopping_AC:
            FullStop();
            break;

        case Reversing_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        StraightReverse(speed * 1.3);
                        ES_Timer_InitTimer(ammofindtimer, ammofindtimervalue);
                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(ammofindtimer);
                        ES_Timer_StopTimer(portalsearchingtimer);
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == ammofindtimer) {
                            ES_Timer_InitTimer(portalsearchingtimer, 600);
                            StraightForward(speed);
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if (ThisEvent.EventParam == portalsearchingtimer) {
                            FullStop();
                            Tcontrol.EventType = AMMO;
                            Tcontrol.EventParam = 0;
                            ThisEvent.EventType = ES_NO_EVENT;
                            PostDagobotHSM(Tcontrol);
                        }

                        break;

                    default:
                        break;
                }
            }
            break;

        case Forwarding_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        StraightForward(speed);
                        break;

                    case TAPE:
                        if ((ThisEvent.EventParam & 0b001000) == 0b000000) { // Front off the T
                            nextState = Reversing_AC;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case ES_EXIT:
                        break;

                    case ES_TIMEOUT:
                        break;

                    default:
                        break;
                }
            }
            break;

        case Reverse_Adjusting_Right:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        //                        GentleLeft(-6 - .3); // backwards left = front of robot pivoting right
                        GentleRight(-6 - .3);
                        ES_Timer_InitTimer(replungetimer, replungetimervalue);
                        break;

                        //                    case TAPE:
                        //                        if ((ThisEvent.EventParam & 0b111110) == 0b000000) { // F
                        //                            nextState = Stopping_AC;
                        //                            makeTransition = TRUE;
                        //                            ThisEvent.EventType = ES_NO_EVENT;
                        //                        } else {
                        //                            ThisEvent.EventType = ES_NO_EVENT;
                        //                        }
                        //                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(replungetimer);
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == replungetimer) {
                            nextState = Forwarding_AC;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    default:
                        break;
                }
            }
            break;

        case Adjusting_Right_AC:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        GentleRight(speed);
                        break;

                    case TAPE:
                        if ((ThisEvent.EventParam & 0b011100) == 0b011100) { // L, C, R
                            nextState = Reverse_Adjusting_Right;
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

        case Reverse_Turning_Left:
            if (ThisEvent.EventType != ES_NO_EVENT) { // An event is still active
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        //ES_Timer_InitTimer(pivotingtimer, pivotingtimervalue);
                        ReverseLeft(speed); // fiz thinks this means reverse right // previously 5
                        ES_Timer_InitTimer(ammofindtimer, ammofindtimervalue);
                        break;

                        //                    case TAPE:
                        //                        if ((ThisEvent.EventParam & 0b011100) == 0b011100){ // L, C, R
                        //                            nextState = Reverse_Adjusting_Right;
                        //                            makeTransition = TRUE;
                        //                            ThisEvent.EventType = ES_NO_EVENT;
                        //                        }
                        //                        break;
                        //
                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == ammofindtimer) {
                            Tcontrol.EventType = MISSED_T;
                            Tcontrol.EventParam = 0;
                            PostDagobotHSM(Tcontrol);
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        //                        else if (plungecount == 4){
                        //                            debug("Oh, shit!");
                        //                            nextState = Stopping_AC;
                        //                            makeTransition = TRUE;
                        //                            ThisEvent.EventType = ES_NO_EVENT;
                        //                            //TODO: Deal with later!
                        //                            // post event to pop into higher state
                        //                        }
                        break;

                    case ES_EXIT:
                        ES_Timer_StopTimer(ammofindtimer);
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


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/


/*******************************************************************************
 * TEST HARNESS                                                                *
 ******************************************************************************/

#ifdef ALIGNCOLLECT_SUBHSM_TEST // <-- change this name and define it in your MPLAB-X
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

#endif // ALIGNCOLLECT_SUBHSM_TEST
