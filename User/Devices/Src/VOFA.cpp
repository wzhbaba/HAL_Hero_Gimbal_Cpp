/**
 *******************************************************************************
 * @file      : VOFA.cpp
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
#include "VOFA.h"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
VOFA_t VOFA;
/* Private function prototypes -----------------------------------------------*/

void VOFA_t::SendData2(float data1, float data2)
{
    Data2.data[0] = data1;
    Data2.data[1] = data2;

    // CDC_Transmit_FS((uint8_t *)&Data2, sizeof(Data2));
    UserUARTSendData(&huart3, (uint8_t *)&Data2, sizeof(Data2), UART_TRAMSMIT_DMA);
}

void VOFA_t::SendData4(float data1, float data2, float data3, float data4)
{
    Data4.data[0] = data1;
    Data4.data[1] = data2;
    Data4.data[2] = data3;
    Data4.data[3] = data4;
    Data4.tail[0] = 0x00;
    Data4.tail[1] = 0x00;
    Data4.tail[2] = 0x80;
    Data4.tail[3] = 0x7f;

    UserUARTSendData(&huart3, (uint8_t *)&Data4, sizeof(Data4), UART_TRANSMIT_IT);
}

void VOFA_t::SendData8(float data1, float data2, float data3, float data4, float data5, float data6, float data7, float data8)
{
    Data8.data[0] = data1;
    Data8.data[1] = data2;
    Data8.data[2] = data3;
    Data8.data[3] = data4;
    Data8.data[4] = data5;
    Data8.data[5] = data6;
    Data8.data[6] = data7;
    Data8.data[7] = data8;

    UserUARTSendData(&huart3, (uint8_t *)&Data8, sizeof(Data8), UART_TRAMSMIT_DMA);
}
