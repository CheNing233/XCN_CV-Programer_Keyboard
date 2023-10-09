/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2020/08/06
 * Description        : 蓝牙键盘应用主函数及任务系统初始化
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */

#include "CONFIG.h"
#include "HAL.h"
#include "hiddev.h"
#include "protocol.h"
#include "app_usb.h"
#include "app_ble.h"
#include "usercfg.h"
#include "keyin.h"

#define EN8_A GPIO_Pin_4 //PB4
#define EN8_B GPIO_Pin_7 //PB7
#define EN8_C GPIO_Pin_12 //PA12

/*********************************************************************
 * GLOBAL TYPEDEFS
 */
__attribute__((aligned(4)))    uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

/*********************************************************************
 * @fn      Main_Circulation
 *
 * @brief   主循环
 *
 * @return  none
 */
__attribute__((section(".highcode")))
__attribute__((noinline))
void Main_Circulation() {
    while(1)
    {
        TMOS_SystemProcess();
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   主函数
 *
 * @return  none
 */
int main(void) {
#if(defined(DCDC_ENABLE)) && (DCDC_ENABLE == TRUE)
    PWR_DCDCCfg(ENABLE);
#endif
    SetSysClock(CLK_SOURCE_PLL_60MHz);
#if(defined(HAL_SLEEP)) && (HAL_SLEEP == TRUE)
    GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
#endif
//#ifdef DEBUG
//    GPIOA_SetBits(bTXD1);
//    GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
//    UART1_DefInit();
//#endif

    DelayMs(10);

    UserCfg_Init();

    CH57X_BLEInit();
    HAL_Init();

    USB_Init();

    GAPRole_PeripheralInit();
    HidDev_Init();
    HidEmu_Init();

    ProtoCtrl_Init();

    // LED INIT
    GPIOB_ModeCfg(EN8_A, GPIO_ModeOut_PP_5mA);
    GPIOB_ModeCfg(EN8_B, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg(EN8_C, GPIO_ModeOut_PP_5mA);

    GPIOB_SetBits(EN8_A);
    GPIOB_SetBits(EN8_B);
    GPIOA_SetBits(EN8_C);

    Keyin_Init();

    Main_Circulation();
}

/******************************** endfile @ main ******************************/
