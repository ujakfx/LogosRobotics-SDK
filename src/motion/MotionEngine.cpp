/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    MotionEngine.cpp

 Purpose:
    Motion Engine implementation.

 Module:
    Motion

 Build:
    008

 License:
    MIT
---------------------------------------------------------------
*/

#include "MotionEngine.h"

#include <config/MachineConfig.h>

namespace LogosRobotics::Motion
{

MotionEngine::MotionEngine(
    Kinematics::IKinematics& kinematics,
    LinearMotionPlanner& planner,
    HomingController& homing)
    :
    m_kinematics(kinematics),
    m_planner(planner),
    m_homing(homing)
{
}


// -------------------------------------------------------------
// INITIALIZE
// -------------------------------------------------------------

Core::Result MotionEngine::initialize()
{
    Core::Result result =
        m_planner.initialize();

    if (result != Core::Result::Ok)
    {
        return result;
    }


    result =
        m_kinematics.initialize();

    if (result != Core::Result::Ok)
    {
        return result;
    }


    // ---------------------------------------------------------
    // Initial logical position.
    //
    // Position is expressed in millimeters.
    //
    // Physical HOME must still be established by home().
    // ---------------------------------------------------------

    m_currentPosition.x = 0;
    m_currentPosition.y = 0;


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// HOME
// -------------------------------------------------------------

Core::Result MotionEngine::home()
{
    /*
    -----------------------------------------------------------
    Physical homing is performed by HomingController.

        X_MIN
        back-off
        slow re-approach

        Y_MIN
        back-off
        slow re-approach
    -----------------------------------------------------------
    */

    Core::Result result =
        m_homing.home();

    if (result != Core::Result::Ok)
    {
        return result;
    }


    /*
    -----------------------------------------------------------
    Physical HOME is now established.

    Logical machine position:

        X = 0 mm
        Y = 0 mm
    -----------------------------------------------------------
    */

    m_currentPosition.x = 0;
    m_currentPosition.y = 0;


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// MOVE TO
// -------------------------------------------------------------

Core::Result MotionEngine::moveTo(
    const Core::Position& position)
{
    /*
    -----------------------------------------------------------
    Position is an ABSOLUTE Cartesian position in millimeters.

    Calculate movement relative to current position.
    -----------------------------------------------------------
    */

    Core::Position deltaMm;

    deltaMm.x =
        position.x - m_currentPosition.x;

    deltaMm.y =
        position.y - m_currentPosition.y;


    /*
    -----------------------------------------------------------
    Convert Cartesian millimeters to Cartesian steps.
    -----------------------------------------------------------
    */

    Core::Position deltaSteps;

    deltaSteps.x =
        deltaMm.x *
        static_cast<Core::Coordinate>(
            Config::MachineConfig::XStepsPerMm);

    deltaSteps.y =
        deltaMm.y *
        static_cast<Core::Coordinate>(
            Config::MachineConfig::YStepsPerMm);


    /*
    -----------------------------------------------------------
    Transform Cartesian STEP movement into motor commands.
    -----------------------------------------------------------
    */

    Core::MotorCommandBuffer commands;

    Core::Result result =
        m_kinematics.transform(
            deltaSteps,
            commands);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    /*
    -----------------------------------------------------------
    Planner performs coordinated motor execution.
    -----------------------------------------------------------
    */

    result =
        m_planner.execute(commands);

    if (result != Core::Result::Ok)
    {
        return result;
    }


    /*
    -----------------------------------------------------------
    Update logical position only after successful execution.

    Position remains in millimeters.
    -----------------------------------------------------------
    */

    m_currentPosition = position;


    return Core::Result::Ok;
}

} // namespace LogosRobotics::Motion