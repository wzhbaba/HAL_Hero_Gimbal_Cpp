/**
 *******************************************************************************
 * @file      : Gimbal.h
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
#ifndef __GIMBAL_H_
#define __GIMBAL_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include "Dji_Motor.h"
#include "IMU.h"
#include "PID.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class Gimbal_t
{
   public:
    PID_Def Position[2];
    PID_Def Speed[2];
    PID_Def Current[2];

    void Stop();
    void Control();
    void AngleCalc();
    void SpeedCalc();
    void SetVisionPitchPos(float set);
    void SetVisionYawPos(float set);
    void SetPitchPosition(float set);
    void SetYawPosition(float set);
};
/* Exported variables --------------------------------------------------------*/
extern Gimbal_t Gimbal;

/* Exported function prototypes ----------------------------------------------*/

#endif

#endif /* __FILE_H_ */
