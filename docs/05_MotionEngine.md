\# Logos Robotics SDK — MotionEngine



\## Overview



`MotionEngine` is the low-level motion API of the Logos Robotics SDK.



Its purpose is to coordinate the main motion-control components of the SDK

and provide a deterministic interface for machine homing and absolute

positioning.



`MotionEngine` does not directly access hardware.



Instead, it coordinates:



\- Kinematics

\- Motion Planner

\- Homing Controller

\- Machine coordinate state



The current implementation is designed for the reference CoreXY machine

running on ESP32-C6.



\---



\# Role in the Architecture



`MotionEngine` occupies the low-level motion-control layer of the SDK.



```text

Application

&#x20;    │

&#x20;    ▼

MotionPlanner

&#x20;    │

&#x20;    ▼

MotionEngine

&#x20;    │

&#x20;    ├──────────────► IKinematics

&#x20;    │

&#x20;    ├──────────────► LinearMotionPlanner

&#x20;    │

&#x20;    └──────────────► HomingController

&#x20;                          │

&#x20;                          ▼

&#x20;                         HAL

&#x20;                          │

&#x20;                          ▼

&#x20;                       Hardware

