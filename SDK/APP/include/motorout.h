/*
 * motorout.h
 *
 *  Created on: 2023Äê11ÔÂ11ÈÕ
 *      Author: 19156
 */

#ifndef APP_INCLUDE_MOTOROUT_H_
#define APP_INCLUDE_MOTOROUT_H_

#define MOTOR_PIN GPIO_Pin_10 // A10

#define MOTOR_PIN_INIT GPIOA_ModeCfg(MOTOR_PIN, GPIO_ModeOut_PP_5mA)
#define MOTOR_PIN_PU GPIOA_SetBits(GPIO_Pin_10)
#define MOTOR_PIN_PD GPIOA_ResetBits(GPIO_Pin_10)

extern uint8_t MotorOut_MainSW;

extern uint16_t MotorOut_unblock_cnt;

extern void MotorOut_Init();
extern void Motor_Block_LightShock();

#endif /* APP_INCLUDE_MOTOROUT_H_ */
