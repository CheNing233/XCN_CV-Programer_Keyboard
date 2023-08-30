/*
 * ENCODER.h
 *
 *  Created on: 2023Äê8ÔÂ28ÈÕ
 *      Author: 19156
 */

#ifndef INCLUDE_ENCODER_H_
#define INCLUDE_ENCODER_H_

#include <CH57x_common.h>

typedef struct {
    uint32_t Encoder_A;
    uint32_t Encoder_B;
    void (*SpinEventCB)(int8_t DeltaValue);
    uint8_t TriggerInterval;
} Encoder_InitTypeDef;

typedef Encoder_InitTypeDef *Encoder_Handle;

extern void Encoder_Init(Encoder_InitTypeDef *Encoder_InitStructure);

extern void Encoder_Spin();

extern int8_t _delta_value;

#endif /* INCLUDE_ENCODER_H_ */
