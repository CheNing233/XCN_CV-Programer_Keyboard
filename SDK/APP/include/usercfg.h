/*
 * usercfg.h
 *
 *  Created on: 2023年9月24日
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

typedef enum {
    CMD_R_CHECK_VALID,
    CMD_W_USERCFG,
    CMD_R_USERCFG,
    CMD_W_KEYSET,
    CMD_R_KEYSET
} cmd_index;

typedef struct __PACKED _usercfg {
    uint8_t Init_Flag; // 已初始化到ROM标志

    uint32_t Proto_FreshState_Interval;// 协议状态刷新轮询间隔
    uint8_t Proto_USBBuffer_PushInterval;// USB推送间隔
    uint8_t Proto_BLEBuffer_PushInterval;// BLE推送间隔

    uint8_t KeyIn_Key_Debouncing_Sampling_Interval;// 键盘循环扫描采样间隔
    uint8_t KeyIn_Enco_Debouncing_Sampling_Interval;// 编码器循环扫描采样间隔

    uint8_t KeyIn_Debouncing_DelayCircle_Cnt;// 键盘消抖延迟循环数

    uint8_t KeyIn_TaskFlgManager_Circle_Interval;// 任务标志更新间隔
    uint8_t KeyIn_TransMacro_Circle_Interval;// 宏翻译间隔

    uint8_t USB_UploadRate;// USB中断传输轮询间隔
    uint8_t BLE_Conn_Interval;// BLE扫描间隔

    uint8_t BLE_Uplaod_PackCnt;// BLE每次发送包数量

} usercfg;

typedef struct __PACKED _keycfg {
    uint8_t Init_Flag;

    uint8_t Set_Keys[8];
    uint8_t Set_Csms[4];
    uint8_t Reset_Keys[8];
    uint8_t Reset_Csms[4];

    uint8_t FinishTsk_PushCnt;
    uint8_t FinishTsk_RlseCnt;
    uint8_t FinishTsk_HoldCnt;

    uint32_t SwitchNext_DelayCnt;
    uint16_t NextPos;
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
extern void UserCfg_Read_Setting();
extern void UserCfg_Write_Setting(uint8_t* ram_addr);

extern void KeyCfg_Read_Setting(uint8_t* dstp, uint16_t keyset_addr, uint16_t offset);
extern void KeyCfg_Write_Setting(uint8_t* ram_addr, uint16_t keyset_addr, uint16_t offset);
extern void KeyCfg_JumpNext(uint32_t StartPos, keycfg* P_KeyCfg);

#endif /* INCLUDE_USERCFG_H_ */
