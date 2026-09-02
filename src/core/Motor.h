/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    Motor.h

 Purpose:
    Defines the physical motors used by the motion system.

 Module:
    Core

 Build:
    001

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include <cstdint>

namespace LogosRobotics::Core
{

enum class Motor : std::uint8_t
{
    A = 0,
    B,
    C,
    D
};

} // namespace LogosRobotics::Core