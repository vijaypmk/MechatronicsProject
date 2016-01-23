/* 
 * File:   DagobotFrameworkEvents.h
 * Author: mdunne
 *
 * Created on January 3, 2013, 4:53 PM
 */

#ifndef DAGOBOTFRAMEWORKEVENTS_H
#define	DAGOBOTFRAMEWORKEVENTS_H


typedef enum {
    WHITE, DARK
} lightstate_t;

//uint8_t CheckLightLevel(void);
uint8_t CheckBumps(void);
uint8_t CheckTape(void);
uint8_t CheckLoader(void);
uint8_t CheckPortal(void);
uint8_t CheckSniper(void);



#endif	/* DAGOBOTFRAMEWORKEVENTS_H */

