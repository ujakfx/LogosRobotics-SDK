\# Changelog



All notable changes to Logos Robotics SDK are documented in this file.



\---



\# Build 009



\## MotionEngine Functional Verification



\### Added



\- MotionEngine low-level motion API

\- Absolute machine positioning

\- Internal machine position tracking

\- Homing integration

\- Millimeter-to-step conversion through MachineConfig

\- Integration between MotionEngine, Kinematics, Planner and HomingController



\### Verified



\- MotionEngine initialization

\- Homing

\- Machine coordinate initialization

\- Absolute positioning

\- X-axis movement

\- Y-axis movement

\- Diagonal movement

\- Coordinated CoreXY motion

\- Movement to machine center

\- Return to HOME



\### Hardware Verification



Verified on the physical ESP32-C6 CoreXY reference machine.



Test sequence:



```text

HOME

&#x20; ↓

CENTER (229,308)

&#x20; ↓

(100,100)

&#x20; ↓

(300,100)

&#x20; ↓

(300,400)

&#x20; ↓

CENTER (229,308)

&#x20; ↓

HOME

