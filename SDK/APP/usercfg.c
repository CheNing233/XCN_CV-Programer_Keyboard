/*
 * usercfg.c
 *
 *  Created on: 2023Äê9ÔÂ24ÈÕ
 *      Author: 19156
 */

#include "config.h"
#include "usercfg.h"
#include "hiddev.h"

// USB
//usercfg UserCfg_RAM = {
//        .Init_Flag = 233,
//
//        .Proto_FreshState_Interval = 1600,
//        .Proto_USBBuffer_PushInterval = 8,
//        .Proto_BLEBuffer_PushInterval = 16,
//
//        .KeyIn_Debouncing_Sampling_Interval = 4,
//        .KeyIn_Debouncing_DelayCircle_Cnt = 1,
//
//        .USB_UploadRate = 0x01, .BLE_Uplaod_PackCnt = 16
//
//};


usercfg UserCfg_RAM = {
        .Init_Flag = 233,

        .Proto_FreshState_Interval = 1600,
        .Proto_USBBuffer_PushInterval = 8,
        .Proto_BLEBuffer_PushInterval = 8,

        .KeyIn_Debouncing_Sampling_Interval = 4,
        .KeyIn_Debouncing_DelayCircle_Cnt = 1,

        .USB_UploadRate = 0x01, .BLE_Uplaod_PackCnt = 16

};

keycfg KeyCfg_RAM_X = {
        .Init_Flag = 233,

        .Set_Keys = { 0x00, 0x00, HID_KEYBOARD_X, 0x00, 0x00, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 0,
        .SwitchKeys_DelayCnt = 0,

        .NextPos_Relative = 0,
        .Reset_Flag = FALSE
};

keycfg KeyCfg_RAM_C = {
        .Init_Flag = 233,

        .Set_Keys = { 0x00, 0x00, 0x00, HID_KEYBOARD_C , 0x00, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 0,
        .SwitchKeys_DelayCnt = 0,

        .NextPos_Relative = 0,
        .Reset_Flag = FALSE
};

keycfg KeyCfg_RAM_V = {
        .Init_Flag = 233,

        .Set_Keys = { 0x00, 0x00, 0x00, 0x00, HID_KEYBOARD_V, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 0,
        .SwitchKeys_DelayCnt = 0,

        .NextPos_Relative = 0,
        .Reset_Flag = FALSE
};

keycfg KeyCfg_RAM_CTRL = {
        .Init_Flag = 233,

        .Set_Keys = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 0,
        .SwitchKeys_DelayCnt = 0,

        .NextPos_Relative = 0,
        .Reset_Flag = FALSE
};

keycfg KeyCfg_RAM_ENTER = {
        .Init_Flag = 233,

        .Set_Keys = { 0x00, 0x00, 0x00, 0x00, 0X00, HID_KEYBOARD_SPACEBAR, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 0,
        .SwitchKeys_DelayCnt = 0,

        .NextPos_Relative = 0,
        .Reset_Flag = FALSE
};

keycfg KeyCfg_RAM_RBT = {
        .Init_Flag = 233,

        .Set_Keys = { 0x00, 0x00, 0x00, 0x00, 0X00, 0x00, 0x00, 0x00 },
        .Set_Csms = { HID_CONSUMER_PLAY_PAUSE, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0x00, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 2,
        .SwitchKeys_DelayCnt = 0,

        .NextPos_Relative = 0,
        .Reset_Flag = FALSE
};

keycfg KeyCfg_RAM_RL = {
        .Init_Flag = 233,

        .Set_Keys = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, HID_CONSUMER_VOLUME_UP, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0x00, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 2,
        .SwitchKeys_DelayCnt = 0,

        .NextPos_Relative = 0,
        .Reset_Flag = FALSE
};

keycfg KeyCfg_RAM_RR = {
        .Init_Flag = 233,

        .Set_Keys = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, HID_CONSUMER_VOLUME_DOWN, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0x00, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 2,
        .SwitchKeys_DelayCnt = 0,

        .NextPos_Relative = 0,
        .Reset_Flag = FALSE
};

void UserCfg_Init() {

    uint8_t buf[1] = { 0 };

    EEPROM_READ(USERCFG_ROM_ADDR, buf, 1);

    if (buf[0] != 233) {
        EEPROM_ERASE(0, 256);
        EEPROM_WRITE(USERCFG_ROM_ADDR, (uint8_t* )(&UserCfg_RAM),
                sizeof(usercfg));
    } else {
        EEPROM_READ(USERCFG_ROM_ADDR, (uint8_t* )(&UserCfg_RAM),
                sizeof(usercfg));
    }

}


void KeyCfg_JumpNext(uint32_t StartPos, keycfg* P_KeyCfg){
    uint32_t AbsPos = StartPos + (P_KeyCfg->NextPos_Relative * sizeof(keycfg));
    uint8_t InitFlg[1] = { 0x00 };

    EEPROM_READ(AbsPos, InitFlg, 1);

    if(InitFlg[0] != 233){
        return;
    }

    EEPROM_READ(AbsPos, P_KeyCfg, sizeof(keycfg));
}

void KeyCfg_Reset(uint32_t StartPos, keycfg* P_KeyCfg){
    EEPROM_READ(StartPos, P_KeyCfg, sizeof(keycfg));
}
