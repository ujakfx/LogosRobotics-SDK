# Logos Robotics SDK

> **An educational open-source robotics motion control SDK designed to teach as much as it controls.**

**Logos Robotics SDK** is an educational open-source Software Development Kit (SDK) for robotics motion control.

The project focuses on clean software architecture, modular design, and real hardware verification. Its purpose is not only to build reliable motion control systems, but also to serve as an educational reference for embedded software engineering, robotics software architecture, kinematics, motion planning, and hardware abstraction.

---

# Vision

The goal of Logos Robotics SDK is to create a modular, hardware-independent motion control platform that can be reused across different robotics projects.

The first reference implementation targets a **CoreXY motion system running on ESP32-C6 using the Arduino Framework**.

The architecture is designed to support additional kinematic models and hardware platforms in future releases.

---

# Project Goals

- Educational
- Open Source
- Motion Control SDK
- Clean Architecture
- Hardware Independent
- Modular Design
- Real Hardware Verification
- Reusable Components

---

# Engineering Principles

- Every commit must compile.
- Every major feature must be verified before becoming part of the project.
- Documentation is part of the code.
- No magic numbers.
- Readable code over clever code.
- No feature enters the project without successful testing.
- Architecture first. Implementation second.
- Hardware-dependent features must be verified on real hardware.
- Higher layers must not depend on higher-level concepts from lower layers.
- Lower layers must remain independent of higher layers.

---

# Architecture

The SDK follows a layered architecture.

```text
                Application
                     │
                     ▼
              MotionPlanner
                     │
                     ▼
               MotionEngine
                     │
                     ▼
                IKinematics
                     │
                     ▼
                    HAL
                     │
                     ▼
                 Hardware