/*
 * output.c
 *
 *  Created on: 2023Äê8ÔÂ28ÈÕ
 *      Author: 19156
 */

#include "output.h"
#include "HAL.h"

#include "OLED.h"

uint8_t Output_Clear4Ln_WaitCnt = 0;

static uint8_t TMOS_Output_FreshDisplay_TaskId = INVALID_TASK_ID;
static uint16_t Output_FreshDisplay(uint8_t task_id, uint16_t events);

void Output_Init() {

    // OLED INIT
    OLED_Init(OLED_IIC_GND, OLED_IIC_VCC, OLED_IIC_SDA, OLED_IIC_SCL);

    SSD13xx.Print(OLED_Handle, 0, 0, "xChenNIngKB[   ]", 16);
    SSD13xx.Print(OLED_Handle, 0, 1, "----------------", 16);
    SSD13xx.Print(OLED_Handle, 0, 2, "LOCK:           ", 16);

    TMOS_Output_FreshDisplay_TaskId = TMOS_ProcessEventRegister(
            Output_FreshDisplay);

    tmos_start_reload_task(TMOS_Output_FreshDisplay_TaskId, 0x0001, 1600);
}

uint16_t Output_FreshDisplay(uint8_t task_id, uint16_t events) {

    if (events & SYS_EVENT_MSG) {
        return (events ^ SYS_EVENT_MSG);
    }

    if (Output_Clear4Ln_WaitCnt) {
        Output_Clear4Ln_WaitCnt--;
        if (!Output_Clear4Ln_WaitCnt) {
            SSD13xx.Print(OLED_Handle, 0, 3, "                ", 16);
        }
    }

    return 0;
}
