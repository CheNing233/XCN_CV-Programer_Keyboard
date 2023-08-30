/**
 ******************************************************************************
 * @file    IIC.h
 * @brief   Library for IIC
 * @version 1.0.0
 * @date    2023-08-17
 * @author  xChenNing
 * @license MIT License
 ******************************************************************************
 */

#ifndef __USERDRIVER_IIC_IIC_H__
#define __USERDRIVER_IIC_IIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
 * @brief IIC设备 初始化结构体
 */
typedef struct {
    /*
     * @brief 时钟线 上拉
     */
    void (*SCL_PullUp)();
    /*
     * @brief 时钟线 下拉
     */
    void (*SCL_PullDown)();
    /*
     * @brief 数据线 上拉
     */
    void (*SDA_PullUp)();
    /*
     * @brief 数据线 下拉
     */
    void (*SDA_PullDown)();
} IIC_InitTypeDef;

/*
 * IIC设备 句柄
 */
typedef IIC_InitTypeDef *IIC_Handle_t;

/*
 * IIC设备 类
 */
struct _IIC_Class {
    void (*Init)(IIC_InitTypeDef* IIC_InitStructure, IIC_Handle_t* IIC_Handle);
    void (*StartComunication)(IIC_Handle_t IIC_Handle);
    void (*SendByte)(IIC_Handle_t IIC_Handle, uint8_t ByteBuf_Target);
    void (*ReceiveByte)(IIC_Handle_t IIC_Handle, uint8_t *ByteBufPtr_Target);
    void (*StopComunication)(IIC_Handle_t IIC_Handle);
};

/*
 * IIC设备 对象声明
 */
extern struct _IIC_Class IIC;

#ifdef __cplusplus
}
#endif

#endif /* __USERDRIVER_IIC_IIC_H__ */
