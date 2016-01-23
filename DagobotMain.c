#include <xc.h>
#include <stdio.h>
#include "BOARD.h"
#include "serial.h"
#include "pwm.h"
#include "IO_Ports.h"
#include "RC_Servo.h"

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "Dagobot.h"
#include "AD.h"



void main(void)
{
    ES_Return_t ErrorType;

    BOARD_Init();
    // When doing testing, it is usefull to annouce just which program
    // is running.

    printf("Starting Dagobot State Machine \n");
    printf("using the 2nd Generation Events & Services Framework\n");
    printf("batt reading: %d\n", AD_ReadADPin(BAT_VOLTAGE));


    // Your hardware initialization function calls go here
    Dagobot_Init();
//    GentleRight(newspeed+0.8);
//    while(1);
    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    printf("Error type: %d\n",ErrorType);
    if (ErrorType == Success) {

        ErrorType = ES_Run();

    }
    //if we got to here, there was an error
    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer");
        break;
    case FailedInit:
        printf("Failed Initialization");
        break;
    default:
        printf("Other Failure: %d",ErrorType);
        break;
    }
    for (;;)
        ;

};

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/