/*
 * input.c
 *
 *  Created on: 2023年8月28日
 *      Author: 19156
 */

#include "input.h"
#include "output.h"
#include "protoctrl.h"

#include "hid_ble.h"
#include "HAL.h"

#include "OLED.h"
#include "hiddev.h"

#include "../HAL/include/ENCODER.h"

static uint8_t TMOS_Keys_Enc_Scan_TaskId = INVALID_TASK_ID;
static uint16_t TMOS_Keys_Enc_Scan(uint8_t task_id, uint16_t events);

void Input_Init() {

    // ENCODER INIT
    TMOS_Keys_Enc_Scan_TaskId = TMOS_ProcessEventRegister(TMOS_Keys_Enc_Scan);

    Encoder_InitTypeDef Encoder_InitStructure;
    Encoder_InitStructure.Encoder_A = ROLLER_A;
    Encoder_InitStructure.Encoder_B = ROLLER_B;
    Encoder_InitStructure.SpinEventCB = 0x000000;
    Encoder_InitStructure.TriggerInterval = 5;

    Encoder_Init(&Encoder_InitStructure);

    GPIOA_ModeCfg(ROLLER_A, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(ROLLER_B, GPIO_ModeIN_PU);
    GPIOA_ITModeCfg(ROLLER_A, GPIO_ITMode_FallEdge);
    PFIC_EnableIRQ(GPIO_A_IRQn);

    tmos_start_reload_task(TMOS_Keys_Enc_Scan_TaskId, 0x0001, 16);

    // KEY INIT
    GPIOA_ModeCfg(KEY_LEFT_CTRL, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(ROLLER_BUTTON, GPIO_ModeIN_PU);

    GPIOB_ModeCfg(KEY_RIGHT_ENTER, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(KEY_X, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(KEY_C, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(KEY_V, GPIO_ModeIN_PU);
}

uint16_t TMOS_Keys_Enc_Scan(uint8_t task_id, uint16_t events) {

    static uint8_t old_keys = 0x00;
    uint8_t keys = 0x00;

    static uint8_t jump_cnt = 0;

    if (events & SYS_EVENT_MSG) {
        return (events ^ SYS_EVENT_MSG);
    }

    for (uint8_t i = 0; i < 8; i++) {
        ReportBuf_Keyboard[i] = 0x00;
    }
    for (uint8_t i = 0; i < 2; i++) {
        ReportBuf_Consumer[i] = 0x00;
    }

    if (_delta_value) {
        switch (_delta_value) {
        case 1:
            ReportBuf_Consumer[0] = HID_CONSUMER_VOLUME_UP;
            ProtoCtrl_SendCSReport();
            switch (jump_cnt) {
            case 0:
                SSD13xx.PutChar(OLED_Handle, 0, 3, '|');
                break;
            case 1:
                SSD13xx.PutChar(OLED_Handle, 0, 3, '/');
                break;
            case 2:
                SSD13xx.PutChar(OLED_Handle, 0, 3, '-');
                break;
            case 3:
                SSD13xx.PutChar(OLED_Handle, 0, 3, '\\');
                break;
            }
            break;
        case 2:
            ReportBuf_Consumer[0] = HID_CONSUMER_VOLUME_DOWN;
            ProtoCtrl_SendCSReport();
            switch (jump_cnt) {
            case 0:
                SSD13xx.PutChar(OLED_Handle, 0, 3, '|');
                break;
            case 1:
                SSD13xx.PutChar(OLED_Handle, 0, 3, '\\');
                break;
            case 2:
                SSD13xx.PutChar(OLED_Handle, 0, 3, '-');
                break;
            case 3:
                SSD13xx.PutChar(OLED_Handle, 0, 3, '/');
                break;
            }
            break;
        }

        // 此处要求与第一个report间隔几个SSD13XX输出，争取空闲给USB控制器上传
        ReportBuf_Consumer[0] = 0x00;
        ProtoCtrl_SendCSReport();

        _delta_value = 0;
        jump_cnt = (jump_cnt + 1) % 4;
        Output_Clear4Ln_WaitCnt = 2;
    }

    keys |= GPIOA_ReadPortPin(ROLLER_BUTTON) ? 0x00 : MAP_ROLLER_BUTTON;
    keys |= GPIOA_ReadPortPin(KEY_LEFT_CTRL) ? 0x00 : MAP_LEFT_CTRL;

    keys |= GPIOB_ReadPortPin(KEY_RIGHT_ENTER) ? 0x00 : MAP_RIGHT_ENTER;
    keys |= GPIOB_ReadPortPin(KEY_X) ? 0x00 : MAP_KEY_X;
    keys |= GPIOB_ReadPortPin(KEY_C) ? 0x00 : MAP_KEY_C;
    keys |= GPIOB_ReadPortPin(KEY_V) ? 0x00 : MAP_KEY_V;

    if (keys & MAP_ROLLER_BUTTON) {
        ReportBuf_Consumer[0] = HID_CONSUMER_PLAY_PAUSE;
        ProtoCtrl_SendCSReport();
        SSD13xx.Print(OLED_Handle, 10, 3, "P/P", 3);
        ReportBuf_Consumer[0] = 0x00;
        ProtoCtrl_SendCSReport();
    }
    if (keys & MAP_LEFT_CTRL) {
        SSD13xx.PutChar(OLED_Handle, 2, 3, '^');
        ReportBuf_Keyboard[0] = 0x01;
    }
    if (keys & MAP_RIGHT_ENTER) {
        if (keys & MAP_LEFT_CTRL) {
            SSD13xx.Print(OLED_Handle, 10, 3, "ENT", 3);
            ReportBuf_Keyboard[6] = HID_KEYBPAD_ENTER;
        } else {
            SSD13xx.Print(OLED_Handle, 10, 3, "SPC", 3);
            ReportBuf_Keyboard[2] = HID_KEYBOARD_SPACEBAR;
        }
    }

    if (keys & MAP_KEY_X) {
        SSD13xx.PutChar(OLED_Handle, 4, 3, 'X');
        ReportBuf_Keyboard[3] = HID_KEYBOARD_X;
    }
    if (keys & MAP_KEY_C) {
        SSD13xx.PutChar(OLED_Handle, 6, 3, 'C');
        ReportBuf_Keyboard[4] = HID_KEYBOARD_C;
    }
    if (keys & MAP_KEY_V) {
        SSD13xx.PutChar(OLED_Handle, 8, 3, 'V');
        ReportBuf_Keyboard[5] = HID_KEYBOARD_V;
    }

    if (keys != old_keys) {
        ProtoCtrl_SendKBReport();
        old_keys = keys;
        Output_Clear4Ln_WaitCnt = 2;
    }

    return 0;
}

/*
 * @brief ENCODER INTERRUPT
 */
__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode"))) void GPIOA_IRQHandler(void) {
    if (GPIOA_ReadITFlagBit(ROLLER_A)) {
        Encoder_Spin();
        GPIOA_ClearITFlagBit(ROLLER_A);
    }
}
