/* 
 * File:   Application.h
 * Author: Alielden
 *
 * Created on September 9, 2023, 7:04 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section :  Includes */

#include "Ecua_Layer/LED/ecu_led.h"
#include "Ecua_Layer/BUTTON/ecu_button.h"
#include "Ecua_Layer/RELAY/ecu_relay.h"
#include "Ecua_Layer/DC_MOTOR/ecu_dc_motor.h"
#include "Ecua_Layer/7_SEGMENT/ecu_seven_seg.h"
#include "Ecua_Layer/KEYPAD/ecu_keypad.h"
#include "Ecua_Layer/LCD/ecu_lcd.h"
#include "Mca_Layer/INTERRUPT/hal_external_interrupt.h"
#include "Mca_Layer/INTERRUPT/hal_internal_interrupt.h"
#include "Mca_Layer/INTERRUPT/hal_interrupt_manager.h"
#include "Mca_Layer/INTERRUPT/hal_interrupt_config.h"
#include "Mca_Layer/EEPROM/hal_eeprom.h"
#include "Mca_Layer/ADC/hal_adc.h"
#include <xc.h>


 /* Section : Macros */
#define _XTAL_FREQ 8000000


#define ENTER_PASSWORD   0x01
#define CHANGE_PASSWORD  0x02

/* Section : Macros Functions */


/* Section : Data type Declaration */


/* Section : Functions Declaration */

void APPLICATION_INTIALIZE(void);

void ADC_APP_ISR(void);

#endif	/* APPLICATION_H */

