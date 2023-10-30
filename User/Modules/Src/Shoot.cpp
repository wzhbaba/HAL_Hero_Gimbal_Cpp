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
 * @brief Sets the first friction speed for the Shoot_t object.
 *
 * @param speed The desired speed for the first friction.
 */
void Shoot_t::SetFirstFricSpeed(float speed)
{
    Friction_Speed[0].ref = speed;
    Friction_Speed[1].ref = -speed;
}

/**
 * @brief Sets the second friction speed for shooting.
 *
 * This function sets the second friction speed for shooting by updating the reference values of the third and fourth elements in the Friction_Speed array.
 *
 * @param speed The desired speed for the second friction.
 */
void Shoot_t::SetSecondFricSpeed(float speed)
{
    Friction_Speed[2].ref = speed;
    Friction_Speed[3].ref = -speed;
}

/**
 * @brief Sets the friction speed for the first and second motors.
 *
 * @param first The friction speed for the first motor.
 * @param second The friction speed for the second motor.
 */
void Shoot_t::SetFricSpeed(float first, float second)
{
    SetFirstFricSpeed(first);
    SetSecondFricSpeed(second);
}

/**
 * @brief Sets the trigger position by adding the given value to the reference position.
 *
 * @param pos The value to add to the reference position.
 */
void Shoot_t::SetTriggerPos(float pos)
{
    Trigger_Position.ref += pos;
}

/**
 * @brief Sets the preset speed of the Shoot_t object.
 *
 * @param speed The speed to set the preset speed to.
 */
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
    for (short i = 0; i < 4; ++i) {
        Friction_Speed[i].fdb = Friction_Motor[i].speed_rpm;
        Friction_Speed[i].NormalCalc();
    }
}

/**
 * @brief Controls the trigger mechanism of the gimbal.
 *
 * This function calculates the position, speed, and current of the trigger motor
 * and sets the corresponding references and feedbacks for the PID controller.
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

/**
 * @brief This function sets the preset speed of the motor and calculates the normal speed.
 *
 */
void Shoot_t::PresetControl()
{
    Preset_Speed.fdb = Preset_Motor.speed_rpm;
    Preset_Speed.NormalCalc();
}

/**
 * @brief Controls the shooting mechanism by calling FrictionControl(), TriggerControl(), and PresetControl().
 */
void Shoot_t::Control()
{
    FrictionControl();
    TriggerControl();
    PresetControl();
}

/**
 * @brief Stops the shooting mechanism by setting all output speeds to 0.
 */
void Shoot_t::Stop()
{
    for (short i = 0; i < 4; ++i) {
        Friction_Speed[i].output = 0.0f;
    }
    Trigger_Speed.output = 0.0f;
    Preset_Speed.output = 0.0f;
}