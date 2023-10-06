/*
 * USB_Descriptor.h
 *
 *  Created on: 2023��8��24��
 *      Author: 19156
 */

#ifndef USERDRIVER_USB_USB_DESCRIPTOR_H_
#define USERDRIVER_USB_USB_DESCRIPTOR_H_

#include "usercfg.h"

// �˵�0������ݰ����� == 64�ֽ�
#define DevEP0SIZE 0x40

// �豸������
const uint8_t USB_Device_Descr[] = { 0x12, // ����������Ϊ18�ֽ�
        0x01, // ����������Ϊ�豸������
        0x10, 0x01, // ֧�ֵ�USB�淶�汾��Ϊ1.1
        0x00, // �豸�����Ϊδָ��
        0x00, // �豸�������Ϊδָ��
        0x00, // �豸Э�����Ϊδָ��
        DevEP0SIZE, // ������ݰ��ߴ�ΪDevEP0SIZE == 64
        0x3d, 0x41, // �豸����IDΪ0x3d41
        0x07, 0x21, // �豸��ƷIDΪ0x0721
        0x00, 0x00, // �豸�汾��Ϊ0.0
        0x01, // �����ַ���������������Ϊ0
        0x02, // ��Ʒ�ַ���������������Ϊ0
        0x00, // ���к��ַ���������������Ϊ0
        0x01 // �豸֧�ֵ���������Ϊ1
        };

// ����������
uint8_t USB_Config_Descr[] = {

0x09,       //bLength�ֶΡ������������ĳ���Ϊ9�ֽ�
        0x02,       //bDescriptorType�ֶΡ��������������Ϊ0x02
        0x52,       //wTotalLength�ֶΡ��������������ϵ��ܳ���0x003b��������������������������HID����������
        0x00, 0x03, //bNumInterfaces�ֶΡ������ð����Ľӿ�����ֻ��2���ӿ�
        0x01,       //bConfiguration�ֶΡ������õ�ֵΪ1
        0x01,       //iConfigurationz�ֶΣ������õ��ַ���������
        0xA0,       //bmAttributes�ֶ�,bit4-bit7�����豸������
        0x64,       //bMaxPower�ֶΣ����豸��Ҫ������������ÿ��λ����Ϊ 2 mA

        //�ӿ�1��keyboard
        0x09, 0x04, 0x00, 0x00, 0x01, 0x03, 0x01, 0x01, 0x00, //�ӿ�������

        0x09, 0x21, 0x11, 0x01, 0x00, 0x01, 0x22, 0x3e, 0x00, //HID��������

        0x07, 0x05, 0x81, 0x03, 0x08, 0x00, 0x01, //�˵�������

        //�ӿ�2��consumer
        0x09, 0x04, 0x01, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, // �ӿ�������

        0x09, 0x21, 0x00, 0x01, 0x00, 0x01, 0x22, 0x17, 0x00, // HID��������

        0x07, 0x05, 0x82, 0x03, 0x04, 0x00, 0x01,  // �˵�������

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

// ����������
const uint8_t USB_LangId_StrDescr[] = { 0x04, 0x03, 0x09, 0x04 };

// ������Ϣ
const uint8_t USB_ManuInfo_StrDescr[] = { 0x14, 0x03, 'x', 0, 'C', 0, 'h', 0,
        'e', 0, 'n', 0, 'N', 0, 'I', 0, 'n', 0, 'g', 0 };

// ��Ʒ��Ϣ
const uint8_t USB_ProdInfo_StrDescr[] = { 0x2A, 0x03, 'X', 0, 'C', 0, 'N', 0,
        ' ', 0, 'K', 0, 'e', 0, 'y', 0, 'b', 0, 'o', 0, 'a', 0, 'r', 0, 'd', 0,
        ' ', 0, 'V', 0, '5', 0, '7', 0, '3', 0, 'U', 0, 'S', 0, 'B', 0 };

// HID���̱�����������Keyboard��
const uint8_t HID_KeyBoard_RepDesc[62] = {

0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x06, // USAGE (Keyboard)

        0xA1, 0x01, // COLLECTION (Application)

        // IN Byte 0 - ���ܼ�����
        0x05, 0x07, // USAGE_PAGE (Keyboard/Keypad)
        0x19, 0xe0, // USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7, // USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00, // LOGICAL_MINIMUM (0)
        0x25, 0x01, // LOGICAL_MAXIMUM (1)
        0x75, 0x01, // REPORT_SIZE (1)
        0x95, 0x08, // REPORT_COUNT (8)
        0x81, 0x02, // INPUT (Data,Var,Abs)

        // IN Byte 1 - �����ֽ�
        0x95, 0x01, // REPORT_COUNT (1)
        0x75, 0x08, // REPORT_SIZE (8)
        0x81, 0x01, // INPUT (Cnst,Var,Abs)

        // OUT Byte 0 - LSB ���ڿ���LED��
        0x95, 0x03, // REPORT_COUNT (3)
        0x75, 0x01, // REPORT_SIZE (1)
        0x05, 0x08, // USAGE_PAGE (LEDs)
        0x19, 0x01, // USAGE_MINIMUM (Num Lock)
        0x29, 0x03, // USAGE_MAXIMUM (Scroll Lock)
        0x91, 0x02, // OUTPUT (Data,Var,Abs)

        // OUT Byte 0 - MSB �����һ���ֽ�
        0x95, 0x05, // REPORT_COUNT (5)
        0x75, 0x01, // REPORT_SIZE (1)
        0x91, 0x01, // OUTPUT (Cnst,Var,Abs)

        // IN Byte 2~7 - ��ͨ����
        0x95, 0x06, // REPORT_COUNT (6)
        0x75, 0x08, // REPORT_SIZE (8)
        0x26, 0xff, 0x00, // LOGICAL_MAXIMUM (255)
        0x05, 0x07, // USAGE_PAGE (Keyboard/Keypad)
        0x19, 0x00, // USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x91, // USAGE_MAXIMUM (Keyboard Right GUI)
        0x81, 0x00, // INPUT (Data,Ary,Abs)
        0xC0 // END_COLLECTION

        };

// HID��ý�屨����������Consumer��
const uint8_t HID_MediaCtrl_RepDesc[23] = {

// Consumer report ONLY for PC
        0x05, 0x0c,     // ��Ҫʹ�� Consumer ���Ʊ���
        0x09, 0x01,     // Usage ͨ���������

        0xA1, 0x01,     // Collection��Application��

        // IN Byte 0~1 - ��ý�������
        0x15, 0x00,         // �߼���Сֵ��0
        0x26, 0xff, 0x1f,   // �߼����ֵ��0x1FFF (8191)
        0x19, 0x00,         // ʹ����Сֵ��0
        0x2A, 0xff, 0x1f,   // ʹ�����ֵ��0x1FFF (8191)
        0x75, 0x10,         // �����С��λ����16
        0x95, 0x02,         // ���������2
        0x81, 0x00,         // ���루���ݡ�����������ֵ��

        0xc0            // ��������

        };

#endif /* USERDRIVER_USB_USB_DESCRIPTOR_H_ */
