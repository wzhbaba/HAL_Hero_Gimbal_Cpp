/**
 *******************************************************************************
 * @file      : Shoot.cpp
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
#include "Shoot.h"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
Shoot_t Shoot;
/* Private function prototypes -----------------------------------------------*/

/**
 * @brief
 * @param       speed:
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Shoot_t::SetFricSpeed(float speed)
{
    Friction_Speed[0].ref = -speed;
    Friction_Speed[1].ref = speed;
}

/**
 * @brief
 * @param       position:
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Shoot_t::SetTriggerPos(float pos)
{
    Trigger_Position.ref += pos;
}

void Shoot_t::SetPresetSpeed(float speed)
{
    Preset_Speed.ref = -speed;
}

/**
 * @brief
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Shoot_t::FrictionControl()
{
    for (short i = 0; i < 2; ++i) {
        Friction_Speed[i].fdb = Friction_Motor[i].speed_rpm;
        Friction_Speed[i].NormalCalc();
    }
}

/**
 * @brief
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Shoot_t::TriggerControl()
{
    Trigger_Position.fdb = Trigger_Motor.angle_real;
    Trigger_Position.NormalCalc();

    Trigger_Speed.ref = Trigger_Position.output;
    Trigger_Speed.fdb = Trigger_Motor.speed_rpm;
    Trigger_Speed.NormalCalc();

    Trigger_Current.ref = Trigger_Speed.output;
    Trigger_Current.fdb = Trigger_Motor.torque_current;
    Trigger_Current.NormalCalc();
}

void Shoot_t::PresetControl()
{
    Preset_Speed.fdb = Preset_Motor.speed_rpm;
    Preset_Speed.NormalCalc();
}

/**
 * @brief
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Shoot_t::Control()
{
    FrictionControl();
    TriggerControl();
    PresetControl();
}

/**
 * @brief
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Shoot_t::Stop()
{
    for (short i = 0; i < 2; ++i) {
        Friction_Speed[i].output = 0.0f;
    }
    Trigger_Current.output = 0.0f;
    Preset_Speed.output = 0.0f;
}