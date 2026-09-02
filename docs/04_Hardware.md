\# Logos Robotics SDK — Hardware



\## Overview



This document describes the hardware configuration of the current reference

implementation of Logos Robotics SDK.



The reference machine is a two-axis CoreXY plotter controlled by an ESP32-C6

using the Arduino Framework.



The hardware is accessed through the Hardware Abstraction Layer (HAL), which

keeps hardware-specific implementation details outside the motion-control

logic.



\---



\# Reference Hardware



The current reference machine consists of:



```text

Controller:

ESP32-C6



Framework:

Arduino



Motion system:

CoreXY



Stepper motors:

2 × NEMA17



Stepper drivers:

2 × DM542



Pen actuator:

MG90S servo



Limit switches:

4 × mechanical limit switches

