/*
 * input.h
 *
 *  Created on: 2023Äê8ÔÂ28ÈÕ
 *      Author: 19156
 */

#ifndef INCLUDE_INPUT_H_
#define INCLUDE_INPUT_H_

#include <CH57x_common.h>

// KEYBOARD
#define KEY_LEFT_CTRL GPIO_Pin_8 // A8
#define KEY_RIGHT_ENTER GPIO_Pin_12 // B12
#define KEY_X GPIO_Pin_15 // B15
#define KEY_C GPIO_Pin_14 // B14
#define KEY_V GPIO_Pin_13 // B13

// ROLLER
#define ROLLER_BUTTON GPIO_Pin_15 // A15
#define ROLLER_A GPIO_Pin_13 // A13
#define ROLLER_B GPIO_Pin_14 // A14

// KEY MAP
#define MAP_VOL_UP 0x01
#define MAP_VOL_DOWN 0x02
#define MAP_ROLLER_BUTTON 0x04
#define MAP_LEFT_CTRL 0x08
#define MAP_RIGHT_ENTER 0x10
#define MAP_KEY_X 0x20
#define MAP_KEY_C 0x40
#define MAP_KEY_V 0x80

extern void Input_Init();

#endif /* INCLUDE_INPUT_H_ */
