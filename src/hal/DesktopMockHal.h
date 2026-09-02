#pragma once

#include "IHal.h"

namespace LogosRobotics::Hal
{

class DesktopMockHal : public IHal
{
public:

    Core::Result initialize() override;

    Core::Result enableMotor(
        Core::Motor motor) override;

    Core::Result disableMotor(
        Core::Motor motor) override;

    Core::Result setDirection(
        Core::Motor motor,
        Core::Direction direction) override;

    Core::Result stepMotor(
        Core::Motor motor) override;

    Core::Result stepMotors(
        bool stepA,
        bool stepB) override;

    bool isLimitActive(
        Limit limit) const override;

    Core::Result liftUp() override;

    Core::Result liftDown() override;
};

} // namespace LogosRobotics::Hal