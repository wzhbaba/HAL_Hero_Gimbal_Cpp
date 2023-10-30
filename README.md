# RM2023赛季丝杆英雄云台工程框架
## 设备信息
MCU：STM32F407IIH(Robomaster A型开发板)
IMU：HI226(基于BMI088传感器 串口通信)
Pitch轴：M3508电机带丝杆驱动
Yaw轴：6020电机带1：2减速比
发射机构：4摩擦轮（M3508）+1预置轮（M2006）
控制方式：
&emsp;&emsp;遥控控制：DT7
&emsp;&emsp;键鼠控制：图传链路

## 软件环境
开发环境：
STM32CubeMX
VSCode
调试环境：
Ozone

## 代码框架

Gimbal_Screw_CPP
├─.vscode
├─build
├─Core
│&emsp;├─Inc
│&emsp;└─Src
├─Drivers
│&emsp;├─CMSIS
│&emsp;│&emsp;├─Device
│&emsp;│&emsp;└─Include
│&emsp;└─STM32F4xx_HAL_Driver
├─Middlewares
│&emsp;├─ST
│&emsp;│&emsp;├─ARM
│&emsp;│&emsp;└─STM32_USB_Device_Library
│&emsp;└─Third_Party
├─USB_DEVICE
└─User
&emsp;&emsp;├─Algorithm
&emsp;&emsp;├─Application
&emsp;&emsp;├─BSP
&emsp;&emsp;├─Config
&emsp;&emsp;├─Devices
&emsp;&emsp;└─Modules

### 驱动层相关文件
#### Core
CubeMX生成的核心文件
#### Drivers
CubeMX生成的STM32外设驱动
#### Middleware
CubeMX生成的中间组件相关文件（包含了DSP库、FreeRTOS和USB设备驱动）
#### Tips:驱动层相关文件仅可修改Core内的main.c、freertos.c和main.h，
#### 编辑其他文件可能会出现编译无法通过的情况！！！！

### User文件夹相关文件
#### BSP(Board Support Pack)
该文件夹对驱动层内的官方初始化函数和部分传输函数进行再封装，同时重定义了部分官方函数（谨慎修改）



#### Device
该文件夹中的文件是封装好的相关电机库，遥控器库，裁判系统库和陀螺仪库


#### Module
该文件夹中的文件用于底盘运动解算，P轴位置控制，Yaw轴任务控制，发射控制以及与上位机通信子任务


#### Application
该文件夹内的文件为云台运动控制任务和键鼠控制任务

