/**
 *******************************************************************************
 * @file      : Referee.cpp
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
#include <Referee.h>
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
Referee_Def Referee;
/* Private function prototypes -----------------------------------------------*/

/**
 * @brief
 * @param       pData:
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Referee_Def::DataPack(uint8_t* pData)
{
    uint16_t judge_length;  // 统计一帧数据长度
    //	CmdID = 0; //数据命令码解析
    // 空数据包，则不作任何处理
    if (pData == NULL)
        return;

    // 写入帧头数据(5-byte),用于判断是否开始存储裁判数据
    memcpy(&FrameHeader, pData, LEN_HEADER);

    // 判断帧头数据(0)是否为0xA5
    if (pData[SOF] == JUDGE_FRAME_HEADER) {
        // 帧头CRC8校验
        if (Verify_CRC8_Check_Sum(pData, LEN_HEADER) == TRUE) {
            // 统计一帧数据长度(byte),用于CR16校验
            judge_length = pData[DATA_LENGTH] + LEN_HEADER + LEN_CMDID + LEN_TAIL;
            // 帧尾CRC16校验
            if (Verify_CRC16_Check_Sum(pData, judge_length) == TRUE) {
                // 2个8位拼成16位int
                CmdID = (pData[6] << 8 | pData[5]);
                // 解析数据命令码,将数据拷贝到相应结构体中(注意拷贝数据的长度)
                // 第8个字节开始才是数据 data=7
                switch (CmdID) {
                    case ID_command_data:  // 0x0304
                        memcpy(&CommaData, (pData + DATA), LEN_command_data);
                        KeyProcess();
                        break;
                }
            }
        }
    }
}

void Referee_Def::KeyProcess()
{
    for (short i = 0; i < 16; i++) {
        if (CommaData.keyboard_value & (0x01 << i)) {
            KeyState[i].isPressed = 1;
        } else {
            KeyState[i].isPressed = 0;
        }
    }

    if (CommaData.left_button_down == 0x01) {
        KeyState[REFEREE_MOUSE_L].isPressed = 1;
    } else {
        KeyState[REFEREE_MOUSE_L].isPressed = 0;
    }
    if (CommaData.right_button_down == 0x01) {
        KeyState[REFEREE_MOUSE_R].isPressed = 1;
    } else {
        KeyState[REFEREE_MOUSE_R].isPressed = 0;
    }

    for (short i = 0; i < 18; i++) {
        if (KeyState[i].isPressed == 1 && KeyState[i].LastState == 0) {
            KeyState[i].isTicked++;
        }

        if (KeyState[i].isTicked % 2 == 0) {
            KeyState[i].isTicked = 0;
        }

        KeyState[i].LastState = KeyState[i].isPressed;
    }
}

void Referee_Def::BoardCommu(uint8_t can_rx_data[])
{
    Referee.PowerHeatData.shooter_id1_42mm_cooling_heat = can_rx_data[0] << 8 | can_rx_data[1];
    Referee.GameRobotStat.shooter_id1_42mm_cooling_limit = can_rx_data[2] << 8 | can_rx_data[3];
    Referee.GameRobotStat.shooter_id1_42mm_speed_limit = can_rx_data[4] << 8 | can_rx_data[5];
    Referee.GameRobotStat.mains_power_shooter_output = can_rx_data[6] << 8 | can_rx_data[7];
}