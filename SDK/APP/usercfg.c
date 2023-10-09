/*
 * usercfg.c
 *
 *  Created on: 2023Äê9ÔÂ24ÈÕ
 *      Author: 19156
 */

#include "config.h"
#include "usercfg.h"
#include "hiddev.h"

usercfg UserCfg_RAM = {

    .Init_Flag = sizeof(usercfg),

    .Proto_FreshState_Interval = 1600,
    .Proto_USBBuffer_PushInterval = 8,
    .Proto_BLEBuffer_PushInterval = 32,

    .KeyIn_Key_Debouncing_Sampling_Interval = 4,
    .KeyIn_Enco_Debouncing_Sampling_Interval = 4,
    .KeyIn_Debouncing_DelayCircle_Cnt = 1,
    .KeyIn_TaskFlgManager_Circle_Interval = 8,
    .KeyIn_TransMacro_Circle_Interval = 8,

    .USB_UploadRate = 0x01,
    .BLE_Conn_Interval = 4,

    .BLE_Uplaod_PackCnt = 20

};

keycfg KeyCfg_RAM_X = {
        .Init_Flag = sizeof(keycfg),

        .Set_Keys = { 0x00, 0x00, HID_KEYBOARD_X, 0x00, 0x00, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 0,
        .SwitchNext_DelayCnt = 0,

        .NextPos = 0,
};

keycfg KeyCfg_RAM_C = {
        .Init_Flag = sizeof(keycfg),

        .Set_Keys = { 0x00, 0x00, 0x00, HID_KEYBOARD_C , 0x00, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 0,
        .SwitchNext_DelayCnt = 0,

        .NextPos = 0,
};

keycfg KeyCfg_RAM_V = {
        .Init_Flag = sizeof(keycfg),

        .Set_Keys = { 0x00, 0x00, 0x00, 0x00, HID_KEYBOARD_V, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 0,
        .SwitchNext_DelayCnt = 0,

        .NextPos = 0,
};

keycfg KeyCfg_RAM_CTRL = {
        .Init_Flag = sizeof(keycfg),

        .Set_Keys = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 0,
        .SwitchNext_DelayCnt = 0,

        .NextPos = 0,
};

keycfg KeyCfg_RAM_ENTER = {
        .Init_Flag = sizeof(keycfg),

        .Set_Keys = { 0x00, 0x00, 0x00, 0x00, 0X00, HID_KEYBOARD_SPACEBAR, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 0,
        .SwitchNext_DelayCnt = 0,

        .NextPos = 0,
};

keycfg KeyCfg_RAM_RBT = {
        .Init_Flag = sizeof(keycfg),

        .Set_Keys = { 0x00, 0x00, 0x00, 0x00, 0X00, 0x00, 0x00, 0x00 },
        .Set_Csms = { HID_CONSUMER_PLAY_PAUSE, 0x00, 0x00, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0x00, 0xff, 0xff, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 2,
        .SwitchNext_DelayCnt = 0,

        .NextPos = 0,
};

keycfg KeyCfg_RAM_RL = {
        .Init_Flag = sizeof(keycfg),

        .Set_Keys = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, HID_CONSUMER_VOLUME_UP, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0x00, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 2,
        .SwitchNext_DelayCnt = 0,

        .NextPos = 0,
};

keycfg KeyCfg_RAM_RR = {
        .Init_Flag = sizeof(keycfg),

        .Set_Keys = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        .Set_Csms = { 0x00, 0x00, HID_CONSUMER_VOLUME_DOWN, 0x00 },

        .Reset_Keys = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
        .Reset_Csms = { 0xff, 0xff, 0x00, 0xff },

        .FinishTsk_PushCnt = 0,
        .FinishTsk_RlseCnt = 1,
        .FinishTsk_HoldCnt = 2,
        .SwitchNext_DelayCnt = 0,

        .NextPos = 0,
};


void UserCfg_Init() {

    uint8_t buf[1] = { 0 };

    EEPROM_READ(USERCFG_ROM_ADDR, buf, 1);
    if (buf[0] != sizeof(usercfg)) {
        UserCfg_Write_Setting((uint8_t*)&UserCfg_RAM);
    } else {
        UserCfg_Read_Setting();
    }

    EEPROM_READ(KEYCFG_ROM_X, buf, 1);
    if (buf[0] != sizeof(keycfg)) {
        KeyCfg_Write_Setting((uint8_t*)&KeyCfg_RAM_X, KEYCFG_ROM_X, 0);
    } else {
        KeyCfg_Read_Setting((uint8_t*)&KeyCfg_RAM_X, KEYCFG_ROM_X, 0);
    }

    EEPROM_READ(KEYCFG_ROM_C, buf, 1);
    if (buf[0] != sizeof(keycfg)) {
        KeyCfg_Write_Setting((uint8_t*)&KeyCfg_RAM_C, KEYCFG_ROM_C, 0);
    } else {
        KeyCfg_Read_Setting((uint8_t*)&KeyCfg_RAM_C, KEYCFG_ROM_C, 0);
    }

    EEPROM_READ(KEYCFG_ROM_V, buf, 1);
    if (buf[0] != sizeof(keycfg)) {
        KeyCfg_Write_Setting((uint8_t*)&KeyCfg_RAM_V, KEYCFG_ROM_V, 0);
    } else {
        KeyCfg_Read_Setting((uint8_t*)&KeyCfg_RAM_V, KEYCFG_ROM_V, 0);
    }

    EEPROM_READ(KEYCFG_ROM_CTRL, buf, 1);
    if (buf[0] != sizeof(keycfg)) {
        KeyCfg_Write_Setting((uint8_t*)&KeyCfg_RAM_CTRL, KEYCFG_ROM_CTRL, 0);
    } else {
        KeyCfg_Read_Setting((uint8_t*)&KeyCfg_RAM_CTRL, KEYCFG_ROM_CTRL, 0);
    }

    EEPROM_READ(KEYCFG_ROM_ENTER, buf, 1);
    if (buf[0] != sizeof(keycfg)) {
        KeyCfg_Write_Setting((uint8_t*)&KeyCfg_RAM_ENTER, KEYCFG_ROM_ENTER, 0);
    } else {
        KeyCfg_Read_Setting((uint8_t*)&KeyCfg_RAM_ENTER, KEYCFG_ROM_ENTER, 0);
    }

    EEPROM_READ(KEYCFG_ROM_RBT, buf, 1);
    if (buf[0] != sizeof(keycfg)) {
        KeyCfg_Write_Setting((uint8_t*)&KeyCfg_RAM_RBT, KEYCFG_ROM_RBT, 0);
    } else {
        KeyCfg_Read_Setting((uint8_t*)&KeyCfg_RAM_RBT, KEYCFG_ROM_RBT, 0);
    }

    EEPROM_READ(KEYCFG_ROM_RL, buf, 1);
    if (buf[0] != sizeof(keycfg)) {
        KeyCfg_Write_Setting((uint8_t*)&KeyCfg_RAM_RL, KEYCFG_ROM_RL, 0);
    } else {
        KeyCfg_Read_Setting((uint8_t*)&KeyCfg_RAM_RL, KEYCFG_ROM_RL, 0);
    }

    EEPROM_READ(KEYCFG_ROM_RR, buf, 1);
    if (buf[0] != sizeof(keycfg)) {
        KeyCfg_Write_Setting((uint8_t*)&KeyCfg_RAM_RR, KEYCFG_ROM_RR, 0);
    } else {
        KeyCfg_Read_Setting((uint8_t*)&KeyCfg_RAM_RR, KEYCFG_ROM_RR, 0);
    }
}

void UserCfg_Read_Setting() {
    EEPROM_READ(USERCFG_ROM_ADDR, (uint8_t* )(&UserCfg_RAM), sizeof(usercfg));
}

void UserCfg_Write_Setting(uint8_t* ram_addr) {
    EEPROM_ERASE(0, 256);
    EEPROM_WRITE(USERCFG_ROM_ADDR, ram_addr, sizeof(usercfg));
}

void KeyCfg_Read_Setting(uint8_t* dstp, uint16_t keyset_addr, uint16_t offset) {
    EEPROM_READ(keyset_addr + (offset * sizeof(keycfg)), dstp, sizeof(keycfg));
}

void KeyCfg_Write_Setting(uint8_t* ram_addr, uint16_t keyset_addr, uint16_t offset) {
    keycfg empty_buf = {
        0
    };

    tmos_memset((uint8_t*)&empty_buf, 0XFF, sizeof(keycfg));

    EEPROM_WRITE(keyset_addr + (offset * sizeof(keycfg)), (uint8_t*)&empty_buf, sizeof(keycfg));
    EEPROM_WRITE(keyset_addr + (offset * sizeof(keycfg)), ram_addr, sizeof(keycfg));
}


void KeyCfg_JumpNext(uint32_t StartPos, keycfg* P_KeyCfg) {
    uint32_t AbsPos = StartPos + (P_KeyCfg->NextPos * sizeof(keycfg));
    uint8_t InitFlg[1] = { 0x00 };

    EEPROM_READ(AbsPos, InitFlg, 1);

    if (InitFlg[0] != sizeof(keycfg)) {
        return;
    }

    EEPROM_READ(AbsPos, P_KeyCfg, sizeof(keycfg));
}
