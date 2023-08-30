/*
 * protoctrl.c
 *
 *  Created on: 2023年8月29日
 *      Author: 19156
 */
#include "HAL.h"
#include "hid_ble.h"
#include "hid_usb.h"
#include "protoctrl.h"
#include "hiddev.h"

#include "output.h"

Board_ProtoSWState Global_ProtoState;
Borad_ProtoConnState Global_ProtoUSBConn = Board_Conn_Stop;
Borad_ProtoConnState Global_ProtoBLEConn = Board_Conn_Stop;

static uint8_t TMOS_ProtoCtrl_StateUpdater_TaskId = INVALID_TASK_ID;
static uint16_t ProtoCtrl_StateUpdater(uint8_t task_id, uint16_t events);

uint8_t ReportBuf_Keyboard[8] = { 0x00, // 功能键
        0x00, // 保留
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 普通键
        };

uint8_t ReportBuf_Consumer[2] = { 0x00, 0x00 };

void ProtoCtrl_Init() {
    TMOS_ProtoCtrl_StateUpdater_TaskId = TMOS_ProcessEventRegister(
            ProtoCtrl_StateUpdater);

    tmos_start_reload_task(TMOS_ProtoCtrl_StateUpdater_TaskId, 0x0001, 1600);

    GPIOA_ModeCfg(PROTO_SW_PIN, GPIO_ModeIN_PU);
}

uint16_t ProtoCtrl_StateUpdater(uint8_t task_id, uint16_t events) {

    static uint8_t heartbeat_cnt = 0;
    heartbeat_cnt = (heartbeat_cnt + 1) % 2;

    if (events & SYS_EVENT_MSG) {
        return (events ^ SYS_EVENT_MSG);
    }

    Global_ProtoState = (GPIOA_ReadPortPin(PROTO_SW_PIN) ? Board_BLEState : Board_USBState);

    switch (Global_ProtoState) {
    case Board_USBState:
        // 断连并停止广播
        if (Global_ProtoBLEConn != Board_Conn_Stop)
            HidDev_Close();

        if (R8_USB_DEV_AD) {
            SSD13xx.PrintF(OLED_Handle, 12, 0, "USB");
            Global_ProtoUSBConn = Board_Conn_OK;
        } else {
            Global_ProtoUSBConn = Board_Conn_Wait;
            switch (heartbeat_cnt) {
            case 0:
                SSD13xx.PrintF(OLED_Handle, 12, 0, "U. ");
                break;
            case 1:
                SSD13xx.PrintF(OLED_Handle, 12, 0, "U .");
                break;
            }
        }

        break;

    case Board_BLEState:
        // 停止USB传输
        Global_ProtoUSBConn = Board_Conn_Stop;

        // 启动广播
        if (Global_ProtoBLEConn == Board_Conn_Stop)
            HidDev_Start();

        switch (Global_ProtoBLEConn) {
        case Board_Conn_Wait:
            switch (heartbeat_cnt) {
            case 0:
                SSD13xx.PrintF(OLED_Handle, 12, 0, "B. ");
                break;
            case 1:
                SSD13xx.PrintF(OLED_Handle, 12, 0, "B .");
                break;
            }
            break;
        case Board_Conn_OK:
            SSD13xx.PrintF(OLED_Handle, 12, 0, "BLE");
            break;
        }

        break;
    }

    return 0;
}

void ProtoCtrl_SendKBReport() {
    switch (Global_ProtoState) {

    case Board_USBState:
        USB_KB_UploadKey();
        break;

    case Board_BLEState:
        hidEmuSendKbdReport();
        break;
    }
}

void ProtoCtrl_SendCSReport() {
    switch (Global_ProtoState) {

    case Board_USBState:
        USB_KB_UploadConsumer();
        break;

    case Board_BLEState:
        hidEmuSendConsumerReport();
        break;
    }
}
