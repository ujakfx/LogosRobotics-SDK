/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    HomingController.h

 Purpose:
    Controls the machine homing sequence.

 Module:
    Motion

 Build:
    002

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include <core/Types.h>
#include <core/Result.h>
#include <hal/IHal.h>

namespace LogosRobotics::Motion
{

class HomingController
{
public:

    explicit HomingController(
        Hal::IHal& hal);


    Core::Result home();


private:

    Core::Result homeX();

    Core::Result homeY();


    Core::Result backoffX();

    Core::Result backoffY();


    Core::Result slowHomeX();

    Core::Result slowHomeY();


    Hal::IHal& m_hal;
};

} // namespace LogosRobotics::Motion