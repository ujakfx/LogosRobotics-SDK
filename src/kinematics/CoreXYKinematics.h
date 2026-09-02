/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    CoreXYKinematics.h

 Purpose:
    Implements CoreXY kinematics.

 Module:
    Kinematics

 Build:
    002

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include "IKinematics.h"

namespace LogosRobotics::Kinematics
{

class CoreXYKinematics : public IKinematics
{
public:

    CoreXYKinematics() = default;

    ~CoreXYKinematics() override = default;

    Core::Result initialize() override;

    Core::Result transform(
        const Core::Position& position,
        Core::MotorCommandBuffer& commands) const override;

};

} // namespace LogosRobotics::Kinematics