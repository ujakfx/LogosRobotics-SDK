/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    MotionEngine.h

 Purpose:
    Motion engine interface and implementation declaration.

 Module:
    Motion

 Build:
    007

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include <core/Position.h>
#include <core/Result.h>

#include <kinematics/IKinematics.h>
#include <planner/LinearMotionPlanner.h>
#include <motion/HomingController.h>

namespace LogosRobotics::Motion
{

class MotionEngine
{
public:

    MotionEngine(
        Kinematics::IKinematics& kinematics,
        LinearMotionPlanner& planner,
        HomingController& homing);

    Core::Result initialize();

    Core::Result home();

    Core::Result moveTo(
        const Core::Position& position);

private:

    Kinematics::IKinematics& m_kinematics;

    LinearMotionPlanner& m_planner;

    HomingController& m_homing;

    Core::Position m_currentPosition;
};

} // namespace LogosRobotics::Motion