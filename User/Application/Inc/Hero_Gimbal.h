/**
 *******************************************************************************
 * @file      : Infantry_Gimbal.h
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
#ifndef __HERO_GIMBAL_H_
#define __HERO_GIMBAL_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include "Chassis.h"
#include "DR16.h"
#include "Gimbal.h"
#include "Referee.h"
#include "Shoot.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class Hero_Gimbal_t
{
   public:
    void Stop();
    void Control();

   private:
};
/* Exported variables --------------------------------------------------------*/
extern Hero_Gimbal_t Hero_Gimbal;
/* Exported function prototypes ----------------------------------------------*/

#endif

#ifdef __cplusplus
extern "C" {
#endif  // DEBUG

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void GimbalInit();
void HeroGimbalTask();

#ifdef __cplusplus
}
#endif  // DEBUG

#endif /* __FILE_H_ */
