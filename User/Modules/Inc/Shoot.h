/**
 *******************************************************************************
 * @file      : Shoot.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SHOOT_H_
#define __SHOOT_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include "Dji_Motor.h"
#include "PID.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
    ANGLE_FLAG = 0,
    SPEED_FLAG = 1,

} Shoot_Flag;
class Shoot_t
{
   public:
    PID_Def Friction_Speed[2];
    PID_Def Friction_Current[2];
    PID_Def Trigger_Position;
    PID_Def Trigger_Speed;
    PID_Def Trigger_Current;
    PID_Def Preset_Speed;
    PID_Def Preset_Current;
    uint16_t Shoot_Flag;
    void FrictionControl();
    void SetFricSpeed(float speed);
    void SetTriggerPos(float pos);
    void SetTriggerSpeed(float speed);
    void SetPresetSpeed(float speed);
    void TriggerControl();
    void PresetControl();
    void Control();
    void Stop();

   private:
};

/* Exported variables --------------------------------------------------------*/
extern Shoot_t Shoot;
/* Exported function prototypes ----------------------------------------------*/

#endif

#endif /* __FILE_H_ */
