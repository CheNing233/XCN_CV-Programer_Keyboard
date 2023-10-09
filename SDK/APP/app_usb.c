/*
 * USB.c
 *
 *  Created on: 2023年8月17日
 *      Author: 19156
 *
 *   Attention: Only for CH573F
 */

#include "config.h"
#include "app_usb.h"
#include "app_usb_decr.h"
#include "usercfg.h"

// 端点缓存区
__attribute__((aligned(4)))               uint8_t EP0_Databuf[64 + 64 + 64]; //ep0(64)+ep4_out(64)+ep4_in(64)
__attribute__((aligned(4)))               uint8_t EP1_Databuf[64 + 64]; //ep1_out(64)+ep1_in(64)
__attribute__((aligned(4)))               uint8_t EP2_Databuf[64 + 64]; //ep2_out(64)+ep2_in(64)
__attribute__((aligned(4)))               uint8_t EP3_Databuf[64 + 64]; //ep3_out(64)+ep3_in(64)

/*
 * @brief 用户代码
 */

void USB_Init() {

    pEP0_RAM_Addr = EP0_Databuf;
    pEP1_RAM_Addr = EP1_Databuf;
    pEP2_RAM_Addr = EP2_Databuf;
    pEP3_RAM_Addr = EP3_Databuf;

    USB_DeviceInit();

    PFIC_EnableIRQ(USB_IRQn);

}

void USB_CB_LightChange(uint8_t light_state) {

}

void USB_BulkTrans(uint8_t length, uint8_t cmdkey) {

//
//    if (pEP4_OUT_DataBuf[0] == 'w') {
//        //擦除数据
//        //这里的length 是字节,但是实际的擦除是按照256字节高位对齐,比如传入257字节,实际是擦除了512字节.
//        //擦除后的区域,使用EEPROM_READ读出来默认是0xff,使用指针方式绝对地址读取,非0xff
//        //传入的地址是相对地址,0对应dataflash的起始地址
//        len = pEP4_OUT_DataBuf[1];
//
//        EEPROM_ERASE(0, 256);
//
//        //写入数据
//        //这里的buffer是需要写入的指针数据,不需要进行4字节对齐,数据长度是1的倍数,数据需要在RAM里面
//        //传入的地址是相对地址,0对应dataflash的起始地址
//        EEPROM_WRITE(0, pEP4_OUT_DataBuf+2, len);
//
//        // ACK
//        pEP3_IN_DataBuf[0] = 66;
//        DevEP3_IN_Deal(1);
//    }
//
//    if (pEP4_OUT_DataBuf[0] == 'r') {
//        len = pEP4_OUT_DataBuf[1];
//
//        EEPROM_READ(0, pEP3_IN_DataBuf, len);
//        DevEP3_IN_Deal(len);
//    }
//
//    if (pEP4_OUT_DataBuf[0] == 'u') {
//
//        tmos_memcpy(pEP3_IN_DataBuf, &UserCfg_RAM, sizeof(usercfg));
//
//        DevEP3_IN_Deal(sizeof(usercfg));
//
//    }

    uint16_t keyset_addr = 0;

    keycfg temp_keycfg = {
        0
    };

    switch (cmdkey) {
    case CMD_R_CHECK_VALID:
        pEP3_IN_DataBuf[0] = 233;
        pEP3_IN_DataBuf[1] = 0;
        pEP3_IN_DataBuf[2] = 0;
        pEP3_IN_DataBuf[3] = 1;

        DevEP3_IN_Deal(4);
        break;

    case CMD_R_USERCFG:
        UserCfg_Read_Setting();
        tmos_memcpy(pEP3_IN_DataBuf, &UserCfg_RAM, sizeof(usercfg));
        DevEP3_IN_Deal(sizeof(usercfg));
        break;

    case CMD_W_USERCFG:
        tmos_memcpy(&UserCfg_RAM, pEP4_OUT_DataBuf + 1, length - 1);
        UserCfg_Write_Setting(((uint8_t*) &UserCfg_RAM));
        pEP3_IN_DataBuf[0] = length;
        DevEP3_IN_Deal(1);
        break;

    case CMD_R_KEYSET:
        switch (pEP4_OUT_DataBuf[1]) {
            case 0:
                keyset_addr = KEYCFG_ROM_X;
                break;
            case 1:
                keyset_addr = KEYCFG_ROM_C;
                break;
            case 2:
                keyset_addr = KEYCFG_ROM_V;
                break;
            case 3:
                keyset_addr = KEYCFG_ROM_CTRL;
                break;
            case 4:
                keyset_addr = KEYCFG_ROM_ENTER;
                break;
            case 5:
                keyset_addr = KEYCFG_ROM_RBT;
                break;
            case 6:
                keyset_addr = KEYCFG_ROM_RL;
                break;
            case 7:
                keyset_addr = KEYCFG_ROM_RR;
                break;
        }

        if(keyset_addr == 0)
            break;

        KeyCfg_Read_Setting(((uint8_t*)&temp_keycfg), keyset_addr, pEP4_OUT_DataBuf[2]);

        if(temp_keycfg.Init_Flag != sizeof(keycfg))
            break;

        tmos_memcpy(pEP3_IN_DataBuf, &temp_keycfg, sizeof(keycfg));
        DevEP3_IN_Deal(sizeof(keycfg));
        break;
    case CMD_W_KEYSET:
        switch (pEP4_OUT_DataBuf[1]) {
            case 0:
                keyset_addr = KEYCFG_ROM_X;
                break;
            case 1:
                keyset_addr = KEYCFG_ROM_C;
                break;
            case 2:
                keyset_addr = KEYCFG_ROM_V;
                break;
            case 3:
                keyset_addr = KEYCFG_ROM_CTRL;
                break;
            case 4:
                keyset_addr = KEYCFG_ROM_ENTER;
                break;
            case 5:
                keyset_addr = KEYCFG_ROM_RBT;
                break;
            case 6:
                keyset_addr = KEYCFG_ROM_RL;
                break;
            case 7:
                keyset_addr = KEYCFG_ROM_RR;
                break;
        }

        if(keyset_addr == 0)
            break;

        tmos_memcpy(&temp_keycfg, pEP4_OUT_DataBuf + 3, sizeof(keycfg));

        KeyCfg_Write_Setting(((uint8_t*)&temp_keycfg), keyset_addr, pEP4_OUT_DataBuf[2]);

        pEP3_IN_DataBuf[0] = length;
        DevEP3_IN_Deal(1);

        break;
    default:
        break;
    }
}

__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode"))) void USB_IRQHandler(void) {
    // USB中断服务程序,使用寄存器组1
    USB_DevTransProcess();
}

/*
 * @brief 核心代码
 */

void DevEP1_OUT_Deal(uint8_t l) {
    return;
}

void DevEP2_OUT_Deal(uint8_t l) {
    return;
}

void DevEP3_OUT_Deal(uint8_t l) {
    return;
}

// OUT EP
void DevEP4_OUT_Deal(uint8_t l) { /* 用户可自定义 */
    USB_BulkTrans(l, pEP4_OUT_DataBuf[0]);
    return;
}

uint8_t DevConfig, Ready;
uint8_t SetupReqCode;
uint16_t SetupReqLen;
const uint8_t *pDescr;
uint8_t Report_Value = 0x00;
uint8_t Idle_Value = 0x00;
uint8_t USB_SleepStatus = 0x00; /* USB睡眠状态 */

void USB_DevTransProcess(void) {
    uint8_t len, chtype;
    uint8_t intflag, errflag = 0;

    intflag = R8_USB_INT_FG;
    if (intflag & RB_UIF_TRANSFER) {
        if ((R8_USB_INT_ST & MASK_UIS_TOKEN) != MASK_UIS_TOKEN) // 非空闲
        {
            switch (R8_USB_INT_ST & (MASK_UIS_TOKEN | MASK_UIS_ENDP))
            // 分析操作令牌和端点号
            {
            case UIS_TOKEN_IN: {
                switch (SetupReqCode) {
                case USB_GET_DESCRIPTOR:
                    len = SetupReqLen >= DevEP0SIZE ? DevEP0SIZE : SetupReqLen; // 本次传输长度
                    memcpy(pEP0_DataBuf, pDescr, len); /* 加载上传数据 */
                    SetupReqLen -= len;
                    pDescr += len;
                    R8_UEP0_T_LEN = len;
                    R8_UEP0_CTRL ^= RB_UEP_T_TOG; // 翻转
                    break;
                case USB_SET_ADDRESS:
                    R8_USB_DEV_AD = (R8_USB_DEV_AD & RB_UDA_GP_BIT) | SetupReqLen;
                    R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                    break;

                case USB_SET_FEATURE:
                    break;

                default:
                    R8_UEP0_T_LEN = 0; // 状态阶段完成中断或者是强制上传0长度数据包结束控制传输
                    R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                    break;
                }
            }
                break;

            case UIS_TOKEN_OUT: {
                len = R8_USB_RX_LEN;
                if (SetupReqCode == 0x09) {
                    USB_CB_LightChange(pEP0_DataBuf[0]);
                    PRINT("[%s] Num Lock\t", (pEP0_DataBuf[0] & (1<<0)) ? "*" : " ");PRINT("[%s] Caps Lock\t", (pEP0_DataBuf[0] & (1<<1)) ? "*" : " ");PRINT("[%s] Scroll Lock\n", (pEP0_DataBuf[0] & (1<<2)) ? "*" : " ");
                }
            }
                break;

            case UIS_TOKEN_OUT | 1: {
                if (R8_USB_INT_ST & RB_UIS_TOG_OK) { // 不同步的数据包将丢弃
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
                if (R8_USB_INT_ST & RB_UIS_TOG_OK) { // 不同步的数据包将丢弃
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
                if (R8_USB_INT_ST & RB_UIS_TOG_OK) { // 不同步的数据包将丢弃
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
        if (R8_USB_INT_ST & RB_UIS_SETUP_ACT) // Setup包处理
        {
            R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
            SetupReqLen = pSetupReqPak->wLength;
            SetupReqCode = pSetupReqPak->bRequest;
            chtype = pSetupReqPak->bRequestType;

            len = 0;
            errflag = 0;
            if ((pSetupReqPak->bRequestType & USB_REQ_TYP_MASK) != USB_REQ_TYP_STANDARD) {
                /* 非标准请求 */
                /* 其它请求,如类请求，产商请求等 */
                if (pSetupReqPak->bRequestType & 0x40) {
                    /* 厂商请求 */
                } else if (pSetupReqPak->bRequestType & 0x20) {
                    switch (SetupReqCode) {
                    case DEF_USB_SET_IDLE: /* 0x0A: SET_IDLE */
                        Idle_Value = EP0_Databuf[3];
                        break; //这个一定要有

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
            } else /* 标准请求 */
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

                        USB_Config_Descr[33] = UserCfg_RAM.USB_UploadRate;
                        USB_Config_Descr[58] = UserCfg_RAM.USB_UploadRate;

                        len = USB_Config_Descr[2];
                    }
                        break;

                    case USB_DESCR_TYP_HID:
                        switch ((pSetupReqPak->wIndex) & 0xff) {
                        /* 选择接口 */
                        case 0:
                            pDescr = (uint8_t *) (&USB_Config_Descr[18]);
                            len = 9;
                            break;

                        case 1:
                            pDescr = (uint8_t *) (&USB_Config_Descr[43]);
                            len = 9;
                            break;

                        default:
                            /* 不支持的字符串描述符 */
                            errflag = 0xff;
                            break;
                        }
                        break;

                    case USB_DESCR_TYP_REPORT: {
                        if (((pSetupReqPak->wIndex) & 0xff) == 0) //接口0报表描述符
                            {
                            pDescr = HID_KeyBoard_RepDesc; //数据准备上传
                            len = sizeof(HID_KeyBoard_RepDesc);
                        } else if (((pSetupReqPak->wIndex) & 0xff) == 1) //接口1报表描述符
                            {
                            pDescr = HID_MediaCtrl_RepDesc; //数据准备上传
                            len = sizeof(HID_MediaCtrl_RepDesc);

                        } else if (((pSetupReqPak->wIndex) & 0xff) == 2) {

                            Ready = 1; //如果有更多接口，该标准位应该在最后一个接口配置完成后有效

                        }
                        len = 0xff; //本程序只有2个接口，这句话正常不可能执行
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
                            errflag = 0xFF; // 不支持的字符串描述符
                            break;
                        }
                    }
                        break;

                    default:
                        errflag = 0xff;
                        break;
                    }
                    if (SetupReqLen > len)
                        SetupReqLen = len; //实际需上传总长度
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
                    if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_ENDP) // 端点
                    {
                        switch ((pSetupReqPak->wIndex) & 0xff) {
                        case 0x83:
                            R8_UEP3_CTRL = (R8_UEP3_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_NAK;
                            break;
                        case 0x03:
                            R8_UEP3_CTRL = (R8_UEP3_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_ACK;
                            break;
                        case 0x82:
                            R8_UEP2_CTRL = (R8_UEP2_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_NAK;
                            break;
                        case 0x02:
                            R8_UEP2_CTRL = (R8_UEP2_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_ACK;
                            break;
                        case 0x81:
                            R8_UEP1_CTRL = (R8_UEP1_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_NAK;
                            break;
                        case 0x01:
                            R8_UEP1_CTRL = (R8_UEP1_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_ACK;
                            break;
                        default:
                            errflag = 0xFF; // 不支持的端点
                            break;
                        }
                    } else if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_DEVICE) {
                        if (pSetupReqPak->wValue == 1) {
                            USB_SleepStatus &= ~0x01;
                        }
                    } else {
                        errflag = 0xFF;
                    }
                }
                    break;

                case USB_SET_FEATURE:
                    if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_ENDP) {
                        /* 端点 */
                        switch (pSetupReqPak->wIndex) {
                        case 0x83:
                            R8_UEP3_CTRL = (R8_UEP3_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_STALL;
                            break;
                        case 0x03:
                            R8_UEP3_CTRL = (R8_UEP3_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_STALL;
                            break;
                        case 0x82:
                            R8_UEP2_CTRL = (R8_UEP2_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_STALL;
                            break;
                        case 0x02:
                            R8_UEP2_CTRL = (R8_UEP2_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_STALL;
                            break;
                        case 0x81:
                            R8_UEP1_CTRL = (R8_UEP1_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_STALL;
                            break;
                        case 0x01:
                            R8_UEP1_CTRL = (R8_UEP1_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_STALL;
                            break;
                        default:
                            /* 不支持的端点 */
                            errflag = 0xFF; // 不支持的端点
                            break;
                        }
                    } else if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_DEVICE) {
                        if (pSetupReqPak->wValue == 1) {
                            /* 设置睡眠 */
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
                    if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_ENDP) {
                        /* 端点 */
                        pEP0_DataBuf[0] = 0x00;
                        switch (pSetupReqPak->wIndex) {
                        case 0x83:
                            if ((R8_UEP3_CTRL & (RB_UEP_T_TOG | MASK_UEP_T_RES)) == UEP_T_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;

                        case 0x03:
                            if ((R8_UEP3_CTRL & (RB_UEP_R_TOG | MASK_UEP_R_RES)) == UEP_R_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;

                        case 0x82:
                            if ((R8_UEP2_CTRL & (RB_UEP_T_TOG | MASK_UEP_T_RES)) == UEP_T_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;

                        case 0x02:
                            if ((R8_UEP2_CTRL & (RB_UEP_R_TOG | MASK_UEP_R_RES)) == UEP_R_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;

                        case 0x81:
                            if ((R8_UEP1_CTRL & (RB_UEP_T_TOG | MASK_UEP_T_RES)) == UEP_T_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;

                        case 0x01:
                            if ((R8_UEP1_CTRL & (RB_UEP_R_TOG | MASK_UEP_R_RES)) == UEP_R_RES_STALL) {
                                pEP0_DataBuf[0] = 0x01;
                            }
                            break;
                        }
                    } else if ((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_DEVICE) {
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
            if (errflag == 0xff) // 错误或不支持
                {
                //                  SetupReqCode = 0xFF;
                R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL; // STALL
            } else {
                if (chtype & 0x80) // 上传
                    {
                    len = (SetupReqLen > DevEP0SIZE) ? DevEP0SIZE : SetupReqLen;
                    SetupReqLen -= len;
                } else
                    len = 0; // 下传
                R8_UEP0_T_LEN = len;
                R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK; // 默认数据包是DATA1
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
        } // 挂起
        else {
            ;
        } // 唤醒
        R8_USB_INT_FG = RB_UIF_SUSPEND;
    } else {
        R8_USB_INT_FG = intflag;
    }
}

