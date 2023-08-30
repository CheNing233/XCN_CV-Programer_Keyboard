/*
 * USB.c
 *
 *  Created on: 2023年8月17日
 *      Author: 19156
 */

#include <CH57x_common.h>
#include <config.h>
#include "HAL.h"

#include "protoctrl.h"

#include "hid_usb.h"
#include "../../UserPeriphDriver/USB/USB.h"

static void USB_KB_LEDCB(uint8_t led);

void USB_Init() {
    USBProto_InitTypeDef USBProto_InitStructure;
    USBProto_InitStructure.LEDStatusChange = USB_KB_LEDCB;

    USBProto.Init(&USBProto_InitStructure);

    USB_DeviceInit();

    PFIC_EnableIRQ(USB_IRQn);
}

void USB_KB_UploadKey() {
    memcpy(pEP1_IN_DataBuf, ReportBuf_Keyboard, 8);
    DevEP1_IN_Deal(8);
}

void USB_KB_UploadConsumer() {
    memcpy(pEP2_IN_DataBuf, ReportBuf_Consumer, 2);
    DevEP2_IN_Deal(2);
}

void USB_KB_LEDCB(uint8_t led) {
    if (Global_ProtoState == Board_USBState) {
        if ((led) & 0x01) {
            SSD13xx.Print(OLED_Handle, 6, 2, "NUMS", 4);
        } else {
            SSD13xx.Print(OLED_Handle, 6, 2, "    ", 4);
        }

        if ((led) & 0x02) {
            SSD13xx.Print(OLED_Handle, 11, 2, "CAPS", 4);
        } else {
            SSD13xx.Print(OLED_Handle, 11, 2, "    ", 4);
        }
    }
}

__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode"))) void USB_IRQHandler(void) {
    // USB中断服务程序,使用寄存器组1
    USB_DevTransProcess();
}
