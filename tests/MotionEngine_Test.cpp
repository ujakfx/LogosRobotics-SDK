/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    MotionEngine_Test.cpp

 Purpose:
    MotionEngine desktop integration test.

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

#include "motion/MotionEngine.h"
#include "kinematics/CoreXYKinematics.h"
#include "planner/LinearMotionPlanner.h"
#include "motion/HomingController.h"
#include "hal/DesktopMockHal.h"

using namespace LogosRobotics;

int main()
{
    std::cout
        << "========================================\n"
        << " Logos Robotics SDK\n"
        << " MotionEngine Test\n"
        << "========================================\n\n";


    Hal::DesktopMockHal hal;

    Kinematics::CoreXYKinematics kinematics;

    Motion::LinearMotionPlanner planner(
        hal);

    Motion::HomingController homing(
        hal);

    Motion::MotionEngine engine(
        kinematics,
        planner,
        homing);


    assert(
        engine.initialize()
        == Core::Result::Ok);


    std::cout
        << "Moving to X=100, Y=50...\n";


    Core::Position position;

    position.x = 100;
    position.y = 50;


    Core::Result result =
        engine.moveTo(position);


    assert(
        result == Core::Result::Ok);


    std::cout
        << "Motion completed successfully.\n";

    std::cout
        << "Test passed.\n";


    return 0;
}