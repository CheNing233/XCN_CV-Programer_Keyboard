/*
 * OLED.c
 *
 *  Created on: 2023Äê8ÔÂ17ÈÕ
 *      Author: 19156
 */
#include <CH57x_common.h>
#include <OLED.h>
#include "../../UserPeriphDriver/SSD13xx/SSD13xx.h"
#include "../../UserPeriphDriver/IIC/IIC.h"

IIC_Handle_t SoftwareIIC_Handle;
SSD13xx_handle_t OLED_Handle;

static uint32_t _IIC_SDA;
static uint32_t _IIC_SCL;

static void GPIO_SCL_PullUp();
static void GPIO_SCL_PullDown();
static void GPIO_SDA_PullUp();
static void GPIO_SDA_PullDown();
static void IIC_StartComunication();
static void IIC_SendByte(uint8_t ByteBuf_Target);
static void IIC_StopComunication();

void OLED_Init(uint32_t IIC_GND, uint32_t IIC_VCC, uint32_t IIC_SDA,
        uint32_t IIC_SCL) {

    _IIC_SDA = IIC_SDA;
    _IIC_SCL = IIC_SCL;

    if (IIC_GND != 0 && IIC_VCC != 0) {
        GPIOA_ModeCfg(IIC_GND, GPIO_ModeIN_Floating);
        GPIOA_ModeCfg(IIC_VCC, GPIO_ModeIN_Floating);
    }
    GPIOA_ModeCfg(IIC_SDA, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg(IIC_SCL, GPIO_ModeOut_PP_5mA);

    IIC_InitTypeDef IIC_InitStructure;

    IIC_InitStructure.SCL_PullUp = &GPIO_SCL_PullUp;
    IIC_InitStructure.SCL_PullDown = &GPIO_SCL_PullDown;
    IIC_InitStructure.SDA_PullUp = &GPIO_SDA_PullUp;
    IIC_InitStructure.SDA_PullDown = &GPIO_SDA_PullDown;

    IIC.Init(&IIC_InitStructure, &SoftwareIIC_Handle);

    SSD13xx_InitTypeDef SSD13xx_InitStructure;

    SSD13xx_InitStructure.StartComunication = &IIC_StartComunication;
    SSD13xx_InitStructure.StopComunication = &IIC_StopComunication;
    SSD13xx_InitStructure.SendByte = &IIC_SendByte;

    SSD13xx.Init(&SSD13xx_InitStructure, &OLED_Handle);
}

void IIC_StartComunication() {
    IIC.StartComunication(SoftwareIIC_Handle);
}

void IIC_SendByte(uint8_t ByteBuf_Target) {
    IIC.SendByte(SoftwareIIC_Handle, ByteBuf_Target);
}

void IIC_StopComunication() {
    IIC.StopComunication(SoftwareIIC_Handle);
}

void GPIO_SCL_PullUp() {
    GPIOA_SetBits(_IIC_SCL);
}

void GPIO_SCL_PullDown() {
    GPIOA_ResetBits(_IIC_SCL);
}

void GPIO_SDA_PullUp() {
    GPIOA_SetBits(_IIC_SDA);
}

void GPIO_SDA_PullDown() {
    GPIOA_ResetBits(_IIC_SDA);
}
