/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    Result.h

 Purpose:
    Defines common operation results.

 Module:
    Core

 Build:
    002

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include <cstdint>

namespace LogosRobotics::Core
{

enum class Result : std::uint8_t
{
    Ok = 0,

    InvalidArgument,

    BufferOverflow,

    NotInitialized,

    HardwareError,

    Error
};

} // namespace LogosRobotics::Core