
/*
 * keyin.h
 *
 *  Created on: 2023Äê9ÔÂ24ÈÕ
 *      Author: 19156
 */

#ifndef INCLUDE_KEYIN_H_
#define INCLUDE_KEYIN_H_

// KEYBOARD
//#define KEY_LEFT_CTRL GPIO_Pin_8 // A8
//#define KEY_RIGHT_ENTER GPIO_Pin_12 // B12
//#define KEY_X GPIO_Pin_15 // B15
//#define KEY_C GPIO_Pin_14 // B14
//#define KEY_V GPIO_Pin_13 // B13

#define KEY_LEFT_CTRL GPIO_Pin_15 // B15
#define KEY_RIGHT_ENTER GPIO_Pin_9 // A9
#define KEY_X GPIO_Pin_14 // B14
#define KEY_C GPIO_Pin_13 // B13
#define KEY_V GPIO_Pin_12 // B12

// ROLLER
#define ROLLER_BUTTON GPIO_Pin_22 // B15
#define ROLLER_A GPIO_Pin_14 // A13
#define ROLLER_B GPIO_Pin_13 // A14

// KEY MAP
enum _keymap {
    MAP_CTRL, MAP_ENTER, MAP_X, MAP_C, MAP_V, MAP_RBT, MAP_RL, MAP_RR
};

extern uint8_t Keymap ;
extern uint8_t Keymap_o ;

extern uint8_t enco_finish_flg;
extern uint8_t finish_upload;
extern uint8_t enco_left;
extern uint8_t enco_right;

extern uint8_t TMOS_Keys_TaskManager_ID ;

extern void Keyin_Init();
extern void Keyin_Reset_All();


#endif /* INCLUDE_KEYIN_H_ */
