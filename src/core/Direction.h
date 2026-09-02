/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    Direction.h

 Purpose:
    Defines the logical direction of motion.

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

enum class Direction : std::uint8_t
{
    Negative = 0,
    Positive = 1
};

} // namespace LogosRobotics::Core