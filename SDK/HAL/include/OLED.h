/*
 * OLED.h
 *
 *  Created on: 2023Äê8ÔÂ17ÈÕ
 *      Author: 19156
 */

#ifndef MODULE_OLED_OLED_H_
#define MODULE_OLED_OLED_H_

#include "../../UserPeriphDriver/SSD13xx/SSD13xx.h"
#include "../../UserPeriphDriver/IIC/IIC.h"

void OLED_Init(uint32_t IIC_GND, uint32_t IIC_VCC, uint32_t IIC_SDA,
        uint32_t IIC_SCL);

extern SSD13xx_handle_t OLED_Handle;

#endif /* MODULE_OLED_OLED_H_ */
