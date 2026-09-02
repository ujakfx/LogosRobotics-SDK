/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    LinearMotionPlanner.h

 Purpose:
    Linear motion planner.

 Module:
    Motion

 Build:
    008

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include <planner/IMotionPlanner.h>
#include <hal/IHal.h>
#include <core/MotorCommandBuffer.h>

namespace LogosRobotics::Motion
{

class LinearMotionPlanner : public IMotionPlanner
{
public:

    explicit LinearMotionPlanner(
        Hal::IHal& hal);

    Core::Result initialize() override;

    Core::Result moveTo(
        const Core::Position& position) override;

    bool busy() const override;

    Core::Result execute(
        const Core::MotorCommandBuffer& commands);

private:

    Core::Result executeCoordinated(
        Core::StepCount stepsA,
        Core::Direction directionA,
        Core::StepCount stepsB,
        Core::Direction directionB);

    Hal::IHal& m_hal;

    bool m_busy {false};
};

} // namespace LogosRobotics::Motion