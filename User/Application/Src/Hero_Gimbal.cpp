/**
 *******************************************************************************
 * @file      : Infantry_Gimbal.cpp
 * @brief     :
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0      2023-05-09      Jerry Gong      第一版
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2023 Reborn Team, USTB.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "Hero_Gimbal.h"

#include "Chassis.h"
#include "VOFA.h"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
Hero_Gimbal_t Hero_Gimbal;
/* Private function prototypes -----------------------------------------------*/

/**
 * @brief
 *   @arg       None
 * @retval      None
 * @note        None
 */
void GimbalInit()
{
    Gimbal.Position[0].Set(40.0f, 0.0f, 0.0f, 10000.0f, 2500.0f, 2500.0f, 15000.0f);
    Gimbal.Position[1].Set(40.0f, 0.0f, 0.0f, 10000.0f, 2500.0f, 2500.0f, 15000.0f);
    Gimbal.Speed[0].Set(80.0f, 0.0f, 0.0f, 25000.0f, 5000.0f, 0.0f, 30000.0f);
    Gimbal.Speed[1].Set(150.0f, 0.0f, 0.0f, 25000.0f, 2500.0f, 2500.0f, 30000.0f);

    Shoot.Friction_Speed[0].Set(10.0f, 0.0f, 0.0f, 10000.0f, 2500.0f, 2500.0f, 20000.0f);
    Shoot.Friction_Speed[1].Set(10.0f, 0.0f, 0.0f, 10000.0f, 2500.0f, 2500.0f, 20000.0f);

    Shoot.Trigger_Position.Set(5.0f, 0.0f, 0.0f, 5000.0f, 2500.0f, 0.0f, 15000.0f);
    Shoot.Trigger_Speed.Set(10.0f, 0.0f, 0.0f, 10000.0f, 5000.0f, 0.0f, 30000.0f);
    Shoot.Trigger_Current.Set(2.0f, 0.0f, 0.0f, 10000.0f, 0.0f, 0.0f, 30000.0f);

    Shoot.Preset_Speed.Set(10.0f, 0.0f, 0.0f, 10000.0f, 0.0f, 0.0f, 10000.0f);
    Shoot.Preset_Current.Set(1.0f, 0.0f, 0.0f, 10000.0f, 0.0f, 0.0f, 10000.0f);

    Chassis.Follow.Set(1.0f, 0.0f, 0.0f, 660.0f, 0.0f, 0.0f, 660.0f);
}

/**
 * @brief
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Hero_Gimbal_t::Control()
{
    Gimbal.Control();
    Shoot.Control();
    Chassis.FollowCtrl();
}

/**
 * @brief
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Hero_Gimbal_t::Stop()
{
    Gimbal.Stop();
    Shoot.Stop();
    Chassis.Stop();
}

/**
 * @brief
 *   @arg       None
 * @retval      None
 * @note        None
 */
void HeroGimbalTask()
{
    if (Remote.Pack.s2 == 1 || Remote.Pack.s2 == 3) {
        Hero_Gimbal.Control();
    } else {
        Hero_Gimbal.Stop();
    }
    Chassis.FlagCommu();
    CANx_PackProcess_Data(&hcan1, 0x1FF, 0x08, (int16_t)Gimbal.Speed[1].output, (int16_t)Shoot.Trigger_Current.output, 0, 0);
    CANx_PackProcess_Data(&hcan2, 0x200, 0x08, (int16_t)Shoot.Friction_Speed[0].output, (int16_t)Shoot.Friction_Speed[1].output, (int16_t)Shoot.Preset_Speed.output, (int16_t)Gimbal.Speed[0].output);
    CANx_PackProcess_Data(&hcan1, 0x112, 0x08, (int16_t)Chassis.Pack.x_speed, (int16_t)Chassis.Pack.y_speed, (int16_t)Chassis.Pack.r_speed, Chassis.ui_flag);
    CANx_PackProcess_Data(&hcan1, 0x114, 0x08, IMU.Euler[0] * 100, 0, 0, 0);

    VOFA.SendData4(Gimbal.Position[0].output, Gimbal.Position[1].output, Gimbal.Speed[0].output, Gimbal.Speed[1].output);
}
