/**
 *******************************************************************************
 * @file      : Remote_Keyboard.cpp
 * @brief     :
 * @history   :
 *  Version     Date            Author          Note
 *  V0.9.0      yyyy-mm-dd      <author>        1. <note>
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2023 Reborn Team, USTB.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "Remote_Keyboard.h"

#include "DR16.h"
#include "Hero_Gimbal.h"
#include "Referee.h"
#include "tim.h"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
void RemoteChassisCtrl();
void RemoteGimbalCtrl();
void RemoteShootCtrl();
void KeyboardChassisCtrl();
void KeyboardGimbalCtrl();
void KeyboardShootCtrl();
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void ModeTask()
{
    if (Remote.Pack.s2 == 1) {
        RemoteChassisCtrl();
        RemoteGimbalCtrl();
        RemoteShootCtrl();
    } else if (Remote.Pack.s2 == 3) {
        KeyboardChassisCtrl();
        KeyboardGimbalCtrl();
        KeyboardShootCtrl();
    } else if (Remote.Pack.s2 == 2) {
        Hero_Gimbal.Stop();
    }
}

void RemoteChassisCtrl()
{
    Chassis.Pack.x_target = Remote.Pack.ch2 * 1.5f;
    Chassis.Pack.y_target = Remote.Pack.ch3 * 1.5f;
}

void RemoteGimbalCtrl()
{
    if (Remote.Pack.s1 == 1) {
        Gimbal.SetVisionPitchPos(Vision.pitch * 180.0f / 3.1415926f);
        Gimbal.SetVisionYawPos(Vision.yaw * 180.0f / 3.1415926f);
    } else {
        Gimbal.SetPitchPosition((Remote.Pack.ch1 / 660.0f) * 0.25f);
        Gimbal.SetYawPosition((Remote.Pack.ch0 / 660.0f) * 0.25f);
    }
}

/**
 * @brief
 *   @arg       None
 * @retval      None
 * @note        None
 */
void RemoteShootCtrl()
{
    static uint8_t flag = 0;
    Shoot.SetFricSpeed(4500.0f);

    if (Remote.Pack.s1 == 3) {
        flag = 1;
    }

    if (Remote.Pack.s1 == 2 && flag == 1) {
        Shoot.SetTriggerPos(60 * 19.2f);
        Shoot.SetPresetSpeed(500 * 36.0f);
        flag = 0;
    }

    if (Shoot.Trigger_Position.ref - Shoot.Trigger_Position.fdb < 700) {
        Shoot.SetPresetSpeed(0.0f);
    }
}

void KeyboardChassisCtrl()
{
    if (Referee.KeyState[REFEREE_KEY_W].isPressed == 1) {
        Chassis.Pack.y_target = 660;
    } else if (Referee.KeyState[REFEREE_KEY_S].isPressed == 1) {
        Chassis.Pack.y_target = -660;
    } else {
        Chassis.Pack.y_target = 0;
    }

    if (Referee.KeyState[REFEREE_KEY_A].isPressed == 1) {
        Chassis.Pack.x_target = -660;
    } else if (Referee.KeyState[REFEREE_KEY_D].isPressed == 1) {
        Chassis.Pack.x_target = 660;
    } else {
        Chassis.Pack.x_target = 0;
    }

    if (Referee.KeyState[REFEREE_KEY_SHIFT].isPressed == 1) {
        Chassis.Pack.r_target = 660;
        Chassis.rotate_flag = 1;
    } else {
        Chassis.Pack.r_target = 0;
        Chassis.rotate_flag = 0;
    }

    if (Referee.KeyState[REFEREE_KEY_C].isTicked == 0) {
        Chassis.cap_flag = 0;
    } else {
        Chassis.cap_flag = 1;
    }
}

void KeyboardGimbalCtrl()
{
    if (Referee.KeyState[REFEREE_KEY_Q].isTicked == 1) {
        Gimbal.SetYawPosition(-180.0f);
        Referee.KeyState[REFEREE_KEY_Q].isTicked = 0;
    }

    if (Referee.KeyState[REFEREE_KEY_Z].isTicked == 1) {
        Gimbal.SetMirrorPos(270 * 36.0f);
    } else {
        Gimbal.SetMirrorPos(0.0f);
    }

    if (Referee.KeyState[REFEREE_KEY_X].isTicked == 1) {
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 520);
    } else {
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 420);
    }
    Gimbal.SetPitchPosition(-Referee.CommaData.mouse_y * 0.001f);
    Gimbal.SetYawPosition(Referee.CommaData.mouse_x * 0.001f);
}

void KeyboardShootCtrl()
{
    static uint8_t flag = 0;
    static uint16_t time_out = 0;
    static uint8_t shoot_allow_flag = 0;
    static uint8_t count_flag = 1;

    if (Referee.GameRobotStat.mains_power_shooter_output == 1) {
        if (count_flag) {
            time_out++;
            if (Referee.GameRobotStat.shooter_id1_42mm_cooling_limit == 100) {
                if (time_out >= 800) {
                    time_out = 0;
                    count_flag = 0;
                    shoot_allow_flag = 1;
                }
            } else {
                if (time_out >= 150) {
                    time_out = 0;
                    count_flag = 0;
                    shoot_allow_flag = 1;
                }
            }
        }

        if (Referee.KeyState[REFEREE_KEY_F].isTicked == 1) {
            Chassis.fric_flag = 1;
            if (Referee.GameRobotStat.shooter_id1_42mm_speed_limit == 10) {
                Shoot.SetFricSpeed(3300.0f);
            } else if (Referee.GameRobotStat.shooter_id1_42mm_speed_limit == 16) {
                if (Referee.KeyState[REFEREE_KEY_E].isTicked == 1 && IMU.Euler[0] <= -10.0f) {
                    Chassis.shoot_flag = 1;
                    Shoot.SetFricSpeed(5000.0f);
                } else {
                    Chassis.shoot_flag = 0;
                    Shoot.SetFricSpeed(4750.0f);  // 4900 白弹 4750 荧光
                }
            } else {
                Shoot.SetFricSpeed(4650.0f);  // 4750 norm 4850 high
            }

            if (Referee.KeyState[REFEREE_MOUSE_L].isPressed == 0) {
                flag = 1;
            }

            if (shoot_allow_flag == 1 && Referee.KeyState[REFEREE_MOUSE_L].isPressed == 1 && flag == 1 && (Referee.GameRobotStat.shooter_id1_42mm_cooling_limit - Referee.PowerHeatData.shooter_id1_42mm_cooling_heat) >= 100) {
                Shoot.SetTriggerPos(60 * 19.2f);
                Shoot.SetPresetSpeed(500 * 36.0f);
                flag = 0;
                shoot_allow_flag = 0;
                count_flag = 1;
            }

            if (Shoot.Trigger_Position.ref - Shoot.Trigger_Position.fdb < 45 * 19.2f) {
                Shoot.SetPresetSpeed(0.0f);
            }

            if (Referee.KeyState[REFEREE_KEY_V].isTicked == 1) {
                Shoot.SetTriggerPos(-60 * 19.2f);
                Referee.KeyState[REFEREE_KEY_V].isTicked = 0;
            }

        } else {
            Chassis.fric_flag = 0;
            Shoot.SetFricSpeed(0.0f);
        }

    } else {
        Chassis.fric_flag = 0;
        Shoot.SetFricSpeed(0.0f);
    }
}