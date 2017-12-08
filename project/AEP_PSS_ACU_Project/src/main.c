/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: main.c $
 * $Revision: version 1$
 * $Author: Habib Apez $
 * $Date: 2017-11- 22 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \main.c
    Main at APP in Scheduler.
    Window Lifter project main with Scheduler and State Machines.
*/
/*============================================================================*/
/* COPYRIGHT (C) CONTINENTAL AUTOMOTIVE 2014                                  */
/* AUTOMOTIVE GROUP, Interior Division, Body and Security                     */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*                                                                            */
/*============================================================================*/
/*============================================================================*/
/*                    REUSE HISTORY - taken over from                         */
/*============================================================================*/
/*  Author             |        Version     | FILE VERSION (AND INSTANCE)     */
/*----------------------------------------------------------------------------*/
/* Habib Apez          |          1         |   Initial version               */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: main.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "Common\Std_Types.h"                  // OK
#include "HAL\clock.c"                         // OK
#include "HAL\delays.c"                        // OK
#include "HAL\button.c"                        // OK
#include "HAL\segmentbar.c"                    // OK
#include "HAL\leds.c"                          // OK
#include "HAL\sensors.c"
#include "SERVICES\Interrupts\interrupts.c"    // OK
#include "SERVICES\Scheduler\SchM.c"           // OK
#include "SERVICES\Scheduler\SchM_Cfg.c"       // OK


/* Constants and types  */
/*============================================================================*/

/* Variables */
/*============================================================================*/

/* Private functions prototypes */
/*============================================================================*/
void SysTick_Handler(void);

/* Inline functions */
/*============================================================================*/

/* Private functions */
/*============================================================================*/
/**************************************************************
 *  Name                 : SystTick interruption
 *  Description          : Moves the Window upwards
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void SysTick_Handler(void){
  if ( NULL!= GlbSysTickCallback)
	  GlbSysTickCallback();
  // leds_ToggleBlueBoardLED();
}

/**************************************************************
 *  Name                 : main
 *  Description          : Implements the main function
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
 int main(void){
  clock_InitClock();
  delays_InitTimer();
  segmentbar_InitBar();
  button_InitButtons();
  leds_InitBoardLeds();
  leds_InitLeds();
  sensor_InitSensors();

  T_ULONG SensorReading = 0;

  for(;;){
    SensorReading = sensor_ReadDriverSeatBeltSensor();
    if(SensorReading >3750){			/* If result > 3.75V */
      leds_TurnOnUpLED();
      leds_TurnOffDownLED();
      leds_TurnOffAntipinchLED();
    }
    else if (SensorReading > 2500) { 	/* If result > 3.75V */
      leds_TurnOffUpLED();
      leds_TurnOnDownLED();
      leds_TurnOffAntipinchLED();
    }
    else if (SensorReading >1250) { 	/* If result > 3.75V */
      leds_TurnOffUpLED();
      leds_TurnOffDownLED();
      leds_TurnOnAntipinchLED();
    }
    else {
      leds_TurnOffUpLED();
      leds_TurnOffDownLED();
      leds_TurnOffAntipinchLED();
    }

  }

  for(;;) leds_ToggleBlueBoardLED();

  SchM_Init(&SchM_Config);	/* Scheduler Services Initialization */
  SchM_Start();		        /* Start Scheduler Services */

  for(;;){
    // Do nothing
  }

  return 0;
}

/* Exported functions */
/*============================================================================*/

 /* Notice: the file ends with a blank new line to avoid compiler warnings */
