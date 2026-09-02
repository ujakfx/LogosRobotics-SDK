/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    Axis.h

 Purpose:
    Defines the supported motion axes used throughout the SDK.

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

enum class Axis : std::uint8_t
{
    X = 0,
    Y,
    Z,

    A,
    B,
    C
};

}