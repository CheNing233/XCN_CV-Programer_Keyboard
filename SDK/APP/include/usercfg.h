/*
 * usercfg.h
 *
 *  Created on: 2023��9��24��
 *      Author: 19156
 */

#ifndef INCLUDE_USERCFG_H_
#define INCLUDE_USERCFG_H_

#define USERCFG_ROM_ADDR 0x0

#define KEYCFG_ROM_X 0x1000
#define KEYCFG_ROM_C 0x2000
#define KEYCFG_ROM_V 0x3000
#define KEYCFG_ROM_CTRL 0x4000
#define KEYCFG_ROM_ENTER 0x5000

#define KEYCFG_ROM_RL 0x6000
#define KEYCFG_ROM_RR 0x7000

#define KEYCFG_ROM_RBT 0x0500

typedef struct __PACKED _usercfg {
    uint8_t Init_Flag;// �ѳ�ʼ����ROM��־

    uint32_t Proto_FreshState_Interval;// Э��״̬ˢ����ѯ���
    uint8_t Proto_USBBuffer_PushInterval;// USB���ͼ��
    uint8_t Proto_BLEBuffer_PushInterval;// BLE���ͼ��

    uint8_t KeyIn_Debouncing_Sampling_Interval;// ����ѭ��ɨ��������
    uint8_t KeyIn_Debouncing_DelayCircle_Cnt;// ���������ӳ�ѭ����

    uint8_t USB_UploadRate;// USB�жϴ�����ѯ���
    uint8_t BLE_Uplaod_PackCnt;// BLEÿ�η��Ͱ�����

} usercfg;

typedef struct __PACKED _keycfg{
    uint8_t Init_Flag;

    uint8_t Set_Keys[8];
    uint8_t Set_Csms[4];
    uint8_t Reset_Keys[8];
    uint8_t Reset_Csms[4];

    uint8_t FinishTsk_PushCnt;
    uint8_t FinishTsk_RlseCnt;
    uint8_t FinishTsk_HoldCnt;

    uint32_t SwitchKeys_DelayCnt;

    uint32_t NextPos_Relative;
    uint8_t Reset_Flag;
} keycfg;


extern usercfg UserCfg_RAM;

extern keycfg KeyCfg_RAM_X;
extern keycfg KeyCfg_RAM_C;
extern keycfg KeyCfg_RAM_V;
extern keycfg KeyCfg_RAM_CTRL;
extern keycfg KeyCfg_RAM_ENTER;
extern keycfg KeyCfg_RAM_RBT;
extern keycfg KeyCfg_RAM_RL;
extern keycfg KeyCfg_RAM_RR;

extern void UserCfg_Init();

extern void KeyCfg_JumpNext(uint32_t StartPos, keycfg* P_KeyCfg);
extern void KeyCfg_Reset(uint32_t StartPos, keycfg* P_KeyCfg);

#endif /* INCLUDE_USERCFG_H_ */