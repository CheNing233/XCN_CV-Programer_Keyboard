/*
 * USB.c
 *
 *  Created on: 2023��8��17��
 *      Author: 19156
 *
 *   Attention: Only for CH573F
 */

#include <CH57x_common.h>
#include "USB.h"
#include "USB_Descriptor.h"

// �˵㻺����
__attribute__((aligned(4)))       uint8_t EP0_Databuf[64 + 64 + 64]; //ep0(64)+ep4_out(64)+ep4_in(64)
__attribute__((aligned(4)))       uint8_t EP1_Databuf[64 + 64]; //ep1_out(64)+ep1_in(64)
__attribute__((aligned(4)))       uint8_t EP2_Databuf[64 + 64]; //ep2_out(64)+ep2_in(64)
__attribute__((aligned(4)))       uint8_t EP3_Databuf[64 + 64]; //ep3_out(64)+ep3_in(64)

/*
 * @brief �û�����
 */

void (*_LEDStatusChange)(uint8_t led);
void (*_SleepStatusChange)();
void _Init(USBProto_InitTypeDef *USBKB_InitStructure);

struct _USBProto_Class USBProto = { .Init = _Init };

void _Init(USBProto_InitTypeDef *USBProto_InitStructure) {

    pEP0_RAM_Addr = EP0_Databuf;
    pEP1_RAM_Addr = EP1_Databuf;
    pEP2_RAM_Addr = EP2_Databuf;

    _LEDStatusChange = USBProto_InitStructure->LEDStatusChange;
    _SleepStatusChange = USBProto_InitStructure->SleepStatusChange;
}

/*
 * @brief ���Ĵ���
 */

void DevEP1_OUT_Deal(uint8_t Upload_Length) {
    uint8_t i;

    for (i = 0; i < Upload_Length; i++) {
        pEP1_IN_DataBuf[i] = ~pEP1_OUT_DataBuf[i];
    }
    DevEP1_IN_Deal(Upload_Length);
}

void DevEP2_OUT_Deal(uint8_t l) { /* �û����Զ��� */
    uint8_t i;

    for (i = 0; i < l; i++) {
        pEP2_IN_DataBuf[i] = ~pEP2_OUT_DataBuf[i];
    }
    DevEP2_IN_Deal(l);
}

void DevEP3_OUT_Deal(uint8_t l) { /* �û����Զ��� */
    uint8_t i;

    for (i = 0; i < l; i++) {
        pEP3_IN_DataBuf[i] = ~pEP3_OUT_DataBuf[i];
    }
    DevEP3_IN_Deal(l);
}

void DevEP4_OUT_Deal(uint8_t l) { /* �û����Զ��� */
    uint8_t i;

    for (i = 0; i < l; i++) {
        pEP4_IN_DataBuf[i] = ~pEP4_OUT_DataBuf[i];
    }
    DevEP4_IN_Deal(l);
}

uint8_t DevConfig, Ready;
uint8_t SetupReqCode;
uint16_t SetupReqLen;
const uint8_t *pDescr;
uint8_t Report_Value = 0x00;
uint8_t Idle_Value = 0x00;
uint8_t USB_SleepStatus = 0x00; /* USB˯��״̬ */

void USB_DevTransProcess(void) {
    uint8_t len, chtype;
    uint8_t intflag, errflag = 0;

    intflag = R8_USB_INT_FG;
    if (intflag & RB_UIF_TRANSFER) {
        if ((R8_USB_INT_ST & MASK_UIS_TOKEN) != MASK_UIS_TOKEN) // �ǿ���
        {
            switch (R8_USB_INT_ST & (MASK_UIS_TOKEN | MASK_UIS_ENDP))
            // �����������ƺͶ˵��
            {
            case UIS_TOKEN_IN: {
                switch (SetupReqCode) {
                case USB_GET_DESCRIPTOR:
                    len = SetupReqLen >= DevEP0SIZE ? DevEP0SIZE : SetupReqLen; // ���δ��䳤��
                    memcpy(pEP0_DataBuf, pDescr, len); /* �����ϴ����� */
                    SetupReqLen -= len;
                    pDescr += len;
                    R8_UEP0_T_LEN = len;
                    R8_UEP0_CTRL ^= RB_UEP_T_TOG; // ��ת
                    break;
                case USB_SET_ADDRESS:
                    R8_USB_DEV_AD = (R8_USB_DEV_AD & RB_UDA_GP_BIT)
                            | SetupReqLen;
                    R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                    break;

                case USB_SET_FEATURE:
                    break;

                default:
                    R8_UEP0_T_LEN = 0; // ״̬�׶�����жϻ�����ǿ���ϴ�0�������ݰ��������ƴ���
                    R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                    break;
                }
            }
                break;

            case UIS_TOKEN_OUT: {
                len = R8_USB_RX_LEN;
                if (SetupReqCode == 0x09) {
                    _LEDStatusChange(pEP0_DataBuf[0]);
                    PRINT("[%s] Num Lock\t", (pEP0_DataBuf[0] & (1<<0)) ? "*" : " ");PRINT("[%s] Caps Lock\t", (pEP0_DataBuf[0] & (1<<1)) ? "*" : " ");PRINT("[%s] Scroll Lock\n", (pEP0_DataBuf[0] & (1<<2)) ? "*" : " ");
                }
            }
                break;

            case UIS_TOKEN_OUT | 1: {
                if (R8_USB_INT_ST & RB_UIS_TOG_OK) { // ��ͬ�������ݰ�������
                    R8_UEP1_CTRL ^= RB_UEP_R_TOG;
                    len = R8_USB_RX_LEN;
                    DevEP1_OUT_Deal(len);
                }
            }
                break;

            case UIS_TOKEN_IN | 1:
                R8_UEP1_CTRL ^= RB_UEP_T_TOG;
                R8_UEP1_CTRL = (R8_UEP1_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                break;

            case UIS_TOKEN_OUT | 2: {
                if (R8_USB_INT_ST & RB_UIS_TOG_OK) { // ��ͬ�������ݰ�������
                    R8_UEP2_CTRL ^= RB_UEP_R_TOG;
                    len = R8_USB_RX_LEN;
                    DevEP2_OUT_Deal(len);
                }
            }
                break;

            case UIS_TOKEN_IN | 2:
                R8_UEP2_CTRL ^= RB_UEP_T_TOG;
                R8_UEP2_CTRL = (R8_UEP2_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                break;

            case UIS_TOKEN_OUT | 3: {
                if (R8_USB_INT_ST & RB_UIS_TOG_OK) { // ��ͬ�������ݰ�������
                    R8_UEP3_CTRL ^= RB_UEP_R_TOG;
                    len = R8_USB_RX_LEN;
                    DevEP3_OUT_Deal(len);
                }
            }
                break;

            case UIS_TOKEN_IN | 3:
                R8_UEP3_CTRL ^= RB_UEP_T_TOG;
                R8_UEP3_CTRL = (R8_UEP3_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                break;

            case UIS_TOKEN_OUT | 4: {
                if (R8_USB_INT_ST & RB_UIS_TOG_OK) {
                    R8_UEP4_CTRL ^= RB_UEP_R_TOG;
                    len = R8_USB_RX_LEN;
                    DevEP4_OUT_Deal(len);
                }
            }
                break;

            case UIS_TOKEN_IN | 4:
                R8_UEP4_CTRL ^= RB_UEP_T_TOG;
                R8_UEP4_CTRL = (R8_UEP4_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                break;

            default:
                break;
            }
            R8_USB_INT_FG = RB_UIF_TRANSFER;
        }
        if (R8_USB_INT_ST & RB_UIS_SETUP_ACT) // Setup������
        {
            R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK
                    | UEP_T_RES_NAK;
            SetupReqLen = pSetupReqPak->wLength;
            SetupReqCode = pSetupReqPak->bRequest;
            chtype = pSetupReqPak->bRequestType;

            len = 0;
            errflag = 0;
            if ((pSetupReqPak->bRequestType & USB_REQ_TYP_MASK)
                    != USB_REQ_TYP_STANDARD) {
                /* �Ǳ�׼���� */
                /* ��������,�������󣬲�������� */
                if (pSetupReqPak->bRequestType & 0x40) {
                    /* �������� */
                } else if (pSetupReqPak->bRequestType & 0x20) {
                    switch (SetupReqCode) {
                    case DEF_USB_SET_IDLE: /* 0x0A: SET_IDLE */
                        Idle_Value = EP0_Databuf[3];
                        break; //���һ��Ҫ��

                    case DEF_USB_SET_REPORT: /* 0x09: SET_REPORT */
                        break;

                    case DEF_USB_SET_PROTOCOL: /* 0x0B: SET_PROTOCOL */
                        Report_Value = EP0_Databuf[2];
                        break;

                    case DEF_USB_GET_IDLE: /* 0x02: GET_IDLE */
                        EP0_Databuf[0] = Idle_Value;
                        len = 1;
                        break;

                    case DEF_USB_GET_PROTOCOL: /* 0x03: GET_PROTOCOL */
                        EP0_Databuf[0] = Report_Value;
                        len = 1;
                        break;

                    default:
                        errflag = 0xFF;
                    }
                }
            } else /* ��׼���� */
            {
                switch (SetupReqCode) {
                case USB_GET_DESCRIPTOR: {
                    switch (((pSetupReqPak->wValue) >> 8)) {
                    case USB_DESCR_TYP_DEVICE: {
                        pDescr = USB_Device_Descr;
                        len = USB_Device_Descr[0];
                    }
                        break;

                    case USB_DESCR_TYP_CONFIG: {
                        pDescr = USB_Config_Descr;
                        len = USB_Config_Descr[2];
                    }
                        break;

                    case USB_DESCR_TYP_HID:
                        switch ((pSetupReqPak->wIndex) & 0xff) {
                        /* ѡ��ӿ� */
                        case 0:
                            pDescr = (uint8_t *) (&USB_Config_Descr[18]);
                            len = 9;
                            break;

                        case 1:
                            pDescr = (uint8_t *) (&USB_Config_Descr[43]);
                            len = 9;
                            break;

                        default:
                            /* ��֧�ֵ��ַ��������� */
                            errflag = 0xff;
                            break;
                        }
                        break;

                    case USB_DESCR_TYP_REPORT: {
                        if (((pSetupReqPak->wIndex) & 0xff) == 0) //�ӿ�0����������
                                {
                            pDescr = HID_KeyBoard_RepDesc; //����׼���ϴ�
                            len = sizeof(HID_KeyBoard_RepDesc);
                        } else if (((pSetupReqPak->wIndex) & 0xff) == 1) //�ӿ�1����������
                                {
                            pDescr = HID_MediaCtrl_RepDesc; //����׼���ϴ�
                            len = sizeof(HID_MediaCtrl_RepDesc);
                            Ready = 1; //����и���ӿڣ��ñ�׼λӦ�������һ���ӿ�������ɺ���Ч
                        } else
                            len = 0xff; //������ֻ��2���ӿڣ���仰����������ִ��
                    }
                        break;

                    case USB_DESCR_TYP_STRING: {
                        switch ((pSetupReqPak->wValue) & 0xff) {
                        case 1:
                            pDescr = USB_ManuInfo_StrDescr;
                            len = USB_ManuInfo_StrDescr[0];
                            break;
                        case 2:
                            pDescr = USB_ProdInfo_StrDescr;
                            len = USB_ProdInfo_StrDescr[0];
                            break;
                        case 0:
                            pDescr = USB_LangId_StrDescr;
                            len = USB_LangId_StrDescr[0];
                            break;
                        default:
                            errflag = 0xFF; // ��֧�ֵ��ַ���������
                            break;
                        }
                    }
                        break;

                    default:
                        errflag = 0xff;
                        break;
                    }
                    if (SetupReqLen > len)
                        SetupReqLen = len; //ʵ�����ϴ��ܳ���
                    len = (SetupReqLen >= DevEP0SIZE) ?
                    DevEP0SIZE :
                                                        SetupReqLen;
                    memcpy(pEP0_DataBuf, pDescr, len);
                    pDescr += len;
                }
                    break;

                case USB_SET_ADDRESS:
                    SetupReqLen = (pSetupReqPak->wValue) & 0xff;
                    break;

                case USB_GET_CONFIGURATION:
                    pEP0_DataBuf[0] = DevConfig;
                    if (SetupReqLen > 1)
                        SetupReqLen = 1;
                    break;

                case USB_SET_CONFIGURATION:
                    DevConfig = (pSetupReqPak->wValue) & 0xff;
                    break;

                case USB_CLEAR_FEATURE: {
                    if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK)
                            == USB_REQ_RECIP_ENDP) // �˵�
                    {
                        switch ((pSetupReqPak->wIndex) & 0xff) {
                        case 0x83:
                            R8_UEP3_CTRL = (R8_UEP3_CTRL
                                    & ~(RB_UEP_T_TOG | MASK_UEP_T_RES))
                                    | UEP_T_RES_NAK;
                            break;
                        case 0x03:
                            R8_UEP3_CTRL = (R8_UEP3_CTRL
                                    & ~(RB_UEP_R_TOG | MASK_UEP_R_RES))
                                    | UEP_R_RES_ACK;
                            break;
                        case 0x82:
                            R8_UEP2_CTRL = (R8_UEP2_CTRL
                                    & ~(RB_UEP_T_TOG | MASK_UEP_T_RES))
                                    | UEP_T_RES_NAK;
                            break;
                        case 0x02:
                            R8_UEP2_CTRL = (R8_UEP2_CTRL
                                    & ~(RB_UEP_R_TOG | MASK_UEP_R_RES))
                                    | UEP_R_RES_ACK;
                            break;
                        case 0x81:
                            R8_UEP1_CTRL = (R8_UEP1_CTRL
                                    & ~(RB_UEP_T_TOG | MASK_UEP_T_RES))
                                    | UEP_T_RES_NAK;
                            break;
                        case 0x01:
                            R8_UEP1_CTRL = (R8_UEP1_CTRL
                                    & ~(RB_UEP_R_TOG | MASK_UEP_R_RES))
                                    | UEP_R_RES_ACK;
                            break;
                        default:
                            errflag = 0xFF; // ��֧�ֵĶ˵�
                            break;
                        }
                    } else if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK)
                            == USB_REQ_RECIP_DEVICE) {
                        if (pSetupReqPak->wValue == 1) {
                            USB_SleepStatus &= ~0x01;
                        }
                    } else {
                        errflag = 0xFF;
                    }
                }
                    break;

                case USB_SET_FEATURE:
                    if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK)
                            == USB_REQ_RECIP_ENDP) {
                        /* �˵� */
                        switch (pSetupReqPak->wIndex) {
                        case 0x83:
                            R8_UEP3_CTRL = (R8_UEP3_CTRL
                                    & ~(RB_UEP_T_TOG | MASK_UEP_T_RES))
                                    | UEP_T_RES_STALL;
                            break;
                        case 0x03:
                            R8_UEP3_CTRL = (R8_UEP3_CTRL
                                    & ~(RB_UEP_R_TOG | MASK_UEP_R_RES))
                                    | UEP_R_RES_STALL;
                            break;
                        case 0x82:
                            R8_UEP2_CTRL = (R8_UEP2_CTRL
                                    & ~(RB_UEP_T_TOG | MASK_UEP_T_RES))
                                    | UEP_T_RES_STALL;
                            break;
                        case 0x02:
                            R8_UEP2_CTRL = (R8_UEP2_CTRL
                                    & ~(RB_UEP_R_TOG | MASK_UEP_R_RES))
                                    | UEP_R_RES_STALL;
                            break;
                        case 0x81:
                            R8_UEP1_CTRL = (R8_UEP1_CTRL
                                    & ~(RB_UEP_T_TOG | MASK_UEP_T_RES))
                                    | UEP_T_RES_STALL;
                            break;
                        case 0x01:
                            R8_UEP1_CTRL = (R8_UEP1_CTRL
                                    & ~(RB_UEP_R_TOG | MASK_UEP_R_RES))
                                    | UEP_R_RES_STALL;
                            break;
                        default:
                            /* ��֧�ֵĶ˵� */
                            errflag = 0xFF; // ��֧�ֵĶ˵�
                            break;
                        }
                    } else if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK)
                            == USB_REQ_RECIP_DEVICE) {
                        if (pSetupReqPak->wValue == 1) {
                            /* ����˯�� */
                            USB_SleepStatus |= 0x01;
                        }
                    } else {
                        errflag = 0xFF;
                    }
                    break;

                case USB_GET_INTERFACE:
                    pEP0_DataBuf[0] = 0x00;
                    if (SetupReqLen > 1)
                        SetupReqLen = 1;
                    break;

                case USB_SET_INTERFACE:
                    break;

                case USB_GET_STATUS:
                    if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK)
                            == USB_REQ_RECIP_ENDP) {
                        /* �˵� */
                        pEP0_DataBuf[0] = 0x00;
                        switch (pSetupReqPak->wIndex) {
                        case 0x83:
                            if ((R8_UEP3_CTRL & (RB_UEP_T_TOG | MASK_UEP_T_RES))
                                    == UEP_T_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;

                        case 0x03:
                            if ((R8_UEP3_CTRL & (RB_UEP_R_TOG | MASK_UEP_R_RES))
                                    == UEP_R_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;

                        case 0x82:
                            if ((R8_UEP2_CTRL & (RB_UEP_T_TOG | MASK_UEP_T_RES))
                                    == UEP_T_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;

                        case 0x02:
                            if ((R8_UEP2_CTRL & (RB_UEP_R_TOG | MASK_UEP_R_RES))
                                    == UEP_R_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;

                        case 0x81:
                            if ((R8_UEP1_CTRL & (RB_UEP_T_TOG | MASK_UEP_T_RES))
                                    == UEP_T_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;

                        case 0x01:
                            if ((R8_UEP1_CTRL & (RB_UEP_R_TOG | MASK_UEP_R_RES))
                                    == UEP_R_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;
                        }
                    } else if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK)
                            == USB_REQ_RECIP_DEVICE) {
                        pEP0_DataBuf[0] = 0x00;
                        if (USB_SleepStatus) {
                            pEP0_DataBuf[0] = 0x02;
                        } else {
                            pEP0_DataBuf[0] = 0x00;
                        }
                    }
                    pEP0_DataBuf[1] = 0;
                    if (SetupReqLen >= 2) {
                        SetupReqLen = 2;
                    }
                    break;

                default:
                    errflag = 0xff;
                    break;
                }
            }
            if (errflag == 0xff) // �����֧��
                    {
                //                  SetupReqCode = 0xFF;
                R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_STALL
                        | UEP_T_RES_STALL; // STALL
            } else {
                if (chtype & 0x80) // �ϴ�
                        {
                    len = (SetupReqLen > DevEP0SIZE) ? DevEP0SIZE : SetupReqLen;
                    SetupReqLen -= len;
                } else
                    len = 0; // �´�
                R8_UEP0_T_LEN = len;
                R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK
                        | UEP_T_RES_ACK; // Ĭ�����ݰ���DATA1
            }

            R8_USB_INT_FG = RB_UIF_TRANSFER;
        }
    } else if (intflag & RB_UIF_BUS_RST) {
        R8_USB_DEV_AD = 0;
        R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        R8_UEP1_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        R8_UEP2_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        R8_UEP3_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        R8_USB_INT_FG = RB_UIF_BUS_RST;
    } else if (intflag & RB_UIF_SUSPEND) {
        if (R8_USB_MIS_ST & RB_UMS_SUSPEND) {
            ;
        } // ����
        else {
            ;
        } // ����
        R8_USB_INT_FG = RB_UIF_SUSPEND;
    } else {
        R8_USB_INT_FG = intflag;
    }
}
