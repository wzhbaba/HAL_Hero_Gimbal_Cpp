/**
 *******************************************************************************
 * @file      : Chassis.h
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
#ifndef __CHASSIS_H_
#define __CHASSIS_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include "CommomInc.h"
#include "arm_math.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct Chassis_s {
    int16_t x_speed;
    int16_t y_speed;
    int16_t r_speed;
    int16_t x_target;
    int16_t y_target;
    int16_t r_target;
};

class Chassis_t
{
   public:
    Chassis_s Pack;
    PID_Def Follow;
    int16_t Yaw_Encoder;
    int16_t Target_Encoder = 7340;
    uint8_t rotate_flag;
    uint8_t cap_flag;
    uint8_t fric_flag;
    uint8_t aim_flag;
    uint8_t covers_flag;
    uint8_t shoot_flag;
    uint8_t ui_flag;

    void FollowCtrl();
    void Stop();
    void FlagCommu();
};

/* Exported variables --------------------------------------------------------*/
extern Chassis_t Chassis;
/* Exported function prototypes ----------------------------------------------*/

#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __FILE_H_ */
