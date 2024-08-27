#ifndef __PROTOCOL__
#define __PROTOCOL__

typedef enum _Board_Protocol_Use {
    Board_Use_USB, Board_Use_BLE
} Board_Protocol_Use;

extern Board_Protocol_Use Protocol_SW;

extern uint8_t ReportBuf_Keyboard[8];
extern uint8_t ReportBuf_Consumer[4];

extern void ProtoCtrl_Init();
extern void ProtoCtrl_Act_USB();
extern void ProtoCtrl_Act_BLE();

#endif
