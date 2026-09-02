/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    CoreXYKinematics_Test.cpp

 Purpose:
    Desktop unit test for CoreXY kinematics.

 Module:
    Tests

 Build:
    012

 License:
    MIT
---------------------------------------------------------------
*/

#include <cassert>
#include <iostream>

#include "kinematics/CoreXYKinematics.h"

using namespace LogosRobotics;

int main()
{
    std::cout
        << "========================================\n"
        << " Logos Robotics SDK\n"
        << " CoreXY Kinematics Test\n"
        << "========================================\n\n";


    Kinematics::CoreXYKinematics kinematics;


    assert(
        kinematics.initialize()
        == Core::Result::Ok);


    /*
    -----------------------------------------------------------
    Test:

        X = +100 steps
        Y = +50 steps

    Verified machine convention:

        X+ = A-, B-
        Y+ = A-, B+

    Therefore:

        A = -X - Y = -150
        B = -X + Y = -50
    -----------------------------------------------------------
    */

    Core::Position position;

    position.x = 100;
    position.y = 50;


    Core::MotorCommandBuffer commands;


    Core::Result result =
        kinematics.transform(
            position,
            commands);


    assert(
        result == Core::Result::Ok);


    assert(
        commands.count == 2);


    const Core::MotorCommand& commandA =
        commands.commands[0];

    const Core::MotorCommand& commandB =
        commands.commands[1];


    assert(
        commandA.motor
        == Core::Motor::A);

    assert(
        commandA.direction
        == Core::Direction::Negative);

    assert(
        commandA.steps
        == 150);


    assert(
        commandB.motor
        == Core::Motor::B);

    assert(
        commandB.direction
        == Core::Direction::Negative);

    assert(
        commandB.steps
        == 50);


    std::cout
        << "CoreXY transformation passed.\n";

    std::cout
        << "A: Negative, 150 steps\n";

    std::cout
        << "B: Negative, 50 steps\n";

    std::cout
        << "Test passed.\n";


    return 0;
}