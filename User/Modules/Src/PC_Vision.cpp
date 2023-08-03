/**
 *******************************************************************************
 * @file      : PC_Vision.cpp
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
#include <PC_Vision.h>

#include "CRC.h"
#include "SolveTrajectory.h"
#include "usbd_cdc_if.h"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
Vision_Def Vision;
/* Private function prototypes -----------------------------------------------*/

/**
 * @brief
 * @param       *pData:
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Vision_Def::DataPack(uint8_t *pData)
{
    static VisToRobPacket Rx_Data;

    if (pData != NULL) {
        memcpy(&Rx_Data, pData, sizeof(VisToRobPacket));
        if (Rx_Data.checksum == Get_CRC16_Check_Sum(pData, sizeof(VisToRobPacket) - 2, 0xffff)) {
            st.armor_id = Rx_Data.id;
            st.armor_num = Rx_Data.armors_num;
            memcpy(&st.xw, &Rx_Data.x, sizeof(float) * 11);
            if (Rx_Data.tracking == true) {
                state = true;
                autoSolveTrajectory(&pitch, &yaw, &aim_x, &aim_y, &aim_z);
            } else {
                state = false;
            }
        }
    }
}

void Vision_Def::Send(float pitch, float yaw)
{
    static RobToVisPacket Tx_Data;

    Tx_Data.header = 0x5A;
    Tx_Data.detect_color = 1;
    Tx_Data.reset_tracker = 0;
    Tx_Data.reserved = 0;

    Tx_Data.pitch = pitch / 180.0f * PI;
    Tx_Data.yaw = yaw / 180.0f * PI;

    Tx_Data.aim_x = aim_x;
    Tx_Data.aim_y = aim_y;
    Tx_Data.aim_z = aim_z;

    Tx_Data.checksum = Get_CRC16_Check_Sum((uint8_t *)&Tx_Data, sizeof(RobToVisPacket) - 2, 0xFFFF);

    CDC_Transmit_FS((uint8_t *)&Tx_Data, sizeof(RobToVisPacket));
}
