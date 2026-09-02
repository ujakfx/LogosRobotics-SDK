# Logos Robotics SDK Architecture

## Overview

Logos Robotics SDK is an educational, open-source motion control SDK designed
to separate application-level motion planning, motion execution, kinematics,
and hardware control into independent and reusable modules.

The architecture is designed to support multiple motion systems and multiple
hardware platforms while keeping the core motion logic independent of the
underlying hardware.

The current reference implementation targets a CoreXY motion system running
on an ESP32-C6 using the Arduino Framework.

---

# Layered Architecture

The current SDK architecture consists of the following layers:

```text
                 Application
                      │
                      ▼
               MotionPlanner
                 High-Level API
                      │
                      ▼
                MotionEngine
                 Low-Level API
                      │
                      ▼
                 IKinematics
                      │
                      ▼
                     HAL
                      │
                      ▼
                  Hardware