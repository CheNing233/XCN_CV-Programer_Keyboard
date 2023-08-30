/**
 ******************************************************************************
 * @file    IIC.c
 * @brief   Library for IIC
 * @version 1.0.0
 * @date    2023-08-17
 * @author  xChenNing
 * @license MIT License
 ******************************************************************************
 */
#include <stdlib.h>
#include <string.h>
#include "IIC.h"

static void _Init(IIC_InitTypeDef* IIC_InitStructure, IIC_Handle_t* IIC_Handle);
static void _StartComunication(IIC_Handle_t IIC_Handle);
static void _SendByte(IIC_Handle_t IIC_Handle, uint8_t ByteBuf_Target);
static void _ReceiveByte(IIC_Handle_t IIC_Handle, uint8_t *ByteBufPtr_Target);
static void _StopComunication(IIC_Handle_t IIC_Handle);

static inline void _SCL_PullUp(IIC_Handle_t IIC_Handle);
static inline void _SCL_PullDown(IIC_Handle_t IIC_Handle);
static inline void _SDA_PullUp(IIC_Handle_t IIC_Handle);
static inline void _SDA_PullDown(IIC_Handle_t IIC_Handle);

struct _IIC_Class IIC = { .Init = _Init,
        .StartComunication = _StartComunication, .SendByte = _SendByte,
        .ReceiveByte = _ReceiveByte, .StopComunication = _StopComunication };

inline void _Init(IIC_InitTypeDef* IIC_InitStructure, IIC_Handle_t* IIC_Handle) {
    // create handle
    IIC_Handle_t ptr = (IIC_Handle_t) malloc(sizeof(IIC_InitTypeDef));

    // copy configuration
    memcpy(ptr, IIC_InitStructure, sizeof(IIC_InitTypeDef));

    // initialize bus
    _SCL_PullUp(ptr);
    _SDA_PullUp(ptr);

    // initialize handle
    *IIC_Handle = ptr;
}

inline void _StartComunication(IIC_Handle_t IIC_Handle) {
    _SDA_PullUp(IIC_Handle);
    _SCL_PullUp(IIC_Handle);

    _SDA_PullDown(IIC_Handle);
    _SCL_PullDown(IIC_Handle);
}

inline void _SendByte(IIC_Handle_t IIC_Handle, uint8_t ByteBuf_Target) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        if ((ByteBuf_Target & (0x80 >> i)) > 0) {
            _SDA_PullUp(IIC_Handle);
        } else {
            _SDA_PullDown(IIC_Handle);
        }

        _SCL_PullUp(IIC_Handle);
        _SCL_PullDown(IIC_Handle);
    }
    // ¶îÍâÊ±ÖÓ
    _SCL_PullUp(IIC_Handle);
    _SCL_PullDown(IIC_Handle);
}

inline void _ReceiveByte(IIC_Handle_t IIC_Handle, uint8_t *ByteBufPtr_Target) {
    ;
}

inline void _StopComunication(IIC_Handle_t IIC_Handle) {
    _SDA_PullDown(IIC_Handle);

    _SCL_PullUp(IIC_Handle);
    _SDA_PullUp(IIC_Handle);
}

static inline void _SCL_PullUp(IIC_Handle_t IIC_Handle) {
    IIC_Handle->SCL_PullUp();
}

static inline void _SCL_PullDown(IIC_Handle_t IIC_Handle) {
    IIC_Handle->SCL_PullDown();
}

static inline void _SDA_PullUp(IIC_Handle_t IIC_Handle) {
    IIC_Handle->SDA_PullUp();
}

static inline void _SDA_PullDown(IIC_Handle_t IIC_Handle) {
    IIC_Handle->SDA_PullDown();
}
