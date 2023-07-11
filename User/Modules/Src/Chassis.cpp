/**
 *******************************************************************************
 * @file      : Chassis.cpp
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
#include "Chassis.h"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
Chassis_t Chassis;

/* Private function prototypes -----------------------------------------------*/

void Chassis_t::FollowCtrl()
{
    Pack.x_speed = -arm_sin_f32(Gimbal_Motor[1].angle_real / 180 * PI) * Pack.y_target + arm_cos_f32(Gimbal_Motor[1].angle_real / 180 * PI) * Pack.x_target;
    Pack.y_speed = arm_cos_f32(Gimbal_Motor[1].angle_real / 180 * PI) * Pack.y_target + arm_sin_f32(Gimbal_Motor[1].angle_real / 180 * PI) * Pack.x_target;

    if (rotate_flag == 1) {
        Pack.r_speed = Pack.r_target;
    } else {
        Follow.ref = Yaw_Encoder;
        Follow.fdb = Target_Encoder;
        Follow.NormalCalc();
        Pack.r_speed = Follow.output;
    }
}

void Chassis_t::Stop()
{
    Pack.x_speed = 0;
    Pack.y_speed = 0;
    Pack.r_speed = 0;
}

void Chassis_t::FlagCommu()
{
    ui_flag = rotate_flag << 6 | cap_flag << 5 | fric_flag << 4 | aim_flag << 3 | covers_flag << 2 | shoot_flag << 1;
}