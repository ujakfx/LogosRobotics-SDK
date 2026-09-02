/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    CoreXYKinematics.cpp

 Purpose:
    Implements CoreXY kinematics.

 Module:
    Kinematics

 Build:
    003

 License:
    MIT
---------------------------------------------------------------
*/

#include "CoreXYKinematics.h"
#include <cstdlib>

namespace LogosRobotics::Kinematics
{

Core::Result CoreXYKinematics::initialize()
{
    return Core::Result::Ok;
}

Core::Result CoreXYKinematics::transform(
    const Core::Position& position,
    Core::MotorCommandBuffer& commands) const
{
    commands.clear();


    // ---------------------------------------------------------
    // CoreXY transformation
    //
    // Machine motor orientation:
    //
    // X+ = A-, B-
    // Y+ = A-, B+
    //
    // Therefore:
    //
    // A = -X - Y
    // B = -X + Y
    // ---------------------------------------------------------

    Core::Coordinate deltaA =
        -position.x - position.y;

    Core::Coordinate deltaB =
        -position.x + position.y;


    Core::Direction directionA =
        (deltaA >= 0)
            ? Core::Direction::Positive
            : Core::Direction::Negative;


    Core::Direction directionB =
        (deltaB >= 0)
            ? Core::Direction::Positive
            : Core::Direction::Negative;


    Core::StepCount stepsA =
        static_cast<Core::StepCount>(
            std::abs(deltaA));


    Core::StepCount stepsB =
        static_cast<Core::StepCount>(
            std::abs(deltaB));


    Core::MotorCommand commandA
    {
        Core::Motor::A,
        directionA,
        stepsA
    };


    Core::MotorCommand commandB
    {
        Core::Motor::B,
        directionB,
        stepsB
    };


    if (!commands.add(commandA))
    {
        return Core::Result::BufferOverflow;
    }


    if (!commands.add(commandB))
    {
        return Core::Result::BufferOverflow;
    }


    return Core::Result::Ok;
}

} // namespace LogosRobotics::Kinematics