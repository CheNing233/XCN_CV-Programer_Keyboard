/*
 * motorout.c
 *
 *  Created on: 2023Äê11ÔÂ11ÈÕ
 *      Author: 19156
 */

#include "config.h"
#include "motorout.h"

uint8_t MotorOut_MainSW = FALSE;

uint8_t MotorOut_Holder_Id = INVALID_TASK_ID;
uint16_t MotorOut_Holder(uint8_t task_id, uint16_t events);

uint16_t MotorOut_unblock_cnt = 0;

void MotorOut_Init(){
    MOTOR_PIN_INIT;
    MOTOR_PIN_PD;

    MotorOut_Holder_Id = TMOS_ProcessEventRegister(MotorOut_Holder);
    tmos_start_reload_task(MotorOut_Holder_Id, 0x0001, 16);
}

void Motor_Block_LightShock(){
    MOTOR_PIN_PU;
    DelayMs(30);
    MOTOR_PIN_PD;
}

uint16_t MotorOut_Holder(uint8_t task_id, uint16_t events){

    static uint16_t MotorOut_unblock_cnt_o = 0;

    if(MotorOut_unblock_cnt != 0){
        MotorOut_unblock_cnt--;
    }

    if(MotorOut_unblock_cnt != 0 && MotorOut_unblock_cnt_o == 0){
        MOTOR_PIN_PU;
    } else if (MotorOut_unblock_cnt == 0 && MotorOut_unblock_cnt_o > 0) {
        MOTOR_PIN_PD;
    }

    MotorOut_unblock_cnt_o = MotorOut_unblock_cnt;
    return 0;
}
