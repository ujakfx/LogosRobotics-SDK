/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    Position.h

 Purpose:
    Defines a two-dimensional logical position.

 Module:
    Core

 Build:
    001

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include "Types.h"

namespace LogosRobotics::Core
{

struct Position
{
    Coordinate x {0};
    Coordinate y {0};
};

} // namespace LogosRobotics::Core