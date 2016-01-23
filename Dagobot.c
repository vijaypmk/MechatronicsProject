//Dagobot.c


#include "IO_Ports.h"
#include "RC_Servo.h"
#include "pwm.h"
#include "Dagobot.h"
#include "AD.h"
#include <stdio.h>
#include "LED.h"

//motor defines
#define LEFT_DIR PORTX03_LAT
#define RIGHT_DIR PORTX04_LAT

#define LEFT_DIR_TRIS PORTX03_TRIS
#define RIGHT_DIR_TRIS PORTX04_TRIS

#define LEFT_PWM PWM_PORTY10
#define RIGHT_PWM PWM_PORTY12

//tape sensor defines
#define LEFT_LEFT_TAPE PORTW04_BIT
#define LEFT_TAPE PORTW05_BIT
#define FRONT_TAPE PORTW07_BIT
#define RIGHT_TAPE PORTW03_BIT
#define RIGHT_RIGHT_TAPE PORTW06_BIT
#define BACK_TAPE PORTW08_BIT
#define LOADER_TAPE PORTZ04_BIT
#define LED PORTX08_LAT

//track wire sensor defines
#define LEFT_TRACK_WIRE PORTZ03_BIT

//bump sensor defines
#define FRONT_RIGHT_BUMPER PORTV05_BIT
#define FRONT_LEFT_BUMPER PORTV06_BIT

//beacon detector defines
#define BEACON_DETECTER PORTY07_BIT

//ball storage servo defines
#define LOADER RC_PORTZ08

#define DPRINT FALSE

void Dagobot_Init(void) {

    //set the control pins for the motors as output
    PWM_Init();
    PWM_SetFrequency(500);
    PWM_AddPins(LEFT_PWM | RIGHT_PWM);

    LEFT_DIR_TRIS = 0;
    RIGHT_DIR_TRIS = 0;

    //set direction
    LEFT_DIR = 0;
    RIGHT_DIR = 0;

    //set the control pins for tape sensors as input
    PORTW04_TRIS = 1;
    PORTW03_TRIS = 1;
    PORTW08_TRIS = 1;
    PORTW05_TRIS = 1;
    PORTW06_TRIS = 1;
    PORTW07_TRIS = 1;
    PORTZ04_TRIS = 1;
    PORTX08_TRIS = 0;

    //set up the control pins for bumper sensors as input
    PORTV05_TRIS = 1;
    PORTV06_TRIS = 1;

    //set up the control pins for beacon detector as input
    PORTY07_TRIS = 1;

    //set up the control pins for servo
    RC_Init();
    RC_AddPins(LOADER);
}

char Dagobot_RightPivot(char newSpeed) {
    Dagobot_LeftMtrSpeed(newSpeed + 0.25);
    Dagobot_RightMtrSpeed(-(newSpeed));
    return (SUCCESS);
}

//sets left motor speed
char Dagobot_LeftMtrSpeed(char newSpeed) {
    if ((newSpeed < -10) || (newSpeed > 10)) {
        return (ERROR);
    }
    if (newSpeed < 0) {
        LEFT_DIR = 0;
        newSpeed = newSpeed * (-1); // set speed to a positive value
    } else {
        LEFT_DIR = 1;
    }
    if (PWM_SetDutyCycle(LEFT_PWM, ((248*newSpeed)/AD_ReadADPin(BAT_VOLTAGE))*100) == ERROR) {
        return (ERROR);
    }
    return (SUCCESS);
}

//sets right motor speed
char Dagobot_RightMtrSpeed(char newSpeed) {
    if ((newSpeed < -10) || (newSpeed > 10)) {
        return (ERROR);
    }
    if (newSpeed < 0) {
        RIGHT_DIR = 0;
        newSpeed = newSpeed * (-1); // set speed to a positive value
    } else {
        RIGHT_DIR = 1;
    }
    if (PWM_SetDutyCycle(RIGHT_PWM, ((248*newSpeed)/AD_ReadADPin(BAT_VOLTAGE))*100) == ERROR) {
        return (ERROR);
    }
    return (SUCCESS);
}

//read all tape
unsigned char Dagobot_ReadTape(void) {
    unsigned char tape_state;
    tape_state = (!BACK_TAPE + ((!RIGHT_RIGHT_TAPE) << 1)+((!RIGHT_TAPE) << 2)+((!FRONT_TAPE) << 3)+((!LEFT_TAPE) << 4)+((!LEFT_LEFT_TAPE) << 5));
    return tape_state;
}


unsigned char Dagobot_ReadLineTape(void) {
    unsigned char tape_state;
    tape_state = (!RIGHT_TAPE + ((!FRONT_TAPE) << 1)+((!LEFT_TAPE) << 2));
    return tape_state;
}


//read LL tape
unsigned int Dagobot_ReadLeftLeftTape(void) {
    return AD_ReadADPin(LEFT_LEFT_TAPE);
}

//read L tape
unsigned int Dagobot_ReadLeftTape(void) {
    return AD_ReadADPin(LEFT_TAPE);
}

//read F tape
unsigned int Dagobot_ReadFrontTape(void) {
    return AD_ReadADPin(FRONT_TAPE);
}

//read R tape
unsigned int Dagobot_ReadRightTape(void) {
    return AD_ReadADPin(RIGHT_TAPE);
}

//read RR tape
unsigned int Dagobot_ReadRightRightTape(void) {
    return AD_ReadADPin(RIGHT_RIGHT_TAPE);
}

//read B tape
unsigned int Dagobot_ReadBackTape(void) {
    return !BACK_TAPE;
}

//read loader tape
unsigned char Dagobot_ReadLoaderTape(void) {
    return LOADER_TAPE;
}

//set tape LED
char Dagobot_SetLED(char c) {
    LED = c;
}

//read track wire sensor
unsigned char Dagobot_ReadLPortal(void) {
    return !LEFT_TRACK_WIRE;
}

//read all bumpers
unsigned char Dagobot_ReadBumpers(void) {
    unsigned char bump_state;
    bump_state = (FRONT_LEFT_BUMPER + ((FRONT_RIGHT_BUMPER) << 1));
    return bump_state;
}

//read front left bumper
unsigned int Dagobot_ReadFrontLeftBumper(void) {
    return  AD_ReadADPin(FRONT_LEFT_BUMPER);
}

//read front right bumper
unsigned int Dagobot_ReadFrontRightBumper(void) {
    return  AD_ReadADPin(FRONT_RIGHT_BUMPER);
}

//read beacon detecter
unsigned char Dagobot_ReadIR(void) {
    return !BEACON_DETECTER;
}

void debug(char blah[]) {
    if (DPRINT == TRUE) {
        printf("%s\n", blah);
    }
}

//set loader servo
unsigned char Dagobot_SetLoaderServo(unsigned short int position2) {
    if (position2 < 1000 || position2 > 2000)
        return ERROR;
    else {
        RC_SetPulseTime(LOADER, position2);
        return SUCCESS;
    }
}