/**
 *******************************************************************************
 * @file      : DR16.h
 * @brief     :
 * @history   :
 *  Version     Date            Author          Note
 *  V0.9.0      2023-05-03    Jerry Gong        1. <note>
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2023 Reborn Team, USTB.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DR16_H_
#define __DR16_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include <drv_uart.h>

/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
enum {
    DR16_KEY_W = 0,
    DR16_KEY_S,
    DR16_KEY_A,
    DR16_KEY_D,
    DR16_KEY_SHIFT,
    DR16_KEY_CTRL,
    DR16_KEY_Q,
    DR16_KEY_E,
    DR16_KEY_R,
    DR16_KEY_F,
    DR16_KEY_G,
    DR16_KEY_Z,
    DR16_KEY_X,
    DR16_KEY_C,
    DR16_KEY_V,
    DR16_KEY_B,
    DR16_MOUSE_L,
    DR16_MOUSE_R,
};

struct DR16_DatePack_t {
    int16_t ch0;
    int16_t ch1;
    int16_t ch2;
    int16_t ch3;
    uint8_t s1;
    uint8_t s2;
    int16_t mouse_x;
    int16_t mouse_y;
    int16_t mouse_z;
    uint8_t press_l;
    uint8_t press_r;
    uint16_t key;
};
struct DR16_Keyboard {
    uint8_t isPressed;
    uint8_t isTicked;
    uint8_t LastState;
};
class DBUS_Def
{
   public:
    DR16_DatePack_t Pack;
    DR16_Keyboard KeyState[18];
    void SbusToRc(uint8_t *pData);
    void KeyProcess();

   private:
};

/* Exported variables --------------------------------------------------------*/
extern DBUS_Def Remote;
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
