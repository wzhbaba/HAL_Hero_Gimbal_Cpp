/**
 *******************************************************************************
 * @file      : VOFA.h
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
#ifndef __VOFA_H_
#define __VOFA_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include "drv_uart.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
    float data[2];
    uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7f};
} Data2_t;

typedef struct {
    float data[4];
    uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7f};
} Data4_t;

typedef struct {
    float data[8];
    uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7f};
} Data8_t;

class VOFA_t
{
   public:
    Data2_t Data2;
    Data4_t Data4;
    Data8_t Data8;
    void SendData2(float data1, float data2);
    void SendData4(float data1, float data2, float data3, float data4);
    void SendData8(float data1, float data2, float data3, float data4, float data5, float data6, float data7, float data8);
};
/* Exported variables --------------------------------------------------------*/
extern VOFA_t VOFA;
/* Exported function prototypes ----------------------------------------------*/

#endif

#endif /* __FILE_H_ */
