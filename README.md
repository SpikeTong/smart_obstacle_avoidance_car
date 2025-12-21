# smart-obstacle-avoidance-car

An STM32-based IoT patrol car with obstacle avoidance

\# 基于STM32的智能避障巡检小车



\## 项目概述

本项目实现了一个具备自主避障、环境监测（温湿度、烟雾）和Wi-Fi数据上传功能的智能小车。主控采用STM32F103C8T6，通过云平台实现远程监控。



\## 硬件组成

\- 主控：STM32F103C8T6

\- 避障：HC-SR04超声波模块 + SG90舵机

\- 环境传感器：DHT11（温湿度）、MQ-2（烟雾）

\- 通信：ESP8266 Wi-Fi模块

\- 电机驱动：L298N



\## 软件架构

代码采用模块化设计，主要目录说明：

\- `/User`：主程序及应用层逻辑

\- `/Drivers`：各硬件外设驱动

\- `/Project`：Keil MDK工程文件

\- `/Core`：STM32核心启动文件



\## 如何使用

1\.  用Keil uVision5打开 `/Project` 目录下的工程文件。

2\.  根据硬件连接检查 `User/main.c` 中的引脚定义。

3\.  编译并下载到STM32开发板。



\## 功能演示

\- 上电后小车自动前进，实现动态避障。

\- 环境数据实时上传至OneNET云平台。

