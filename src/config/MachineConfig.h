/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    MachineConfig.h

 Purpose:
    Machine-specific configuration and calibration values.

 Module:
    Config

 Build:
    002

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include <cstdint>

namespace LogosRobotics::Config
{

struct MachineConfig
{
    // ---------------------------------------------------------
    // Steps per millimeter
    //
    // Measured:
    //
    // X:
    //     1000 STEP = 100 mm
    //
    // Y:
    //     1000 STEP = 100 mm
    //
    // Therefore:
    //     10 STEP/mm
    // ---------------------------------------------------------

    static constexpr std::uint32_t XStepsPerMm = 10;
    static constexpr std::uint32_t YStepsPerMm = 10;


    // ---------------------------------------------------------
    // Working area
    //
    // Measured:
    //
    // X = 458 mm
    // Y = 616 mm
    // ---------------------------------------------------------

    static constexpr std::uint32_t XWorkMm = 458;
    static constexpr std::uint32_t YWorkMm = 616;


    // ---------------------------------------------------------
    // Center position
    // ---------------------------------------------------------

    static constexpr std::uint32_t XCenterMm =
        XWorkMm / 2;

    static constexpr std::uint32_t YCenterMm =
        YWorkMm / 2;


    // ---------------------------------------------------------
    // Convert millimeters to motor steps
    // ---------------------------------------------------------

    static constexpr std::uint32_t stepsFromMmX(
        std::uint32_t mm)
    {
        return mm * XStepsPerMm;
    }


    static constexpr std::uint32_t stepsFromMmY(
        std::uint32_t mm)
    {
        return mm * YStepsPerMm;
    }
};

} // namespace LogosRobotics::Config