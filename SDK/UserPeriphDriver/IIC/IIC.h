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
 * @brief IIC�豸 ��ʼ���ṹ��
 */
typedef struct {
    /*
     * @brief ʱ���� ����
     */
    void (*SCL_PullUp)();
    /*
     * @brief ʱ���� ����
     */
    void (*SCL_PullDown)();
    /*
     * @brief ������ ����
     */
    void (*SDA_PullUp)();
    /*
     * @brief ������ ����
     */
    void (*SDA_PullDown)();
} IIC_InitTypeDef;

/*
 * IIC�豸 ���
 */
typedef IIC_InitTypeDef *IIC_Handle_t;

/*
 * IIC�豸 ��
 */
struct _IIC_Class {
    void (*Init)(IIC_InitTypeDef* IIC_InitStructure, IIC_Handle_t* IIC_Handle);
    void (*StartComunication)(IIC_Handle_t IIC_Handle);
    void (*SendByte)(IIC_Handle_t IIC_Handle, uint8_t ByteBuf_Target);
    void (*ReceiveByte)(IIC_Handle_t IIC_Handle, uint8_t *ByteBufPtr_Target);
    void (*StopComunication)(IIC_Handle_t IIC_Handle);
};

/*
 * IIC�豸 ��������
 */
extern struct _IIC_Class IIC;

#ifdef __cplusplus
}
#endif

#endif /* __USERDRIVER_IIC_IIC_H__ */
