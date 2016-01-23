/*
 * File: DagobotHSM.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Dagobot file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that 
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is another template file for the SubHSM's that is slightly differet, and
 * should be used for all of the subordinate state machines (flat or heirarchical)
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 16/Sep/2013
 */

#ifndef HSM_Dagobot_H  // <- This should be changed to your own guard on both
#define HSM_Dagobot_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
#include "Dagobot.h"


/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

//defines for motors
#define MotorRatio 1.3
#define MotorRatioR 1




#define FullStop() Dagobot_LeftMtrSpeed(0);Dagobot_RightMtrSpeed(0)

#define StraightForward(x) Dagobot_LeftMtrSpeed(x); Dagobot_RightMtrSpeed((x*MotorRatio));
#define GentleLeft(x) Dagobot_LeftMtrSpeed(x); Dagobot_RightMtrSpeed(x*MotorRatio*1.1);
#define TurnLeft(x) Dagobot_LeftMtrSpeed(0);Dagobot_RightMtrSpeed(x*MotorRatio);
#define PivotLeft(x) Dagobot_LeftMtrSpeed(-(x));Dagobot_RightMtrSpeed(x*MotorRatio);
//#define BloodyHellTurnLeft(x) Dagobot_LeftMtrSpeed(x*.65*MotorRatio);Dagobot_RightMtrSpeed((x*1.5));
#define BloodyHellTurnLeft(x) Dagobot_LeftMtrSpeed(x*.35*MotorRatio);Dagobot_RightMtrSpeed((x*1.3));
#define GentleRight(x) Dagobot_LeftMtrSpeed(x*1.45); Dagobot_RightMtrSpeed((x*MotorRatio)); // left 1.35
#define TurnRight(x) Dagobot_LeftMtrSpeed(x);Dagobot_RightMtrSpeed(0);
#define PivotRight(x) Dagobot_LeftMtrSpeed((x));Dagobot_RightMtrSpeed((-x*MotorRatio));
#define StraightReverse(x) Dagobot_LeftMtrSpeed(-(x));Dagobot_RightMtrSpeed(-(x*MotorRatio));
#define LeftReverse(x) Dagobot_LeftMtrSpeed(-(x*.75));Dagobot_RightMtrSpeed(-((x*MotorRatio*1.1)));
#define ArcLeft(x) Dagobot_LeftMtrSpeed(speed*.6); Dagobot_RightMtrSpeed(speed*MotorRatio);



#define SlowPivotRight(x) Dagobot_LeftMtrSpeed((x*MotorRatio+1));Dagobot_RightMtrSpeed((-x*MotorRatioR));
#define SharpReverseLeft(x)  Dagobot_LeftMtrSpeed(-(x-.2)*MotorRatio);Dagobot_RightMtrSpeed(-((x*2)*MotorRatioR));//Dagobot_RightMtrSpeed(-((x*1.4)*MotorRatioR));//Dagobot_RightMtrSpeed(-((x+.9)*MotorRatioR));
#define PivotRight_WH(x) Dagobot_LeftMtrSpeed(x*MotorRatio*2.3);Dagobot_RightMtrSpeed(-x*2.3);
#define PivotLeft_WH(x) Dagobot_LeftMtrSpeed(-(x*MotorRatio*2.3));Dagobot_RightMtrSpeed(x*MotorRatioR*2.3);
#define BloodyHellTurnRight(x) Dagobot_LeftMtrSpeed(x*MotorRatio);Dagobot_RightMtrSpeed(x*.55);
#define SharpReverseRight(x) Dagobot_LeftMtrSpeed(-((x*1.5)*MotorRatio)); Dagobot_RightMtrSpeed(-(x*0.6));


//defines for bumps
#define FRONT_BUMPS      0x03
#define FRONT_LEFT_BUMP  0x01
#define FRONT_RIGHT_BUMP 0x02
#define REAR_LEFT_BUMP   0x04
#define REAR_RIGHT_BUMP  0x08
#define REAR_BUMPS       0x12


//defines for tapes
#define Forwarding1 0b000001
#define Forwarding2 0b001001
#define Forwarding3 0b001000
#define Pivoting_Left1 0b011001 //needs to be checked
#define Left_Corner 0b110001
#define Pivoting_Right1 0b001101 //needs to be checked
#define Pivoting_Right2 0b110110
#define Right_Corner 0b000111
#define Turning_Left1 0b100000
#define Turning_Left2 0b101000
#define Turning_Left3 0b011000
#define Turning_Left4 0b001000
#define Turning_Left5 0b100001
#define Turning_Left6 0b010001
#define Turning_Right1 0b000010
#define Turning_Right2 0b000100
#define Turning_Right3 0b001100
#define Turning_Right4 0b001010
#define Turning_Right5 0b000011
#define Turning_Right6 0b000101
#define Corner 0b100010     
#define T_Middle 0b011101
#define T_Left 0b111000
#define T_Right 0b001110


//defines for timers
#define bumptimer 5
#define bumptimervalue 5

#define tapetimer 7
#define tapetimervalue 5

#define IRtimer 8
#define IRtimervalue 5

#define pivotingtimer 9
#define pivotingtimervalue 580//350 //290
#define left90value 1150//1200//340 //320
#define right90value 1050//380//490//510 //700

#define turningtimer 10
#define turningtimervalue 700

#define wallhuggingtimer 11
#define wallhuggingtimervalue 10000

#define portalsearchingtimer 12
#define portalsearchingtimervalue 10000

#define ammofindtimer 13
#define ammofindtimervalue 4000

#define reversingtimer 14
#define reversingtimervalue 480
#define reversingfromwallvalue 880 //820//500
#define forwardstowardswallvalue 1000
#define forwardsparallelwallvalue 860//850//580//560 //850
#define forwardsparallellongwallvalue 2216 //2200 //2130 //1300 //1340 //1320

#define replungetimer 15
#define replungetimervalue 1000

#define turningreversingtimer 6
#define turningreversingtimervalue 350

#define shootingtimer 4
#define shootingtimervalue 4000


//defines for speed
#define speed 8 //12/3 n
#define newspeed 3
#define reversingspeed 4.5
#define bumpspeed 4.7
#define tspeed 5
/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/
// typedefs for the states, which are used for the internal definition and also for
// the return of the query function.
// A preprocessor trick is used to make a list of strings alongside an enum list. To see the result,
// Rightclick -> Navigate -> view macro expansion
// Use unique state names!
#define LIST_OF_HSM_STATES(STATE)\
        STATE(InitHState) /*We typically use this as the InitState*/ \
        STATE(Acquiring_Ammo)       \
        STATE(Engage_Destroy)  \
        STATE(Portal) \

#define ENUM_FORM(STATE) STATE, //Enums are reprinted verbatim and comma'd

typedef enum {
    LIST_OF_HSM_STATES(ENUM_FORM)
} DagobotState_t;

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function InitDagobotHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunDagobotFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitDagobotHSM(uint8_t Priority);


/**
 * @Function PostDagobotHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostDagobotHSM(ES_Event ThisEvent);


/**
 * @Function QueryDagobotHSM(void)
 * @param none
 * @return Current state of the state machine
 * @brief This function is a wrapper to return the current state of the state
 *        machine. Return will match the ENUM above. Remember to rename to
 *        something appropriate, and also to rename the DagobotState_t to your
 *        correct variable name.
 * @author J. Edward Carryer, 2011.10.23 19:25 */
DagobotState_t QueryDagobotHSM(void);

/**
 * @Function RunDagobotHSM(ES_Event ThisEvent)
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
ES_Event RunDagobotHSM(ES_Event ThisEvent);

#endif /* HSM_Dagobot_H */

