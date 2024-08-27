#include "config.h"
#include "usercfg.h"
#include "protocol.h"
#include "hiddev.h"
#include "app_ble.h"
#include "keyin.h"

//      USB/BLE SW
Board_Protocol_Use Protocol_SW = Board_Use_USB;

uint8_t ReportBuf_Keyboard[8] = {
//      Keyboard buffer
    0x00,// 功能键
    0x00, // 保留
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 普通键
    };

uint8_t ReportBuf_Consumer[4] = {
//      Consumer buffer
    0x00, 0x00, 0x00, 0x00 };

static uint8_t TMOSTASK_ProtoCtrl_Fresh_ID = INVALID_TASK_ID;
static uint16_t TMOSTASK_ProtoCtrl_Fresh(uint8_t task_id, uint16_t events);

static uint8_t TMOSTASK_ProtoCtrl_UploadData_ID = INVALID_TASK_ID;
static uint16_t TMOSTASK_ProtoCtrl_UploadData(uint8_t task_id, uint16_t events);

void ProtoCtrl_Init() {

    TMOSTASK_ProtoCtrl_Fresh_ID = TMOS_ProcessEventRegister(TMOSTASK_ProtoCtrl_Fresh);

    TMOSTASK_ProtoCtrl_UploadData_ID = TMOS_ProcessEventRegister(TMOSTASK_ProtoCtrl_UploadData);

    ProtoCtrl_Act_USB();

    tmos_start_task(TMOSTASK_ProtoCtrl_Fresh_ID, 0x0001, UserCfg_RAM.Proto_FreshState_Interval);

    tmos_start_task(TMOSTASK_ProtoCtrl_UploadData_ID, 0x0001, UserCfg_RAM.Proto_USBBuffer_PushInterval);

}


void ProtoCtrl_Act_USB(){
    Protocol_SW = Board_Use_USB;
    HidDev_Close();
}

void ProtoCtrl_Act_BLE(){
    Protocol_SW = Board_Use_BLE;
    HidDev_Start();
}

uint16_t TMOSTASK_ProtoCtrl_Fresh(uint8_t task_id, uint16_t events) {

    static Board_Protocol_Use old_protocolsw = Board_Use_USB;

    /*
     * 弃用
     */

    if (events & SYS_EVENT_MSG) {
        return (events ^ SYS_EVENT_MSG);
    }

    if (events & 0x00ff) {

        if (old_protocolsw != Protocol_SW) {
            switch (Protocol_SW) {
            case Board_Use_USB:


                break;

            case Board_Use_BLE:


                break;
            }
        }

        old_protocolsw = Protocol_SW;

        tmos_start_task(TMOSTASK_ProtoCtrl_Fresh_ID, 0x0001, UserCfg_RAM.Proto_FreshState_Interval);
    }

    return 0;
}

uint16_t TMOSTASK_ProtoCtrl_UploadData(uint8_t task_id, uint16_t events) {

//    static uint8_t roller_onhold = FALSE;

    if (events & SYS_EVENT_MSG) {
        return (events ^ SYS_EVENT_MSG);
    }

    if (events & 0x0001) {

        switch (Protocol_SW) {
        case Board_Use_USB:

            memcpy(pEP1_IN_DataBuf, ReportBuf_Keyboard, sizeof(ReportBuf_Keyboard));
            memcpy(pEP2_IN_DataBuf, ReportBuf_Consumer, sizeof(ReportBuf_Consumer));
            DevEP1_IN_Deal(sizeof(ReportBuf_Keyboard));
            DevEP2_IN_Deal(sizeof(ReportBuf_Consumer));

            tmos_start_task(TMOSTASK_ProtoCtrl_UploadData_ID, 0x0001, UserCfg_RAM.Proto_USBBuffer_PushInterval);
            break;

        case Board_Use_BLE:

            hidEmuSendReport();

            tmos_start_task(TMOSTASK_ProtoCtrl_UploadData_ID, 0x0001, UserCfg_RAM.Proto_BLEBuffer_PushInterval);
            break;

        default:
            tmos_start_task(TMOSTASK_ProtoCtrl_UploadData_ID, 0x0001, UserCfg_RAM.Proto_USBBuffer_PushInterval);
            break;
        }

        finish_upload = TRUE;
//        enco_finish_flg = TRUE;
//        if (enco_left > 0)
//            enco_left--;
//        if (enco_right > 0)
//            enco_right--;
    }

    return 0;
}
