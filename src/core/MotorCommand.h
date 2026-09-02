#pragma once

#include "Motor.h"
#include "Direction.h"
#include "Types.h"

namespace LogosRobotics::Core
{

struct MotorCommand
{
    Motor motor;
    Direction direction;
    StepCount steps;
};
}
