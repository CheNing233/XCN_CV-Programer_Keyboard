/*
 * USB.h
 *
 *  Created on: 2023Äê8ÔÂ17ÈÕ
 *      Author: 19156
 */

#ifndef __USERDRIVER_USB_USB_H__
#define __USERDRIVER_USB_USB_H__

typedef struct {

    void (*LEDStatusChange)(uint8_t led);

    void (*SleepStatusChange)();

} USBProto_InitTypeDef;

typedef USBProto_InitTypeDef *USBProto_Handle_t;

struct _USBProto_Class {
    void (*Init)(USBProto_InitTypeDef *USBProto_InitStructure);
};

extern struct _USBProto_Class USBProto;

#endif /* __USERDRIVER_USB_USB_H__ */
