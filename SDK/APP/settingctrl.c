/*
 * settingctrl.c
 *
 *  Created on: 2023Äê10ÔÂ24ÈÕ
 *      Author: 19156
 */

#include <config.h>
#include <usercfg.h>
#include <keyin.h>
#include <protocol.h>
#include "ledout.h"
#include "motorout.h"

uint8_t is_setting_state = FALSE;

uint16_t SettingCtrl_Scan(){

    // SWITCH USB/BLE
    if (((Keymap & (0x01 << MAP_ENTER)) > 0) && ((Keymap_o & (0x01 << MAP_ENTER)) == 0)) {
        // push

        switch(Protocol_SW){
            case Board_Use_USB:
                ProtoCtrl_Act_BLE();
                break;
            case Board_Use_BLE:
                ProtoCtrl_Act_USB();
                break;
        }

        Keyin_Reset_All();

        is_setting_state = FALSE;
        Motor_Block_LightShock();
        return 0;
    }

    // BACK
    if (((Keymap & (0x01 << MAP_CTRL)) > 0) && ((Keymap_o & (0x01 << MAP_CTRL)) == 0)) {
        // push

        Keyin_Reset_All();

        is_setting_state = FALSE;
        Motor_Block_LightShock();
        return 0;
    }

    // X - LED SW
    if (((Keymap & (0x01 << MAP_X)) > 0) && ((Keymap_o & (0x01 << MAP_X)) == 0)) {
        // push

        if(LedOut_MainSW){
            LedOut_MainSW = FALSE;
        } else {
            LedOut_MainSW = TRUE;
        }

        Keyin_Reset_All();

        is_setting_state = FALSE;
        Motor_Block_LightShock();
        return 0;
    }

    // C - Motor SW
    if (((Keymap & (0x01 << MAP_C)) > 0) && ((Keymap_o & (0x01 << MAP_C)) == 0)) {
        // push

        if(MotorOut_MainSW){
            MotorOut_MainSW = FALSE;
        } else {
            MotorOut_MainSW = TRUE;
        }

        Keyin_Reset_All();

        is_setting_state = FALSE;
        Motor_Block_LightShock();
        return 0;
    }

    return 0;
}


