/*
 * File: TestTapeServiceService.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * TestTapeService file to set up a simple service to work with the Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "DagobotHSM.h"
#include "Dagobot.h"
#include "TestTapeService.h"
#include<stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */


static uint8_t MyPriority;
static unsigned char currentTapeState[100];
static uint8_t ind = 0;
static uint8_t index = 0;
static uint8_t loadindex = 0;
static unsigned char lastTapeState = 0x3F;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTestTapeServiceService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTestTapeServiceService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTestTapeService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    Dagobot_SetLED(1); //setting LEDS for digital

    for (ind = 0; ind < 100; ind++)
        currentTapeState[ind] = 0x00;

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;

    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTestTapeServiceService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTestTapeService(ES_Event ThisEvent) {
    //    printf("postTestTapeService() running\n");
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTestTapeServiceService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */




ES_Event RunTestTapeService(ES_Event ThisEvent) {
    //    printf("RunTestTapeService() running\n");

    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
    ES_Event LoaderEvent;
    //    if(ThisEvent.EventType == ES_INIT)
    //    {
    ////        printf("ee");
    //    }
    //            static uint8_t left_left_tapeArrayON[] = {0,0,0,0,0,0,0,0};
    //            static uint8_t left_tapeArrayON[] = {0,0,0,0,0,0,0,0};
    //            static uint8_t front_tapeArrayON[] = {0,0,0,0,0,0,0,0};
    //            static uint8_t right_tapeArrayON[] = {0,0,0,0,0,0,0,0};
    //            static uint8_t right_right_tapeArrayON[] = {0,0,0,0,0,0,0,0};
    //            static uint8_t back_tapeArrayON[] = {0,0,0,0,0,0,0,0};
    //
    //            //initializing array for LED off
    //            static uint8_t left_left_tapeArrayOFF[] = {0,0,0,0,0,0,0,0};
    //            static uint8_t left_tapeArrayOFF[] = {0,0,0,0,0,0,0,0};
    //            static uint8_t front_tapeArrayOFF[] = {0,0,0,0,0,0,0,0};
    //            static uint8_t right_tapeArrayOFF[] = {0,0,0,0,0,0,0,0};
    //            static uint8_t right_right_tapeArrayOFF[] = {0,0,0,0,0,0,0,0};
    //            static uint8_t back_tapeArrayOFF[] = {0,0,0,0,0,0,0,0};
    //    //
    //    //        //initializing Sums for each arrays
    //            static int sumleft_left_tapeON = 0, sumleft_tapeON = 0, sumfront_tapeON = 0, sumright_tapeON = 0, sumright_right_tapeON = 0, sumback_tapeON = 0;
    //            static int sumleft_left_tapeOFF = 0, sumleft_tapeOFF = 0, sumfront_tapeOFF = 0, sumright_tapeOFF = 0, sumright_right_tapeOFF = 0, sumback_tapeOFF = 0;
    //    //
    //            //initializing averages for each arrays
    //            static int averageleft_left_tapeON = 0, averageleft_tapeON = 0, averagefront_tapeON = 0, averageright_tapeON = 0, averageright_right_tapeON = 0, averageback_tapeON = 0;
    //            static int averageleft_left_tapeOFF = 0, averageleft_tapeOFF = 0, averagefront_tapeOFF = 0, averageright_tapeOFF = 0, averageright_right_tapeOFF = 0, averageback_tapeOFF = 0;
    //    //
    //    //    //initializing tape variables
    //    //    static int left_left_tape_ON = 0;
    //    //    static int left_tape_ON = 0;
    //    //    static int front_tape_ON = 0;
    //    //    static int right_tape_ON = 0;
    //    //    static int right_right_tape_ON = 0;
    //    //    static int back_tape_ON = 0;
    //    //
    //    //    //initializing tape variables
    //    //    static int left_left_tape_OFF = 0;
    //    //    static int left_tape_OFF = 0;
    //    //    static int front_tape_OFF = 0;
    //    //    static int right_tape_OFF = 0;
    //    //    static int right_right_tape_OFF = 0;
    //    //    static int back_tape_OFF = 0;
    //    //
    //    //    //initializing differences for each value
    //        static int differenceleft_left_tape = 0, differenceleft_tape = 0, differencefront_tape = 0, differenceright_tape = 0, differenceright_right_tape = 0, differenceback_tape = 0;
    //    ////
    //        static uint8_t index = 0, check = 1, i;
    //        static int lastleft_left_tape = 0x00, lastleft_tape = 0x00, lastfront_tape = 0x00, lastright_tape = 0x00, lastright_right_tape = 0x00, lastback_tape = 0x00;
    //        static int currentleft_left_tape, currentleft_tape, currentfront_tape, currentright_tape, currentright_right_tape, currentback_tape, WHITE_THRESHOLD = 650, BLACK_THRESHOLD = 300;
    //        static int currentTapeState;
    //        static int lastTapeState = 0x00;
    //
    //    //initializing differences for each arrays
    ////    static int differenceleft_left_tapeArrayON = 0, differenceleft_tapeArrayON = 0, differencefront_tapeArrayON = 0, differenceright_tapeArrayON = 0, differenceright_right_tapeArrayON = 0, differenceback_tapeArrayON = 0;
    ////    static int differenceleft_left_tapeArrayOFF = 0, differenceleft_tapeArrayOFF = 0, differencefront_tapeArrayOFF = 0, differenceright_tapeArrayOFF = 0, differenceright_right_tapeArrayOFF = 0, differenceback_tapeArrayOFF = 0;
    //
    //    static uint8_t index = 0, check = 1, i;
    //    static int lastleft_left_tape = 0, lastleft_tape = 0, lastfront_tape = 0, lastright_tape = 0, lastright_right_tape = 0, lastback_tape = 0;
    //    static int currentleft_left_tape, currentleft_tape, currentfront_tape, currentright_tape, currentright_right_tape, currentback_tape, WHITE_THRESHOLD = 1022, BLACK_THRESHOLD = 1000;
    //    static int currentTapeState;
    //    static int lastTapeState = 0x00;
    //
    //    /********************************************
    //     in here you write your service code
    //     *******************************************/
    //     ES_Timer_SetTimer(tapetimer, tapetimervalue); // Tape sensor check every 10ms
    //        ES_Timer_StartTimer(tapetimer);
    //    currentTapeState = Dagobot_ReadTape();
    if (ThisEvent.EventType == ES_TIMEOUT)// only respond to ES_Init
    {
        //                printf("BLAH\n");
        ////        printf("check = %d\n", check);
        ES_Timer_InitTimer(tapetimer, tapetimervalue);
        //
        //
        //        //initializing array for LED on
        //        // No hardware initialization or single time setups, those
        //        // go in the init function above.
        //        //
        //        // This section is used to reset service for some reason
        //
        //                switch (check) {
        //                    case 1:
        //        //                printf("case 1\n");
        //                        //read OFF values
        ////                        left_left_tape_OFF = Dagobot_ReadLeftLeftTape();
        ////                       //printf("left_left_tape_OFF1 = %d\n",left_left_tape_OFF);
        ////                        left_tape_OFF = Dagobot_ReadLeftTape();
        ////                        front_tape_OFF = Dagobot_ReadFrontTape();
        ////                        right_tape_OFF = Dagobot_ReadRightTape();
        ////                        right_right_tape_OFF = Dagobot_ReadRightRightTape();
        ////                        back_tape_OFF = Dagobot_ReadBackTape();
        //
        //                        left_left_tapeArrayOFF[index] = Dagobot_ReadLeftLeftTape();
        //                         //printf("left_left_tapeArrayOFF[index] = %d\n",left_left_tapeArrayOFF[index]);
        //                        left_tapeArrayOFF[index] = Dagobot_ReadLeftTape();
        //                        front_tapeArrayOFF[index] = Dagobot_ReadFrontTape();
        //                        right_tapeArrayOFF[index] = Dagobot_ReadRightTape();
        //                        right_right_tapeArrayOFF[index] = Dagobot_ReadRightRightTape();
        //                        back_tapeArrayOFF[index] = Dagobot_ReadBackTape();
        //        //
        //        //
        //                        //summing each array
        //                        sumleft_left_tapeOFF = sumleft_left_tapeOFF + left_left_tapeArrayOFF[index];
        //                        sumleft_tapeOFF = sumleft_tapeOFF + left_tapeArrayOFF[index];
        //                        sumfront_tapeOFF = sumfront_tapeOFF + front_tapeArrayOFF[index];
        //                        sumright_tapeOFF = sumright_tapeOFF + right_tapeArrayOFF[index];
        //                        sumright_right_tapeOFF = sumright_right_tapeOFF + right_right_tapeArrayOFF[index];
        //                        sumback_tapeOFF = sumback_tapeOFF + back_tapeArrayOFF[index];
        //
        //        //                //averaging
        //                        averageleft_left_tapeOFF = sumleft_left_tapeOFF >> 3;
        //                        //printf("averageleft_left_tapeOFF = %d\n",averageleft_left_tapeOFF);
        //                        averageleft_tapeOFF = sumleft_tapeOFF >> 3;
        //                        averagefront_tapeOFF = sumfront_tapeOFF >> 3;
        //                        averageright_tapeOFF = sumright_tapeOFF >> 3;
        //                        averageright_right_tapeOFF = sumright_right_tapeOFF >> 3;
        //                        averageleft_tapeOFF = sumleft_tapeOFF >> 3;
        //
        //
        //                        //set LED on
        //                        Dagobot_SetLED(1);
        //                        check = 2; //changing to next state
        //                        break;
        //
        //                    case 2:
        //        //                printf("case 2\n");
        //                        //read OFF values
        //
        ////                        left_left_tape_ON = Dagobot_ReadLeftLeftTape();
        ////                        //printf("left_left_tape_ON1 = %d\n",left_left_tape_ON);
        ////                        left_tape_ON = Dagobot_ReadLeftTape();
        ////                        front_tape_ON = Dagobot_ReadFrontTape();
        ////                        right_tape_ON = Dagobot_ReadRightTape();
        ////                        right_right_tape_ON = Dagobot_ReadRightRightTape();
        ////                        back_tape_ON = Dagobot_ReadBackTape();
        //
        //                        left_left_tapeArrayON[index] = Dagobot_ReadLeftLeftTape();
        //                        left_tapeArrayON[index] = Dagobot_ReadLeftTape();
        //                        front_tapeArrayON[index] = Dagobot_ReadFrontTape();
        //                        right_tapeArrayON[index] = Dagobot_ReadRightTape();
        //                        right_right_tapeArrayON[index] = Dagobot_ReadRightRightTape();
        //                        back_tapeArrayON[index] = Dagobot_ReadBackTape();
        //
        //
        //        //                //summing each array
        //                        sumleft_left_tapeON = sumleft_left_tapeON + left_left_tapeArrayON[index];
        //                        sumleft_tapeON = sumleft_tapeON + left_tapeArrayON[index];
        //                        sumfront_tapeON = sumfront_tapeON + front_tapeArrayON[index];
        //                        sumright_tapeON = sumright_tapeON + right_tapeArrayON[index];
        //                        sumright_right_tapeON = sumright_right_tapeON + right_right_tapeArrayON[index];
        //                        sumback_tapeON = sumback_tapeON + back_tapeArrayON[index];
        //
        //                        //averaging
        //                        averageleft_left_tapeON = sumleft_left_tapeON >> 3;
        //                        averageleft_tapeON = sumleft_tapeON >> 3;
        //                        averagefront_tapeON = sumfront_tapeON >> 3;
        //                        averageright_tapeON = sumright_tapeON >> 3;
        //                        averageright_right_tapeON = sumright_right_tapeON >> 3;
        //                        averageleft_tapeON = sumleft_tapeON >> 3;
        //
        //
        //                        index = ((index++) % 8 - 1); //increment index
        //                        check = 1; //changing state
        //
        //                        //set LED off
        //                        Dagobot_SetLED(0);
        //                        break;
        //
        //        //            default:
        //        //                printf("default case\n");
        //        //                break;
        //                }
        //
        //                /*//averaging
        //                for(i = 0; i < 8; i++)
        //                {
        //                 sumleft_left_tapeON = sumleft_left_tapeON + left_left_tapeArrayON[i];
        //                 sumleft_tapeON = sumleft_tapeON + left_tapeArrayON[i];
        //                 sumcentertapeON = sumcentertapeON + centertapeArrayON[i];
        //                 sumright_tapeON = sumright_tapeON + right_tapeArrayON[i];
        //                 sumrightcornertapeON = sumrightcornertapeON + rightcornertapeArrayON[i];
        //                 sumback_tapeON = sumback_tapeON + back_tapeArrayON[i];
        //
        //                 sumleft_left_tapeOFF = sumleft_left_tapeOFF + left_left_tapeArrayOFF[i];
        //                 sumleft_tapeOFF = sumleft_tapeOFF + left_tapeArrayOFF[i];
        //                 sumcentertapeOFF = sumcentertapeOFF + centertapeArrayOFF[i];
        //                 sumright_tapeOFF = sumright_tapeOFF + right_tapeArrayOFF[i];
        //                 sumrightcornertapeOFF = sumrightcornertapeOFF + rightcornertapeArrayOFF[i];
        //                 sumback_tapeOFF = sumback_tapeOFF + back_tapeArrayOFF[i];
        //                }*/
        //
        //
        //
        //                differenceleft_left_tape = averageleft_left_tapeON - averageleft_left_tapeOFF;
        //                differenceleft_tape = averageleft_tapeON - averageleft_tapeOFF;
        //                differencefront_tape = averagefront_tapeON - averagefront_tapeOFF;
        //                differenceright_tape = averageright_tapeON - averageright_tapeOFF;
        //                differenceright_right_tape = averageright_right_tapeON - averageright_right_tapeOFF;
        //                differenceback_tape = averageback_tapeON - averageback_tapeOFF;
        //
        //                //take ON vs OFF difference (noise)
        ////                differenceleft_left_tape = left_left_tape_ON - left_left_tape_OFF;
        ////        //        printf("differenceleft_left_tape: %d\n", differenceleft_left_tape);
        ////                differenceleft_tape = left_tape_ON - left_tape_OFF;
        ////                differencefront_tape = front_tape_ON - front_tape_OFF;
        ////                differenceright_tape = right_tape_ON - right_tape_OFF;
        ////                differenceright_right_tape = right_right_tape_ON - right_right_tape_OFF;
        ////                differenceback_tape = back_tape_ON - back_tape_OFF;
        //
        //        //        BOOL flag = FALSE;
        //
        //
        //                //check whether tape reading light or dark
        //
        //                if (differenceleft_left_tape < BLACK_THRESHOLD) {
        //        //            printf("differenceleft_left_tape1 = %d\n",differenceleft_left_tape);
        //        //            printf("left_left_tape_OFF1 = %d\n",left_left_tape_OFF);
        //        //            printf("left_left_tape_ON1 = %d\n",left_left_tape_ON);
        //                    currentleft_left_tape = 1;
        //                    lastleft_left_tape = currentleft_left_tape;
        //                } else if (differenceleft_left_tape > WHITE_THRESHOLD) {
        //        //            printf("differenceleft_left_tape2 = %d\n",differenceleft_left_tape);
        //        //            printf("left_left_tape_OFF2 = %d\n",left_left_tape_OFF);
        //        //            printf("left_left_tape_ON2 = %d\n",left_left_tape_ON);
        //                    currentleft_left_tape = 0;
        //                    lastleft_left_tape = currentleft_left_tape;
        //                } else {
        //                    currentleft_left_tape = lastleft_left_tape;
        //                }
        //
        //                //setting left center tape output
        //
        //                if (differenceleft_tape < BLACK_THRESHOLD) {
        //        //            printf("differenceleft_tape1 = %d\n",differenceleft_tape);
        //        //            printf("left_tape_OFF1 = %d\n",left_tape_OFF);
        //        //            printf("left_tape_ON1 = %d\n",left_tape_ON);
        //                    currentleft_tape = 1;
        //                    lastleft_tape = currentleft_tape;
        //                } else if (differenceleft_tape > WHITE_THRESHOLD) {
        //        //                  printf("differenceleft_tape2 = %d\n",differenceleft_tape);
        //        //            printf("left_tape_OFF2 = %d\n",left_tape_OFF);
        //        //            printf("left_tape_ON2 = %d\n",left_tape_ON);
        //                    currentleft_tape = 0;
        //                    lastleft_tape = currentleft_tape;
        //                } else {
        //                    currentleft_tape = lastleft_tape;
        //                }
        //
        //                //setting center tape output
        //
        //                if (differencefront_tape < BLACK_THRESHOLD) {
        //        //            printf("differencefront_tape1 = %d\n",differencefront_tape);
        //        //            printf("front_tape_OFF1 = %d\n",front_tape_OFF);
        //        //            printf("front_tape_ON1 = %d\n",front_tape_ON);
        //                    currentfront_tape = 1;
        //                    lastfront_tape = currentfront_tape;
        //                } else if (differencefront_tape > WHITE_THRESHOLD) {
        //        //            printf("differencefront_tape2 = %d\n",differencefront_tape);
        //        //            printf("front_tape_OFF2 = %d\n",front_tape_OFF);
        //        //            printf("front_tape_ON2 = %d\n",front_tape_ON);
        //                    currentfront_tape = 0;
        //                    lastfront_tape = currentfront_tape;
        //                } else {
        //                    currentfront_tape = lastfront_tape;
        //                }
        //
        //                //setting right center tape output
        //
        //                if (differenceright_tape < BLACK_THRESHOLD) {
        //        //            printf("differenceright_tape1 = %d\n",differenceright_tape);
        //        //            printf("right_tape_OFF1 = %d\n",right_tape_OFF);
        //        //            printf("right_tape_ON1 = %d\n",right_tape_ON);
        //                    currentright_tape = 1;
        //                    lastright_tape = currentright_tape;
        //                } else if (differenceright_tape > WHITE_THRESHOLD) {
        //        //            printf("differenceright_tape2 = %d\n",differenceright_tape);
        //        //            printf("right_tape_OFF2 = %d\n",right_tape_OFF);
        //        //            printf("right_tape_ON2 = %d\n",right_tape_ON);
        //                    currentright_tape = 0;
        //                    lastright_tape = currentright_tape;
        //                } else {
        //                    currentright_tape = lastright_tape;
        //                }
        //
        //                //setting right corner tape output
        //
        //                if (differenceright_right_tape < BLACK_THRESHOLD) {
        //        //            printf("differenceright_right_tape1 = %d\n",differenceright_right_tape);
        //        //            printf("right_right_tape_OFF1 = %d\n",right_right_tape_OFF);
        //        //            printf("right_right_tape_ON1 = %d\n",right_right_tape_ON);
        //                    currentright_right_tape = 1;
        //                    lastright_right_tape = currentright_right_tape;
        //                } else if (differenceright_right_tape > WHITE_THRESHOLD) {
        //        //            printf("differenceright_right_tape2 = %d\n",differenceright_right_tape);
        //        //            printf("right_right_tape_OFF2 = %d\n",right_right_tape_OFF);
        //        //            printf("right_right_tape_ON2 = %d\n",right_right_tape_ON);
        //                    currentright_right_tape = 0;
        //                    lastright_right_tape = currentright_right_tape;
        //                } else {
        //                    currentright_right_tape = lastright_right_tape;
        //                }
        //
        //
        //                //setting back tape output
        //
        //                if (differenceback_tape < BLACK_THRESHOLD) {
        //                    currentback_tape = 1;
        //                    lastback_tape = currentback_tape;
        //        //            printf("differenceback_tape1 = %d\n",differenceback_tape);
        //        //            printf("back_tape_OFF1 = %d\n",back_tape_OFF);
        //        //            printf("back_tape_ON1 = %d\n",back_tape_ON);
        //                } else if (differenceback_tape > WHITE_THRESHOLD) {
        //        //            printf("differenceback_tape2 = %d\n",differenceback_tape);
        //        //            printf("back_tape_OFF2 = %d\n",back_tape_OFF);
        //        //            printf("back_tape_ON2 = %d\n",back_tape_ON);
        //                    currentback_tape = 0;
        //                    lastback_tape = currentback_tape;
        //                } else {
        //        //            printf("differenceback_tape3 = %d\n",differenceback_tape);
        //        //            printf("back_tape_OFF3 = %d\n",back_tape_OFF);
        //        //            printf("back_tape_ON3 = %d\n",back_tape_ON);
        //                    currentback_tape = lastback_tape;
        //                }
        //
        //        //        printf("%d\n",differenceleft_left_tape);
        //        //        printf("%x\n",currentleft_left_tape);
        //        //        printf("%x\n",currentleft_tape);
        //        //        printf("%x\n",currentfront_tape);
        //        //        printf("%x\n",currentright_tape);
        //        //        printf("%x\n",currentright_right_tape);
        //        //        printf("%x\n",currentback_tape);
        //
        //                currentTapeState = (currentback_tape + ((currentright_right_tape) << 1)+((currentright_tape) << 2)+((currentfront_tape) << 3)+((currentleft_tape) << 4)+((currentleft_left_tape) << 5));
        //
        //              currentTapeState = Dagobot_ReadTape();
        //
        //               //printf("0x%x\n",currentTapeState);
        //                if (currentTapeState != lastTapeState) { //event detected
        //                    //printf("differenceleft_left_tape%d\n",differenceback_tape);
        //                    ThisEvent.EventType = TAPE;
        //                    ThisEvent.EventParam = currentTapeState;
        //                    lastTapeState = currentTapeState;
        //                    PostDagobotHSM(ReturnEvent);
        //                }
        //            }



        //Digital Read
        currentTapeState[index] = Dagobot_ReadTape();
        //        printf("0x%x", currentTapeState);
        BOOL flag = FALSE, loadFlag = FALSE;
        int i, count = 0;
        if ((currentTapeState[index] != lastTapeState)) {
            for (i = 1; i < 100; i++) {
                if (currentTapeState[i - 1] != currentTapeState[index]) {
                                        flag = TRUE;
                    count++;

                    lastTapeState = currentTapeState[index];
                } else {
//                    flag = FALSE;
                    count--;
                }
            }
        }
        if (count > 10) {
            ThisEvent.EventType = TAPE;
            ThisEvent.EventParam = currentTapeState[index];
            PostDagobotHSM(ThisEvent);
        }

    }
    index++, loadindex++;
    if (index == 100) index = 0;
    if (loadindex == 5) loadindex = 0;
    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/


/*******************************************************************************
 * TEST HARNESS                                                                *
 ******************************************************************************/

#ifdef TESTTAPESERVICE_TEST // <-- change this name and define it in your MPLAB-X
//     project to run the test harness
#include <stdio.h>

void main(void) {
    ES_Return_t ErrorType;
    BOARD_Init();
    // When doing testing, it is useful to annouce just which program
    // is running.

    printf("Starting the Simple Service Test Harness \r\n");
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

#endif // TEMPLATESERVICE_TEST