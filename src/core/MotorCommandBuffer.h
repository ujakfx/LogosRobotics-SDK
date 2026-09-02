/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    MotorCommandBuffer.h

 Purpose:
    Defines a fixed-size buffer for motor commands.

 Module:
    Core

 Build:
    002

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include "Constants.h"
#include "MotorCommand.h"

#include <cstdint>

namespace LogosRobotics::Core
{

struct MotorCommandBuffer
{
    MotorCommand commands[MaxMotors];

    std::uint8_t count {0};

    void clear()
    {
        count = 0;
    }

    bool add(const MotorCommand& command)
    {
        if (count >= MaxMotors)
        {
            return false;
        }

        commands[count] = command;
        ++count;

        return true;
    }

    bool empty() const
    {
        return count == 0;
    }

    bool full() const
    {
        return count >= MaxMotors;
    }

};

} // namespace LogosRobotics::Core