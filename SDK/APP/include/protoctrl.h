/*
 * protoctrl.h
 *
 *  Created on: 2023Äê8ÔÂ29ÈÕ
 *      Author: 19156
 */

#ifndef INCLUDE_PROTOCTRL_H_
#define INCLUDE_PROTOCTRL_H_

#include <CH57x_common.h>

#define PROTO_SW_PIN GPIO_Pin_9

typedef enum _Board_ProtoSWState {
    Board_USBState, Board_BLEState
} Board_ProtoSWState;

extern Board_ProtoSWState Global_ProtoState;

typedef enum _Borad_ProtoConnState {
    Board_Conn_Wait, Board_Conn_OK, Board_Conn_Stop, Board_Conn_ERR
} Borad_ProtoConnState;

extern Borad_ProtoConnState Global_ProtoUSBConn;
extern Borad_ProtoConnState Global_ProtoBLEConn;

extern uint8_t ReportBuf_Keyboard[8];
extern uint8_t ReportBuf_Consumer[2];

extern void ProtoCtrl_Init();

void ProtoCtrl_SendKBReport();
void ProtoCtrl_SendCSReport();

#endif /* INCLUDE_PROTOCTRL_H_ */
