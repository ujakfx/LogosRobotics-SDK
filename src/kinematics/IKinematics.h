/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    IKinematics.h

 Purpose:
    Defines the kinematics transformation interface.

 Module:
    Kinematics

 Build:
    001

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include "../core/Position.h"
#include "../core/MotorCommandBuffer.h"
#include "../core/Result.h"

namespace LogosRobotics::Kinematics
{

class IKinematics
{
public:

    virtual ~IKinematics() = default;

    virtual Core::Result initialize() = 0;

    virtual Core::Result transform(
        const Core::Position& position,
        Core::MotorCommandBuffer& commands) const = 0;

};

} // namespace LogosRobotics::Kinematics