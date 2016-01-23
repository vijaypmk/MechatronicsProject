/****************************************************************************
 Module
     ES_Configure.h
 Description
     This file contains macro definitions that are edited by the user to
     adapt the Events and Services framework to a particular application.
 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 01/15/12 10:03 jec      started coding
 *****************************************************************************/

#ifndef CONFIGURE_H
#define CONFIGURE_H



//defines for keyboard input
//#define USE_KEYBOARD_INPUT
//What State machine are we testing
//#define POSTFUNCTION_FOR_KEYBOARD_INPUT PostDagobotHSM

//define for TattleTale
#define USE_TATTLETALE

//uncomment to supress the entry and exit events
//#define SUPPRESS_EXIT_ENTRY_IN_TATTLE

/****************************************************************************/
// Name/define the events of interest
// Universal events occupy the lowest entries, followed by user-defined events
/****************************************************************************/
//This section lists the names of your events as macro'd list
//Give them unique names!
#define EVENT_NAMES(EVENT) \
    EVENT(ES_NO_EVENT) \
    EVENT(ES_ERROR)  /* used to indicate an error from the service */ \
    EVENT(ES_INIT)  /* used to transition from initial pseudo-state */ \
    EVENT(ES_ENTRY) /* used to enter a state*/ \
    EVENT(ES_EXIT) /* used to exit a state*/ \
    EVENT(ES_KEYINPUT)  /* used to signify a key has been pressed*/ \
    EVENT(ES_LISTEVENTS)  /* used to list events in keyboard input, does not get posted to fsm*/ \
    EVENT(ES_TIMEOUT)  /* signals that the timer has expired */ \
    EVENT(ES_TIMERACTIVE)  /* signals that a timer has become active */ \
    EVENT(ES_TIMERSTOPPED)  /* signals that a timer has stopped*/ \
    /* User-defined events start here */ \
    EVENT(TAPE) \
    EVENT(T_JUNCTION) \
    EVENT(BUMPED)  /* Bump sensors triggered*/ \
    EVENT(DONE_EVADING) \
    EVENT(PORTAL_ON) \
    EVENT(AMMO) \
    EVENT(NO_AMMO) \
    EVENT(PORTAL_OFF) \
    EVENT(CHANGE) \
    EVENT(ALIGNED) \
    EVENT(MISSED_T) \
    EVENT(FORCED) \
    EVENT(BUMP_CHECK) \
    EVENT(DONE_FIRING) \
    EVENT(SNIPED) \
    EVENT(PORTAL_MOVE) \
    EVENT(SWITCH_TO_KILL) \
   
     /*lower level evade state machine done */ \

// This turns the EVENT_NAMES list into an enum statement
// To see how it expands, right-click -> navigate -> View macro expansion
#define ENUM_FORM(STATE) STATE, //Enums are reprinted verbatim and comma'd
typedef enum {
    EVENT_NAMES(ENUM_FORM)
    NUMBEROFEVENTS,
} ES_EventTyp_t;

// This turns the EVENT_NAMES into a list of strings
// To see how it expands, right-click -> navigate -> View macro expansion
#define STRING_FORM(STATE) #STATE, //Strings are stringified and comma'd
static const char *EventNames[] = {
    EVENT_NAMES(STRING_FORM)
};

/****************************************************************************/
// This are the name of the Event checking funcion header file.
#define EVENT_CHECK_HEADER "DagobotFrameworkEvents.h"

/****************************************************************************/
// This is the list of event checking functions
#define EVENT_CHECK_LIST  CheckPortal//CheckLoader //CheckPortal//CheckLoader //CheckBumps//CheckTape//

/****************************************************************************/
// These are the definitions for the post functions to be executed when the
// correspnding timer expires. All 8 must be defined. If you are not using
// a timers, then you can use TIMER_UNUSED
#define TIMER_UNUSED ((pPostFunc)0)
#define TIMER0_RESP_FUNC PostTimerService
#define TIMER1_RESP_FUNC PostTimerService
//user modifiable timers start below here
#define TIMER2_RESP_FUNC PostDagobotHSM
#define TIMER3_RESP_FUNC TIMER_UNUSED
#define TIMER4_RESP_FUNC PostDagobotHSM //shootingtimer
#define TIMER5_RESP_FUNC PostTestBumpService //bumptimer
#define TIMER6_RESP_FUNC PostDagobotHSM    //ReverseTurningTimer
#define TIMER7_RESP_FUNC PostTestTapeService //tapetimer
#define TIMER8_RESP_FUNC PostTestBeaconDetectorService //IRtimer
#define TIMER9_RESP_FUNC PostDagobotHSM //pivotingtimer
#define TIMER10_RESP_FUNC PostDagobotHSM //turningtimer
#define TIMER11_RESP_FUNC PostDagobotHSM //wallhuggingtimer
#define TIMER12_RESP_FUNC PostDagobotHSM //portalsearchingtimer
#define TIMER13_RESP_FUNC PostDagobotHSM //ammofindtimer
#define TIMER14_RESP_FUNC PostDagobotHSM //reversingtimer
#define TIMER15_RESP_FUNC PostDagobotHSM //replungetimer


/****************************************************************************/
// Give the timer numbers symbolc names to make it easier to move them
// to different timers if the need arises. Keep these definitons close to the
// definitions for the response functions to make it easire to check that
// the timer number matches where the timer event will be routed

#define FANCY_DAGOBOT_TIMER 2 /*make sure this is enabled above and posting to the correct state machine*/


/****************************************************************************/
// The maximum number of services sets an upper bound on the number of
// services that the framework will handle. Reasonable values are 8 and 16
// HOWEVER: at this time only a value of 8 is supported.
#define MAX_NUM_SERVICES 8

/****************************************************************************/
// This macro determines that nuber of services that are *actually* used in
// a particular application. It will vary in value from 1 to MAX_NUM_SERVICES
#define NUM_SERVICES 6

/****************************************************************************/
// These are the definitions for Service 0, the lowest priority service
// every Events and Services application must have a Service 0. Further
// services are added in numeric sequence (1,2,3,...) with increasing
// priorities
// the header file with the public fuction prototypes
#ifdef DEV
#define SERV_0_HEADER "ES_TimerService.h"
#endif
// the name of the Init function
#define SERV_0_INIT InitTimerService
// the name of the run function
#define SERV_0_RUN RunTimerService
// How big should this service's Queue be?
#define SERV_0_QUEUE_SIZE 9

/****************************************************************************/
// These are the definitions for Service 1
#if NUM_SERVICES > 1
// the header file with the public fuction prototypes
#ifdef DEV
#define SERV_1_HEADER "ES_KeyboardInput.h"
#endif
// the name of the Init function
#define SERV_1_INIT InitKeyboardInput
// the name of the run function
#define SERV_1_RUN RunKeyboardInput
// How big should this services Queue be?
#define SERV_1_QUEUE_SIZE 9
#endif

// These are the definitions for Service 2
#if NUM_SERVICES > 2
// the header file with the public fuction prototypes
#define SERV_2_HEADER "DagobotHSM.h"
// the name of the Init function
#define SERV_2_INIT InitDagobotHSM
// the name of the run function
#define SERV_2_RUN RunDagobotHSM
// How big should this services Queue be?
#define SERV_2_QUEUE_SIZE 3
#endif



/****************************************************************************/
// These are the definitions for Service 3
#if NUM_SERVICES > 3
// the header file with the public fuction prototypes
#define SERV_3_HEADER "TestTapeService.h"
// the name of the Init function
#define SERV_3_INIT InitTestTapeService
// the name of the run function
#define SERV_3_RUN RunTestTapeService
// How big should this services Queue be?
#define SERV_3_QUEUE_SIZE 3
#endif

/****************************************************************************/
// These are the definitions for Service 4
#if NUM_SERVICES > 4
// the header file with the public fuction prototypes
#define SERV_4_HEADER "TestBumpService.h"
// the name of the Init function
#define SERV_4_INIT InitTestBumpService
// the name of the run function
#define SERV_4_RUN RunTestBumpService
// How big should this services Queue be?
#define SERV_4_QUEUE_SIZE 3
#endif

/****************************************************************************/
// These are the definitions for Service 5
#if NUM_SERVICES > 5
// the header file with the public fuction prototypes
#define SERV_5_HEADER "TestBeaconDetectorService.h"
// the name of the Init function
#define SERV_5_INIT InitTestBeaconDetectorService
// the name of the run function
#define SERV_5_RUN RunTestBeaconDetectorService
// How big should this services Queue be?
#define SERV_5_QUEUE_SIZE 3
#endif

/****************************************************************************/
// These are the definitions for Service 6
#if NUM_SERVICES > 6
// the header file with the public fuction prototypes
#define SERV_6_HEADER "TestService.h"
// the name of the Init function
#define SERV_6_INIT TestServiceInit
// the name of the run function
#define SERV_6_RUN TestServiceRun
// How big should this services Queue be?
#define SERV_6_QUEUE_SIZE 3
#endif

/****************************************************************************/
// These are the definitions for Service 7
#if NUM_SERVICES > 7
// the header file with the public fuction prototypes
#define SERV_7_HEADER "TestService.h"
// the name of the Init function
#define SERV_7_INIT TestServiceInit
// the name of the run function
#define SERV_7_RUN TestServiceRun
// How big should this services Queue be?
#define SERV_7_QUEUE_SIZE 3
#endif

/****************************************************************************/
// the name of the posting function that you want executed when a new
// keystroke is detected.
// The default initialization distributes keystrokes to all state machines
#define POST_KEY_FUNC ES_PostAll



/****************************************************************************/
// These are the definitions for the Distribution lists. Each definition
// should be a comma seperated list of post functions to indicate which
// services are on that distribution list.
#define NUM_DIST_LISTS 0
#if NUM_DIST_LISTS > 0
#define DIST_LIST0 PostDagobotFSM
#endif
#if NUM_DIST_LISTS > 1
#define DIST_LIST1 PostDagobotFSM
#endif
#if NUM_DIST_LISTS > 2
#define DIST_LIST2 PostDagobotFSM
#endif
#if NUM_DIST_LISTS > 3
#define DIST_LIST3 PostDagobotFSM
#endif
#if NUM_DIST_LISTS > 4
#define DIST_LIST4 PostDagobotFSM
#endif
#if NUM_DIST_LISTS > 5
#define DIST_LIST5 PostDagobotFSM
#endif
#if NUM_DIST_LISTS > 6
#define DIST_LIST6 PostDagobotFSM
#endif
#if NUM_DIST_LISTS > 7
#define DIST_LIST7 PostDagobotFSM
#endif



#endif /* CONFIGURE_H */