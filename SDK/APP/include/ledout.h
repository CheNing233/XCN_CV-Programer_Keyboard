/*
 * ledout.h
 *
 *  Created on: 2023Äê10ÔÂ10ÈÕ
 *      Author: 19156
 */

#ifndef APP_INCLUDE_LEDOUT_H_
#define APP_INCLUDE_LEDOUT_H_

#define LED_TX_HIGH 51
#define LED_TX_LOW 26
#define LED_TX_CIRCLE 80

#define LED_X 2
#define LED_C 1
#define LED_V 0
#define LED_CTRL 4
#define LED_SPACE 5
#define LED_BT 3


typedef enum _Board_LightState {
    Light_off,

    Light_Setting_In,
    Light_Setting_Slt_x,
    Light_Setting_Slt_c,
    Light_Setting_Slt_v,
    Light_Setting_Slt_ctrl,
    Light_Setting_Slt_space,

    Light_KeyHold_On,
    Light_KeyHold_Out,

} Board_LightState;

extern uint8_t LedOut_MainSW;

extern void LedOut_Init();

#endif /* APP_INCLUDE_LEDOUT_H_ */
