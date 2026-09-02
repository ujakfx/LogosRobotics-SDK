/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    LinearMotionPlanner.cpp

 Purpose:
    Linear motion planner implementation.

 Module:
    Motion

 Build:
    009

 License:
    MIT
---------------------------------------------------------------
*/

#include "LinearMotionPlanner.h"

namespace LogosRobotics::Motion
{

LinearMotionPlanner::LinearMotionPlanner(
    Hal::IHal& hal)
    :
    m_hal(hal)
{
}

Core::Result LinearMotionPlanner::initialize()
{
    m_busy = false;

    return m_hal.initialize();
}

Core::Result LinearMotionPlanner::moveTo(
    const Core::Position& position)
{
    (void)position;

    return Core::Result::Ok;
}

bool LinearMotionPlanner::busy() const
{
    return m_busy;
}

Core::Result LinearMotionPlanner::execute(
    const Core::MotorCommandBuffer& commands)
{
    if (commands.empty())
    {
        return Core::Result::Ok;
    }

    m_busy = true;

    Core::StepCount stepsA = 0;
    Core::StepCount stepsB = 0;

    Core::Direction directionA =
        Core::Direction::Positive;

    Core::Direction directionB =
        Core::Direction::Positive;

    /*
    -----------------------------------------------------------
    Read motor commands.
    -----------------------------------------------------------
    */

    for (std::uint8_t i = 0;
         i < commands.count;
         ++i)
    {
        const Core::MotorCommand& command =
            commands.commands[i];

        if (command.motor == Core::Motor::A)
        {
            stepsA = command.steps;
            directionA = command.direction;
        }
        else if (command.motor == Core::Motor::B)
        {
            stepsB = command.steps;
            directionB = command.direction;
        }
    }

    /*
    -----------------------------------------------------------
    Set directions BEFORE any STEP pulse.
    -----------------------------------------------------------
    */

    if (stepsA > 0)
    {
        Core::Result result =
            m_hal.setDirection(
                Core::Motor::A,
                directionA);

        if (result != Core::Result::Ok)
        {
            m_busy = false;
            return result;
        }

        result =
            m_hal.enableMotor(Core::Motor::A);

        if (result != Core::Result::Ok)
        {
            m_busy = false;
            return result;
        }
    }

    if (stepsB > 0)
    {
        Core::Result result =
            m_hal.setDirection(
                Core::Motor::B,
                directionB);

        if (result != Core::Result::Ok)
        {
            m_busy = false;
            return result;
        }

        result =
            m_hal.enableMotor(Core::Motor::B);

        if (result != Core::Result::Ok)
        {
            m_busy = false;
            return result;
        }
    }

    /*
    -----------------------------------------------------------
    Coordinated linear interpolation.

    totalSteps = number of STEP cycles of the dominant motor.

    The accumulators determine whether Motor A and/or Motor B
    must receive a STEP during each cycle.
    -----------------------------------------------------------
    */

    const Core::StepCount totalSteps =
        (stepsA > stepsB)
            ? stepsA
            : stepsB;

    Core::StepCount accumulatorA = 0;
    Core::StepCount accumulatorB = 0;

    for (Core::StepCount i = 0;
         i < totalSteps;
         ++i)
    {
        accumulatorA += stepsA;
        accumulatorB += stepsB;

        bool stepA = false;
        bool stepB = false;

        if (accumulatorA >= totalSteps)
        {
            stepA = true;
            accumulatorA -= totalSteps;
        }

        if (accumulatorB >= totalSteps)
        {
            stepB = true;
            accumulatorB -= totalSteps;
        }

        /*
        -------------------------------------------------------
        One coordinated STEP cycle.

        If both are true:
            A and B STEP simultaneously.

        If only A is true:
            only A STEP.

        If only B is true:
            only B STEP.
        -------------------------------------------------------
        */

        Core::Result result =
            m_hal.stepMotors(stepA, stepB);

        if (result != Core::Result::Ok)
        {
            m_busy = false;
            return result;
        }
    }

    /*
    -----------------------------------------------------------
    Disable motors only AFTER the complete coordinated move.
    -----------------------------------------------------------
    */

    if (stepsA > 0)
    {
        Core::Result result =
            m_hal.disableMotor(Core::Motor::A);

        if (result != Core::Result::Ok)
        {
            m_busy = false;
            return result;
        }
    }

    if (stepsB > 0)
    {
        Core::Result result =
            m_hal.disableMotor(Core::Motor::B);

        if (result != Core::Result::Ok)
        {
            m_busy = false;
            return result;
        }
    }

    m_busy = false;

    return Core::Result::Ok;
}

} // namespace LogosRobotics::Motion