/*
 * ledout.c
 *
 *  Created on: 2023年10月10日
 *      Author: 19156
 */

#include "math.h"
#include "config.h"
#include "ledout.h"
#include "keyin.h"
#include "settingctrl.h"

uint8_t LedOut_MainSW = TRUE;

__attribute__((aligned(4)))    uint32_t LED_TX_DMA_BUF[] = {

    // LIGHT 1
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // LIGHT 2
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // LIGHT 3
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // LIGHT 4
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // LIGHT 5
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // LIGHT 6
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // RST
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, };

__attribute__((aligned(4)))    uint32_t LED_TX_DMA_Front[] = {

    // LIGHT 1
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // LIGHT 2
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // LIGHT 3
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // LIGHT 4
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // LIGHT 5
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // LIGHT 6
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

    // RST
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, };

__attribute__((aligned(4)))    uint32_t LED_SET[] = {
    // G
    51, 51, 51, 51, 51, 51, 51, 51,

    // R
    51, 26, 51, 51, 26, 51, 51, 26,

    // B
    51, 51, 26, 26, 26, 26, 26, 51,
};

#define LED_PINK 255, 182, 193

uint8_t LedOut_FreshTask_Id = INVALID_TASK_ID;
static uint16_t LedOut_FreshTask(uint8_t task_id, uint16_t events);

uint8_t LedOut_FreshLight_Id = INVALID_TASK_ID;
static uint16_t LedOut_FreshLight(uint8_t task_id, uint16_t events);

inline void setLEDColor(uint32_t* array, uint8_t R, uint8_t G, uint8_t B);

uint8_t LightState_X = 0;
uint8_t LightState_C = 0;
uint8_t LightState_V = 0;
uint8_t LightState_CTRL = 0;
uint8_t LightState_SPACE = 0;
uint8_t LightState_BT = 0;

uint8_t DMA_Lock = FALSE;

void LedOut_Init() {

    GPIOA_ModeCfg(GPIO_Pin_11, GPIO_ModeOut_PP_5mA);

    TMR2_PWMCycleCfg(LED_TX_CIRCLE); // 1.5us

    TMR2_DMACfg(ENABLE, (uint16_t) (uint32_t) &(LED_TX_DMA_Front[0]),
        (uint16_t) (uint32_t) &(LED_TX_DMA_Front[(sizeof(LED_TX_DMA_Front) / sizeof(uint32_t))]), Mode_LOOP);

    TMR2_PWMInit(High_Level, PWM_Times_1);

    TMR2_ClearITFlag(TMR1_2_IT_DMA_END);

    PFIC_EnableIRQ(TMR2_IRQn);
    TMR2_ITCfg(ENABLE, TMR1_2_IT_DMA_END);

    LedOut_FreshTask_Id = TMOS_ProcessEventRegister(LedOut_FreshTask);
    LedOut_FreshLight_Id = TMOS_ProcessEventRegister(LedOut_FreshLight);


    tmos_start_reload_task(LedOut_FreshTask_Id, 0x0001, 16);
    tmos_start_reload_task(LedOut_FreshLight_Id, 0x0001, 16);

}

uint16_t LedOut_FreshTask(uint8_t task_id, uint16_t events) {

    static uint8_t light_keymap_o = 0x00;
    static uint8_t is_setting_state_o = FALSE;

    if(!LedOut_MainSW){
         LightState_X = 0;
         LightState_C = 0;
         LightState_V = 0;
         LightState_CTRL = 0;
         LightState_SPACE = 0;
         LightState_BT = 0;
        return 0;
    }

    if(LightState_X != 0 && LightState_X != 255)
        LightState_X /= 1.1;
    if(LightState_C != 0 && LightState_C != 255)
        LightState_C /= 1.1;
    if(LightState_V != 0 && LightState_V != 255)
        LightState_V /= 1.1;
    if(LightState_CTRL != 0 && LightState_CTRL != 255)
        LightState_CTRL /= 1.1;
    if(LightState_SPACE != 0 && LightState_SPACE != 255)
        LightState_SPACE /= 1.1;

    if(LightState_BT != 0 && LightState_BT != 255)
        LightState_BT /= 1.1;

    if((Keymap & (0x01 << MAP_X)) > 0){
        LightState_X = 255;
    } else if ( ((Keymap & (0x01 << MAP_X)) == 0) && ((light_keymap_o & (0x01 << MAP_X)) > 0) ) {
        LightState_X = 254;
    }

    if((Keymap & (0x01 << MAP_C)) > 0){
        LightState_C = 255;
    } else if ( ((Keymap & (0x01 << MAP_C)) == 0) && ((light_keymap_o & (0x01 << MAP_C)) > 0) ) {
        LightState_C = 254;
    }

    if((Keymap & (0x01 << MAP_V)) > 0){
        LightState_V = 255;
    } else if ( ((Keymap & (0x01 << MAP_V)) == 0) && ((light_keymap_o & (0x01 << MAP_V)) > 0) ) {
        LightState_V = 254;
    }

    if((Keymap & (0x01 << MAP_CTRL)) > 0){
        LightState_CTRL = 255;
    } else if ( ((Keymap & (0x01 << MAP_CTRL)) == 0) && ((light_keymap_o & (0x01 << MAP_CTRL)) > 0) ) {
        LightState_CTRL = 254;
    }

    if((Keymap & (0x01 << MAP_ENTER)) > 0){
        LightState_SPACE = 255;
    } else if ( ((Keymap & (0x01 << MAP_ENTER)) == 0) && ((light_keymap_o & (0x01 << MAP_ENTER)) > 0) ) {
        LightState_SPACE = 254;
    }

    if(is_setting_state){
        LightState_BT = 255;
    } else if (is_setting_state == FALSE && is_setting_state_o == TRUE) {
        LightState_BT = 254;
    }

    light_keymap_o = Keymap;
    is_setting_state_o = is_setting_state;
    return 0;
}

uint16_t LedOut_FreshLight(uint8_t task_id, uint16_t events) {

    DMA_Lock = TRUE;

    if(LightState_X == 255){
        setLEDColor(LED_SET, LED_PINK);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_X * 24)]), LED_SET, sizeof(LED_SET));
    } else {
        setLEDColor(LED_SET, LightState_X, LightState_X, LightState_X);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_X * 24)]), LED_SET, sizeof(LED_SET));
    }

    if(LightState_C == 255){
        setLEDColor(LED_SET, LED_PINK);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_C * 24)]), LED_SET, sizeof(LED_SET));
    } else {
        setLEDColor(LED_SET, LightState_C, LightState_C, LightState_C);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_C * 24)]), LED_SET, sizeof(LED_SET));
    }

    if(LightState_V == 255){
        setLEDColor(LED_SET, LED_PINK);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_V * 24)]), LED_SET, sizeof(LED_SET));
    } else {
        setLEDColor(LED_SET, LightState_V, LightState_V, LightState_V);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_V * 24)]), LED_SET, sizeof(LED_SET));
    }


    if(LightState_CTRL == 255){
        setLEDColor(LED_SET, LED_PINK);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_CTRL * 24)]), LED_SET, sizeof(LED_SET));
    } else {
        setLEDColor(LED_SET, LightState_CTRL, LightState_CTRL, LightState_CTRL);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_CTRL * 24)]), LED_SET, sizeof(LED_SET));
    }

    if(LightState_SPACE == 255){
        setLEDColor(LED_SET, LED_PINK);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_SPACE * 24)]), LED_SET, sizeof(LED_SET));
    } else {
        setLEDColor(LED_SET, LightState_SPACE, LightState_SPACE, LightState_SPACE);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_SPACE * 24)]), LED_SET, sizeof(LED_SET));
    }

    if(LightState_BT == 255){
        setLEDColor(LED_SET, LED_PINK);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_BT * 24)]), LED_SET, sizeof(LED_SET));
    } else {
        setLEDColor(LED_SET, LightState_BT, LightState_BT, LightState_BT);
        tmos_memcpy(&(LED_TX_DMA_BUF[(LED_BT * 24)]), LED_SET, sizeof(LED_SET));
    }

    DMA_Lock = FALSE;

    return 0;
}

/*********************************************************************
 * @fn      TMR2_IRQHandler
 *
 * @brief   TMR2中断函数
 *
 * @return  none
 */
__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode")))
void TMR2_IRQHandler(void) {
    if (TMR2_GetITFlag(TMR0_3_IT_CYC_END)) {
        TMR2_ClearITFlag(TMR0_3_IT_CYC_END);
        /* 计数器计满，硬件自动清零，重新开始计数 */
        /* 用户可自行添加需要的处理 */
    }
    if (TMR2_GetITFlag(TMR1_2_IT_DMA_END)) {
        TMR2_ClearITFlag(TMR1_2_IT_DMA_END);
        /* DMA 结束 */
        /* 用户可自行添加需要的处理 */
        if (DMA_Lock == FALSE){
            memcpy(LED_TX_DMA_Front, LED_TX_DMA_BUF, sizeof(LED_TX_DMA_Front));
        }
    }
}



void setLEDColor(uint32_t* array, uint8_t R, uint8_t G, uint8_t B) {
    // 设置G7~G0
    for (int i = 0; i < 8; i++) {
        array[i] = (G & (1 << (7 - i))) ? 51 : 26;
    }

    // 设置R7~R0
    for (int i = 0; i < 8; i++) {
        array[i + 8] = (R & (1 << (7 - i))) ? 51 : 26;
    }

    // 设置B7~B0
    for (int i = 0; i < 8; i++) {
        array[i + 16] = (B & (1 << (7 - i))) ? 51 : 26;
    }
}
