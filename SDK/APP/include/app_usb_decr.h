/*
 * USB_Descriptor.h
 *
 *  Created on: 2023年8月24日
 *      Author: 19156
 */

#ifndef USERDRIVER_USB_USB_DESCRIPTOR_H_
#define USERDRIVER_USB_USB_DESCRIPTOR_H_

#include "usercfg.h"

// 端点0最大数据包长度 == 64字节
#define DevEP0SIZE 0x40

// 设备描述符
const uint8_t USB_Device_Descr[] = { 0x12, // 描述符长度为18字节
        0x01, // 描述符类型为设备描述符
        0x10, 0x01, // 支持的USB规范版本号为1.1
        0x00, // 设备类代码为未指定
        0x00, // 设备子类代码为未指定
        0x00, // 设备协议代码为未指定
        DevEP0SIZE, // 最大数据包尺寸为DevEP0SIZE == 64
        0x3d, 0x41, // 设备厂商ID为0x3d41
        0x07, 0x21, // 设备产品ID为0x0721
        0x00, 0x00, // 设备版本号为0.0
        0x01, // 厂商字符串描述符的索引为0
        0x02, // 产品字符串描述符的索引为0
        0x00, // 序列号字符串描述符的索引为0
        0x01 // 设备支持的配置数量为1
        };

// 配置描述符
uint8_t USB_Config_Descr[] = {

0x09,       //bLength字段。配置描述符的长度为9字节
        0x02,       //bDescriptorType字段。配置描述符编号为0x02
        0x52,       //wTotalLength字段。配置描述符集合的总长度0x003b，包含所有配置描述符，除了HID报表描述符
        0x00, 0x03, //bNumInterfaces字段。该配置包含的接口数，只有2个接口
        0x01,       //bConfiguration字段。该配置的值为1
        0x01,       //iConfigurationz字段，该配置的字符串索引。
        0xA0,       //bmAttributes字段,bit4-bit7描述设备的特性
        0x64,       //bMaxPower字段，该设备需要的最大电流量。每单位电流为 2 mA

        //接口1，keyboard
        0x09, 0x04, 0x00, 0x00, 0x01, 0x03, 0x01, 0x01, 0x00, //接口描述符

        0x09, 0x21, 0x11, 0x01, 0x00, 0x01, 0x22, 0x3e, 0x00, //HID类描述符

        0x07, 0x05, 0x81, 0x03, 0x08, 0x00, 0x01, //端点描述符

        //接口2，consumer
        0x09, 0x04, 0x01, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, // 接口描述符

        0x09, 0x21, 0x00, 0x01, 0x00, 0x01, 0x22, 0x17, 0x00, // HID类描述符

        0x07, 0x05, 0x82, 0x03, 0x04, 0x00, 0x01,  // 端点描述符

        // Interface 3: Bulk Transfer Interface
        0x09,// bLength
        0x04,             // bDescriptorType
        0x02,             // bInterfaceNumber (2)
        0x00,             // bAlternateSetting
        0x02,             // bNumEndpoints (2)
        0x0A,             // bInterfaceClass (Data Interface Class)
        0x00,             // bInterfaceSubClass
        0x00,             // bInterfaceProtocol
        0x00,             // iInterface

        // Endpoint Descriptor (IN)
        0x07,// bLength
        0x05,             // bDescriptorType
        0x83,             // bEndpointAddress (IN/D2H)
        0x02,             // bmAttributes (Bulk)
        0x40, 0x00,       // wMaxPacketSize (64 bytes)
        0x00,             // bInterval (NA)

        // Endpoint Descriptor (OUT)
        0x07,// bLength
        0x05,             // bDescriptorType
        0x04,             // bEndpointAddress (OUT/H2D)
        0x02,             // bmAttributes (Bulk)
        0x40, 0x00,       // wMaxPacketSize (64 bytes)
        0x00,             // bInterval (NA)

        };

// 语言描述符
const uint8_t USB_LangId_StrDescr[] = { 0x04, 0x03, 0x09, 0x04 };

// 厂家信息
const uint8_t USB_ManuInfo_StrDescr[] = { 0x14, 0x03, 'x', 0, 'C', 0, 'h', 0,
        'e', 0, 'n', 0, 'N', 0, 'I', 0, 'n', 0, 'g', 0 };

// 产品信息
const uint8_t USB_ProdInfo_StrDescr[] = { 0x2A, 0x03, 'X', 0, 'C', 0, 'N', 0,
        ' ', 0, 'K', 0, 'e', 0, 'y', 0, 'b', 0, 'o', 0, 'a', 0, 'r', 0, 'd', 0,
        ' ', 0, 'V', 0, '5', 0, '7', 0, '3', 0, 'U', 0, 'S', 0, 'B', 0 };

// HID键盘报表描述符（Keyboard）
const uint8_t HID_KeyBoard_RepDesc[62] = {

0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x06, // USAGE (Keyboard)

        0xA1, 0x01, // COLLECTION (Application)

        // IN Byte 0 - 功能键集合
        0x05, 0x07, // USAGE_PAGE (Keyboard/Keypad)
        0x19, 0xe0, // USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7, // USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00, // LOGICAL_MINIMUM (0)
        0x25, 0x01, // LOGICAL_MAXIMUM (1)
        0x75, 0x01, // REPORT_SIZE (1)
        0x95, 0x08, // REPORT_COUNT (8)
        0x81, 0x02, // INPUT (Data,Var,Abs)

        // IN Byte 1 - 保留字节
        0x95, 0x01, // REPORT_COUNT (1)
        0x75, 0x08, // REPORT_SIZE (8)
        0x81, 0x01, // INPUT (Cnst,Var,Abs)

        // OUT Byte 0 - LSB 用于控制LED灯
        0x95, 0x03, // REPORT_COUNT (3)
        0x75, 0x01, // REPORT_SIZE (1)
        0x05, 0x08, // USAGE_PAGE (LEDs)
        0x19, 0x01, // USAGE_MINIMUM (Num Lock)
        0x29, 0x03, // USAGE_MAXIMUM (Scroll Lock)
        0x91, 0x02, // OUTPUT (Data,Var,Abs)

        // OUT Byte 0 - MSB 填充满一个字节
        0x95, 0x05, // REPORT_COUNT (5)
        0x75, 0x01, // REPORT_SIZE (1)
        0x91, 0x01, // OUTPUT (Cnst,Var,Abs)

        // IN Byte 2~7 - 普通按键
        0x95, 0x06, // REPORT_COUNT (6)
        0x75, 0x08, // REPORT_SIZE (8)
        0x26, 0xff, 0x00, // LOGICAL_MAXIMUM (255)
        0x05, 0x07, // USAGE_PAGE (Keyboard/Keypad)
        0x19, 0x00, // USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x91, // USAGE_MAXIMUM (Keyboard Right GUI)
        0x81, 0x00, // INPUT (Data,Ary,Abs)
        0xC0 // END_COLLECTION

        };

// HID多媒体报表描述符（Consumer）
const uint8_t HID_MediaCtrl_RepDesc[23] = {

// Consumer report ONLY for PC
        0x05, 0x0c,     // 主要使用 Consumer 控制编码
        0x09, 0x01,     // Usage 通用桌面控制

        0xA1, 0x01,     // Collection（Application）

        // IN Byte 0~1 - 多媒体控制码
        0x15, 0x00,         // 逻辑最小值：0
        0x26, 0xff, 0x1f,   // 逻辑最大值：0x1FFF (8191)
        0x19, 0x00,         // 使用最小值：0
        0x2A, 0xff, 0x1f,   // 使用最大值：0x1FFF (8191)
        0x75, 0x10,         // 报告大小（位）：16
        0x95, 0x02,         // 报告计数：2
        0x81, 0x00,         // 输入（数据、变量、绝对值）

        0xc0            // 结束集合

        };

#endif /* USERDRIVER_USB_USB_DESCRIPTOR_H_ */
