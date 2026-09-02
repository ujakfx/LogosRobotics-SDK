/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    IMotionPlanner.h

 Purpose:
    Motion Planner interface.

 Module:
    Motion

 Build:
    006

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include <core/Position.h>
#include <core/Result.h>

namespace LogosRobotics::Motion
{

class IMotionPlanner
{
public:

    virtual ~IMotionPlanner() = default;

    virtual Core::Result initialize() = 0;

    virtual Core::Result moveTo(
        const Core::Position& position) = 0;

    virtual bool busy() const = 0;
};

} // namespace LogosRobotics::Motion