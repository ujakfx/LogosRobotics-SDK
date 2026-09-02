/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    HomingController.cpp

 Purpose:
    Implements the machine homing sequence.

 Module:
    Motion

 Build:
    002

 License:
    MIT
---------------------------------------------------------------
*/

#include "HomingController.h"

namespace LogosRobotics::Motion
{

namespace
{

constexpr Core::StepCount BackoffSteps = 100;

}


// -------------------------------------------------------------
// CONSTRUCTOR
// -------------------------------------------------------------

HomingController::HomingController(
    Hal::IHal& hal)
    :
    m_hal(hal)
{
}


// -------------------------------------------------------------
// HOME
// -------------------------------------------------------------

Core::Result HomingController::home()
{
    Core::Result result;


    // ---------------------------------------------------------
    // X axis
    // ---------------------------------------------------------

    if (!m_hal.isLimitActive(
            Hal::Limit::XMin))
    {
        result = homeX();

        if (result != Core::Result::Ok)
        {
            return result;
        }


        result = backoffX();

        if (result != Core::Result::Ok)
        {
            return result;
        }


        result = slowHomeX();

        if (result != Core::Result::Ok)
        {
            return result;
        }
    }


    // ---------------------------------------------------------
    // Y axis
    // ---------------------------------------------------------

    if (!m_hal.isLimitActive(
            Hal::Limit::YMin))
    {
        result = homeY();

        if (result != Core::Result::Ok)
        {
            return result;
        }


        result = backoffY();

        if (result != Core::Result::Ok)
        {
            return result;
        }


        result = slowHomeY();

        if (result != Core::Result::Ok)
        {
            return result;
        }
    }


    // ---------------------------------------------------------
    // Motors OFF after homing
    // ---------------------------------------------------------

    m_hal.disableMotor(
        Core::Motor::A);

    m_hal.disableMotor(
        Core::Motor::B);


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// HOME X - FAST
//
// X_MIN direction:
//
//     Motor A = Positive
//     Motor B = Positive
//
// This physically moves the carriage toward X_MIN.
// -------------------------------------------------------------

Core::Result HomingController::homeX()
{
    Core::Result result;


    result =
        m_hal.setDirection(
            Core::Motor::A,
            Core::Direction::Positive);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_hal.setDirection(
            Core::Motor::B,
            Core::Direction::Positive);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_hal.enableMotor(
            Core::Motor::A);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_hal.enableMotor(
            Core::Motor::B);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    while (!m_hal.isLimitActive(
        Hal::Limit::XMin))
    {
        result =
            m_hal.stepMotors(
                true,
                true);

        if (result != Core::Result::Ok)
        {
            return result;
        }
    }


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// BACKOFF X
//
// Move away from X_MIN by 100 coordinated steps.
//
// X_MIN escape:
//
//     Motor A = Negative
//     Motor B = Negative
// -------------------------------------------------------------

Core::Result HomingController::backoffX()
{
    Core::Result result;


    result =
        m_hal.setDirection(
            Core::Motor::A,
            Core::Direction::Negative);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_hal.setDirection(
            Core::Motor::B,
            Core::Direction::Negative);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    for (Core::StepCount i = 0;
         i < BackoffSteps;
         ++i)
    {
        result =
            m_hal.stepMotors(
                true,
                true);

        if (result != Core::Result::Ok)
        {
            return result;
        }
    }


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// SLOW HOME X
//
// Return slowly toward X_MIN.
//
//     Motor A = Positive
//     Motor B = Positive
// -------------------------------------------------------------

Core::Result HomingController::slowHomeX()
{
    Core::Result result;


    result =
        m_hal.setDirection(
            Core::Motor::A,
            Core::Direction::Positive);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_hal.setDirection(
            Core::Motor::B,
            Core::Direction::Positive);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    while (!m_hal.isLimitActive(
        Hal::Limit::XMin))
    {
        result =
            m_hal.stepMotors(
                true,
                true);

        if (result != Core::Result::Ok)
        {
            return result;
        }
    }


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// HOME Y - FAST
//
// Y_MIN direction:
//
//     Motor A = Positive
//     Motor B = Negative
//
// This physically moves the carriage toward Y_MIN.
// -------------------------------------------------------------

Core::Result HomingController::homeY()
{
    Core::Result result;


    result =
        m_hal.setDirection(
            Core::Motor::A,
            Core::Direction::Positive);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_hal.setDirection(
            Core::Motor::B,
            Core::Direction::Negative);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_hal.enableMotor(
            Core::Motor::A);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_hal.enableMotor(
            Core::Motor::B);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    while (!m_hal.isLimitActive(
        Hal::Limit::YMin))
    {
        result =
            m_hal.stepMotors(
                true,
                true);

        if (result != Core::Result::Ok)
        {
            return result;
        }
    }


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// BACKOFF Y
//
// Move away from Y_MIN by 100 coordinated steps.
//
// Y_MIN escape:
//
//     Motor A = Negative
//     Motor B = Positive
// -------------------------------------------------------------

Core::Result HomingController::backoffY()
{
    Core::Result result;


    result =
        m_hal.setDirection(
            Core::Motor::A,
            Core::Direction::Negative);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_hal.setDirection(
            Core::Motor::B,
            Core::Direction::Positive);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    for (Core::StepCount i = 0;
         i < BackoffSteps;
         ++i)
    {
        result =
            m_hal.stepMotors(
                true,
                true);

        if (result != Core::Result::Ok)
        {
            return result;
        }
    }


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// SLOW HOME Y
//
// Return slowly toward Y_MIN.
//
//     Motor A = Positive
//     Motor B = Negative
// -------------------------------------------------------------

Core::Result HomingController::slowHomeY()
{
    Core::Result result;


    result =
        m_hal.setDirection(
            Core::Motor::A,
            Core::Direction::Positive);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_hal.setDirection(
            Core::Motor::B,
            Core::Direction::Negative);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    while (!m_hal.isLimitActive(
        Hal::Limit::YMin))
    {
        result =
            m_hal.stepMotors(
                true,
                true);

        if (result != Core::Result::Ok)
        {
            return result;
        }
    }


    return Core::Result::Ok;
}

} // namespace LogosRobotics::Motion