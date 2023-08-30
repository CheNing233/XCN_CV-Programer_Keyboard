/*
 * output.h
 *
 *  Created on: 2023Äê8ÔÂ28ÈÕ
 *      Author: 19156
 */

#ifndef INCLUDE_OUTPUT_H_
#define INCLUDE_OUTPUT_H_

#include <CH57x_common.h>

// OLED
#define OLED_IIC_SDA GPIO_Pin_5
#define OLED_IIC_SCL GPIO_Pin_4
#define OLED_IIC_VCC 0
#define OLED_IIC_GND 0

extern void Output_Init();

extern uint8_t Output_Clear4Ln_WaitCnt;

#endif /* INCLUDE_OUTPUT_H_ */
