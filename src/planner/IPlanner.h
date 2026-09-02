/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    IPlanner.h

 Purpose:
    Defines the high-level motion planning interface.

 Module:
    Planner

 Build:
    001

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include "../core/Position.h"
#include "../core/Result.h"

namespace LogosRobotics::Planner
{

class IPlanner
{
public:

    virtual ~IPlanner() = default;

    virtual Core::Result initialize() = 0;

    virtual Core::Result home() = 0;

    virtual Core::Result moveTo(
        const Core::Position& position) = 0;

    virtual Core::Result stop() = 0;

    virtual bool isBusy() const = 0;

};

} // namespace LogosRobotics::Planner