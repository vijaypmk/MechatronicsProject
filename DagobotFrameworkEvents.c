#include <BOARD.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DagobotFrameworkEvents.h"
#include "Dagobot.h"
#include "TestTapeService.h"
#include<stdio.h>


#define DARK_THRESHOLD 234
#define LIGHT_THRESHOLD 88

uint8_t CheckBumps(void)
{
  uint8_t returnVal = FALSE;
  static int lastBumpState = 0;
  int currentBumpState;
  ES_Event thisEvent;

  // check the bumpers
  currentBumpState = Dagobot_ReadBumpers();
  if (currentBumpState != lastBumpState) { //event detected
    thisEvent.EventType = BUMPED;
    thisEvent.EventParam = (uint16_t) currentBumpState;
    PostTestBumpService(thisEvent);
    returnVal = TRUE;
    lastBumpState = currentBumpState;
  }
  return returnVal;
}


uint8_t CheckTape(void)
{
  uint8_t returnVal = FALSE;
  static unsigned char lastTapeState = 0;
  unsigned char currentTapeState;
  ES_Event thisEvent;
  currentTapeState = Dagobot_ReadTape();
  if (currentTapeState != lastTapeState) { //event detected
    thisEvent.EventType = TAPE;
    thisEvent.EventParam = (uint16_t) currentTapeState;
    PostTestTapeService(thisEvent);
    returnVal = TRUE;
    lastTapeState = currentTapeState;
  }
  return returnVal;
}

//Ball Loaded
uint8_t CheckLoader(void)
{
  uint8_t returnVal = FALSE;
  static int lastLoadState = 0;
  int currentLoadState;
  ES_Event thisEvent;
  currentLoadState = Dagobot_ReadLoaderTape();
  if (currentLoadState != lastLoadState ) { //event detected
    thisEvent.EventType = AMMO;
    thisEvent.EventParam = currentLoadState;
    PostDagobotHSM(thisEvent);  //post event loaded to service
    returnVal = TRUE;
    lastLoadState = currentLoadState;
  }

  //if unloaded and track wire ON set state machine to Dash Portal State or go back to searching level (Original SM)
  //if unloaded move randomely in large circles for 20 sec, if track wire not ON go back to searching level
}

//Portal Checking
uint8_t CheckPortal(void)
{
  uint8_t returnVal = FALSE;
  static int lastPortalState = 0;
  int currentPortalState;
  ES_Event thisEvent;
  // check the bumpers
  currentPortalState = Dagobot_ReadLPortal();
  if (currentPortalState != lastPortalState) { //event detected
    thisEvent.EventType = PORTAL_ON;
    thisEvent.EventParam = currentPortalState;
    PostDagobotHSM(thisEvent);  //post event loaded to service
    returnVal = TRUE;
    lastPortalState = currentPortalState;
  }

  //if unloaded and track wire ON set state machine to Dash Portal State or go back to searching level (Original SM)
  //if unloaded move randomely in large circles for 20 sec, if track wire not ON go back to searching level
}


uint8_t CheckSniper(void)
{
  uint8_t returnVal = FALSE;
  static int lastSniperState = 0;
  int currentSniperState;
  ES_Event thisEvent;
  // check the bumpers
  currentSniperState = Dagobot_ReadIR();
  if (currentSniperState != lastSniperState) { //event detected
    thisEvent.EventType = SNIPED;
    thisEvent.EventParam =  currentSniperState;
    PostDagobotHSM(thisEvent);
    returnVal = TRUE;
    lastSniperState = currentSniperState;
  }
  return returnVal;
}

