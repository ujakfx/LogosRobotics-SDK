/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    IHal.h

 Purpose:
    Hardware Abstraction Layer interface.

 Module:
    HAL

 Build:
    006

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include "../core/Direction.h"
#include "../core/Motor.h"
#include "../core/Result.h"

namespace LogosRobotics::Hal
{

enum class Limit
{
    XMin,
    XMax,
    YMin,
    YMax
};


class IHal
{
public:

    virtual ~IHal() = default;

    virtual Core::Result initialize() = 0;

    virtual Core::Result enableMotor(
        Core::Motor motor) = 0;

    virtual Core::Result disableMotor(
        Core::Motor motor) = 0;

    virtual Core::Result setDirection(
        Core::Motor motor,
        Core::Direction direction) = 0;

    virtual Core::Result stepMotor(
        Core::Motor motor) = 0;

    virtual Core::Result stepMotors(
        bool stepA,
        bool stepB) = 0;

    virtual bool isLimitActive(
        Limit limit) const = 0;

    virtual Core::Result liftUp() = 0;

    virtual Core::Result liftDown() = 0;
};

} // namespace LogosRobotics::Hal