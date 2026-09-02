/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    Esp32ArduinoHal.h

 Purpose:
    ESP32 Arduino HAL implementation.

 Module:
    HAL

 Build:
    012

 License:
    MIT
---------------------------------------------------------------
*/

#pragma once

#include "IHal.h"

namespace LogosRobotics::Hal
{

class Esp32ArduinoHal : public IHal
{
public:

    Esp32ArduinoHal();

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


private:

    // ---------------------------------------------------------
    // Motor A
    // STEP -> GPIO 4
    // DIR  -> GPIO 10
    // ---------------------------------------------------------

    static constexpr int MotorAStepPin      = 4;
    static constexpr int MotorADirectionPin = 10;


    // ---------------------------------------------------------
    // Motor B
    // STEP -> GPIO 5
    // DIR  -> GPIO 11
    // ---------------------------------------------------------

    static constexpr int MotorBStepPin      = 5;
    static constexpr int MotorBDirectionPin = 11;


    // ---------------------------------------------------------
    // Limit switches
    //
    // OPEN   = LOW
    // ACTIVE = HIGH
    // ---------------------------------------------------------

    static constexpr int XMinLimitPin = 6;
    static constexpr int XMaxLimitPin = 7;

    static constexpr int YMinLimitPin = 18;
    static constexpr int YMaxLimitPin = 19;


    // ---------------------------------------------------------
    // Pen lift servo
    //
    // MG90S signal -> GPIO 2
    //
    // UP   = 40 degrees
    // DOWN = 80 degrees
    // ---------------------------------------------------------

    static constexpr int ServoPin = 2;

    static constexpr int LiftUpAngle   = 40;
    static constexpr int LiftDownAngle = 80;


    // Current servo position
    int m_servoAngle = LiftUpAngle;


    // Generate one servo pulse
    void servoPulse(
        int angle);
};

} // namespace LogosRobotics::Hal