//Dagobot.h

#ifndef DAGOBOT_H
#define DAGOBOT_H

#include "BOARD.H"

//Global Variables

//None

//Function Prototypes

/**
 * @Function Dagobot_Init(void)
 * @param None.
 * @return None.
 * @brief  Performs all the initialization necessary for Dagobot. this includes initializing
 * the PWM module, the A/D converter(not needed), the data directions on some pins, and
 * setting the initial motor directions.
 * @note  None.
 * @author Team Dagobot, 2015.11.13 */
void Dagobot_Init(void);

char Dagobot_RightPivot(char newSpeed);

/**
 * @Function Dagobot_LeftMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -10 and 10 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Team Dagobot, 2015.11.13 */
char Dagobot_LeftMtrSpeed(char newSpeed);

/**
 * @Function Dagobot_RightMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -10 and 10 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Team Dagobot, 2015.11.13 */
char Dagobot_RightMtrSpeed(char newSpeed);

/**
 * @Function Dagobot_ReadTape(void)
 * @param None.
 * @return 8-bit value representing all six tapes in following order: left corner, left center, center, right center, right corner, back
 * @brief  Returns the state of all 6 tapes
 * @author Team Dagobot, 2015.11.13 */
unsigned char Dagobot_ReadTape(void);

unsigned char Dagobot_ReadLineTape(void);

/**
 * @Function Dagobot_ReadLeftCornerTape(void)
 * @param None.
 * @return bit value of tape 
 * @brief  Returns the state of the left corner tape
 * @author Team Dagobot, 2015.11.13 */
unsigned int Dagobot_ReadLeftLeftTape(void);

/**
 * @Function Dagobot_ReadLeftCenterTape(void)
 * @param None.
 * @return bit value of tape 
 * @brief  Returns the state of the left center tape
 * @author Team Dagobot, 2015.11.13 */
unsigned int Dagobot_ReadLeftTape(void);

/**
 * @Function Dagobot_ReadCenterTape(void)
 * @param None.
 * @return bit value of tape 
 * @brief  Returns the state of the center tape
 * @author Team Dagobot, 2015.11.13 */
unsigned int Dagobot_ReadFrontTape(void);

/**
 * @Function Dagobot_ReadRightCenterTape(void)
 * @param None.
 * @return bit value of tape 
 * @brief  Returns the state of the right center tape
 * @author Team Dagobot, 2015.11.13 */
unsigned int Dagobot_ReadRightTape(void);

/**
 * @Function Dagobot_ReadRightCornerTape(void)
 * @param None.
 * @return bit value of tape 
 * @brief  Returns the state of the right corner tape
 * @author Team Dagobot, 2015.11.13 */
unsigned int Dagobot_ReadRightRightTape(void);

/**
 * @Function Dagobot_ReadBackTape(void)
 * @param None.
 * @return bit value of tape 
 * @brief  Returns the state of the back tape
 * @author Team Dagobot, 2015.11.13 */
unsigned int Dagobot_ReadBackTape(void);

/**
 * @Function Dagobot_ReadLoaderTape(void)
 * @param None.
 * @return bit value of tape 
 * @brief  Returns the state of the loader tape
 * @author Team Dagobot, 2015.11.13 */
unsigned char Dagobot_ReadLoaderTape(void);

/**
 * @Function Dagobot_ReadLPortal(void)
 * @param None.
 * @return bit value of left portal 
 * @brief  Returns the state of the left track wire
 * @author Team Dagobot, 2015.11.13 */
unsigned char Dagobot_ReadLPortal(void);

/**
 * @Function Dagobot_ReadRPortal(void)
 * @param None.
 * @return bit value of right portal 
 * @brief  Returns the state of the right track wire
 * @author Team Dagobot, 2015.11.13 */
unsigned char Dagobot_ReadRPortal(void);

/**
 * @Function Dagobot_ReadBumpers(void)
 * @param None.
 * @return 4-bit value representing all four bumpers in following order: front left,front right, rear left, rear right
 * @brief  Returns the state of all 4 bumpers
 * @author Team Dagobot, 2015.11.13 */
unsigned char Dagobot_ReadBumpers(void);

/**
 * @Function Dagobot_ReadFrontLeftBumper(void)
 * @param None.
 * @return bit value of bumper
 * @brief  Returns the state of the front left bumper
 * @author Team Dagobot, 2015.11.13 */
unsigned int Dagobot_ReadFrontLeftBumper(void);


/**
 * @Function Dagobot_ReadFrontRightBumper(void)
 * @param None.
 * @return bit value of bumper
 * @brief  Returns the state of the front right bumper
 * @author Team Dagobot, 2015.11.13 */
unsigned int Dagobot_ReadFrontRightBumper(void);

/**
 * @Function Dagobot_ReadRearLeftBumper(void)
 * @param None.
 * @return bit value of bumper
 * @brief  Returns the state of the rear left bumper
 * @author Team Dagobot, 2015.11.13 */
unsigned char Dagobot_ReadRearLeftBumper(void);

/**
 * @Function Dagobot_ReadRearRightBumper(void)
 * @param None.
 * @return bit value of bumper
 * @brief  Returns the state of the rear right bumper
 * @author Team Dagobot, 2015.11.13 */
unsigned char Dagobot_ReadRearRightBumper(void);

/**
 * @Function Dagobot_ReadIR(void)
 * @param None.
 * @return bit value of beacon detecter
 * @brief  Returns the state of the beacon detecter
 * @author Team Dagobot, 2015.11.13 */
unsigned char Dagobot_ReadIR(void);

void debug(char blah[]);

/**
 * @Function Dagobot_SetSolenoid1(void)
 * @param None.
 * @return None
 * @brief  Activates Solenoid 1
 * @author Team Dagobot, 2015.11.13 */
//unsigned char Dagobot_SetSolenoid1(void);

/**
 * @Function Dagobot_RelSolenoid1(void)
 * @param None.
 * @return None
 * @brief  Releases Solenoid 1
 * @author Team Dagobot, 2015.11.13 */
//unsigned char Dagobot_RelSolenoid1(void);

/**
 * @Function Dagobot_SetSolenoid2(void)
 * @param None.
 * @return None
 * @brief  Activates Solenoid 2
 * @author Team Dagobot, 2015.11.13 */
//unsigned char Dagobot_SetSolenoid2(void);

/**
 * @Function Dagobot_RelSolenoid1(void)
 * @param None.
 * @return None
 * @brief  Releases Solenoid 2
 * @author Team Dagobot, 2015.11.13 */
//unsigned char Dagobot_RelSolenoid2(void);

/**
 * @Function Dagobot_SetPing1High(void)
 * @param None.
 * @return None
 * @brief  Sets Trigger Pin of Ping 1 Sensor High
 * @author Team Dagobot, 2015.11.13 */
//unsigned char Dagobot_SetPing1High(void);

/**
 * @Function Dagobot_SetPing1Low(void)
 * @param None.
 * @return None
 * @brief  Sets Trigger Pin of Ping 1 Sensor Low
 * @author Team Dagobot, 2015.11.13 */
//unsigned char Dagobot_SetPing1Low(void);

/**
 * @Function Dagobot_SetPing2High(void)
 * @param None.
 * @return None
 * @brief  Sets Trigger Pin of Ping 2 Sensor High
 * @author Team Dagobot, 2015.11.13 */
//unsigned char Dagobot_SetPing2High(void);

/**
 * @Function Dagobot_SetPing2Low(void)
 * @param None.
 * @return None
 * @brief  Sets Trigger Pin of Ping 2 Sensor Low
 * @author Team Dagobot, 2015.11.13 */
//unsigned char Dagobot_SetPing1Low(void);

/**
 * @Function Dagobot_ReadPing1(void)
 * @param None.
 * @return bit value of Ping 1
 * @brief  Returns the value of ECHO pin of Ping 1 Sensor
 * @author Team Dagobot, 2015.11.13 */
//unsigned char Dagobot_ReadPing1(void);

/**
 * @Function Dagobot_ReadPing2(void)
 * @param None.
 * @return bit value of Ping 2
 * @brief  Returns the value of ECHO pin of Ping 2 Sensor
 * @author Team Dagobot, 2015.11.13 */
//unsigned char Dagobot_ReadPing2(void);

/**
 * @Function Dagobot_SetSaberServo(unsigned short int position)
 * @param position- A value between 1000 and 2000.
 * @return None
 * @brief  Sets the position of the servo based on param
 * @author Team Dagobot, 2015.11.13 */
unsigned char Dagobot_SetSaberServo(unsigned short int position1);

/**
 * @Function Dagobot_SetLoaderServo(unsigned short int position)
 * @param position- A value between 1000 and 2000.
 * @return None
 * @brief  Sets the position of the servo based on param
 * @author Team Dagobot, 2015.11.13 */
unsigned char Dagobot_SetLoaderServo(unsigned short int position2);


#endif