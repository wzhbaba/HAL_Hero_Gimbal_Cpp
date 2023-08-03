/**
 *******************************************************************************
 * @file      : Gimbal.cpp
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
#include "Gimbal.h"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
Gimbal_t Gimbal;
/* Private function prototypes -----------------------------------------------*/

void Gimbal_t::SetPitchPosition(float set)
{
    Position[0].ref -= set;
    VAL_LIMIT(Position[0].ref, -42.0f, 20.0f);
}

void Gimbal_t::SetYawPosition(float set)
{
    Position[1].ref -= set;
}

void Gimbal_t::SetMirrorPos(float set)
{
    Position[2].ref = set;
}

void Gimbal_t::SetVisionPitchPos(float set)
{
    Position[0].ref = set;
}

void Gimbal_t::SetVisionYawPos(float set)
{
    static float temp;
    temp = set - IMU.Yaw;
    if (temp < -180.0f) {
        temp += 360.0f;
    } else if (temp > 180.0f) {
        temp -= 360.0f;
    }
    Position[1].ref = temp + IMU.Euler[2];
}

void Gimbal_t::AngleCalc()
{
    Position[0].fdb = IMU.Euler[0];
    Position[1].fdb = IMU.Euler[2];
    Position[2].fdb = Mirror_Motor.angle_real + 270 * 36.0f;

    for (short i = 0; i < 3; ++i) {
        Position[i].NormalCalc();
    }
}

void Gimbal_t::SpeedCalc()
{
    Speed[0].ref = Position[0].output;
    Speed[0].fdb = IMU.Gyro[1] * 60.0f / 360.0f;
    Speed[1].ref = Position[1].output;
    Speed[1].fdb = IMU.Gyro[2] * 60.0f / 360.0f;
    Speed[2].ref = Position[2].output;
    Speed[2].fdb = Mirror_Motor.speed_rpm;

    for (short i = 0; i < 3; ++i) {
        Speed[i].NormalCalc();
    }
}

void Gimbal_t::Stop()
{
    for (short i = 0; i < 3; ++i) {
        Speed[i].output = 0.0f;
    }
}

void Gimbal_t::Control()
{
    AngleCalc();
    SpeedCalc();
}