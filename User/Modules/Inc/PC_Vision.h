/**
 *******************************************************************************
 * @file      : PC_Vision.h
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
#ifndef __PC_VISION_H_
#define __PC_VISION_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include <drv_uart.h>
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#pragma pack(1)
// 必须有__packed，这样就可以使得结构体内存连续，方便赋值给数组，同时节约空间
typedef struct
{
    uint8_t header;
    uint8_t detect_color : 1;  // 0-red 1-blue
    bool reset_tracker : 1;
    uint8_t reserved : 6;
    float pitch;
    float yaw;
    float aim_x;
    float aim_y;
    float aim_z;
    uint16_t checksum;
} RobToVisPacket;

typedef struct
{
    uint8_t header;
    bool tracking : 1;
    uint8_t id : 3;          // 0-outpost 6-guard 7-base
    uint8_t armors_num : 3;  // 2-balance 3-outpost 4-normal
    uint8_t reserved : 1;
    float x;
    float y;
    float z;
    float yaw;
    float vx;
    float vy;
    float vz;
    float v_yaw;
    float r1;
    float r2;
    float dz;
    uint16_t checksum;
} VisToRobPacket;
#pragma pack()

class Vision_Def
{
   public:
    bool state;
    float pitch, yaw, aim_x, aim_y, aim_z;
    void DataPack(uint8_t *pData);
    void Send(float pitch, float yaw);

   private:
};

/* Exported variables --------------------------------------------------------*/
extern Vision_Def Vision;
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
