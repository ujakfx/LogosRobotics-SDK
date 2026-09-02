/*
---------------------------------------------------------------
 Logos Robotics SDK

 File:
    Esp32ArduinoHal.cpp

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

#include "Esp32ArduinoHal.h"

#include <Arduino.h>
#include <cstdint>

namespace LogosRobotics::Hal
{

namespace
{

constexpr std::uint32_t StepPulseWidthUs = 200;


// -------------------------------------------------------------
// Servo timing
//
// MG90S:
//    50 Hz
//    20 ms period
//
// 40°  -> approximately 944 us
// 80°  -> approximately 1389 us
//
// Range used:
//    500 us -> 0°
//    2500 us -> 180°
// -------------------------------------------------------------

constexpr std::uint32_t ServoPeriodUs = 20000;

constexpr std::uint32_t ServoMinPulseUs = 500;
constexpr std::uint32_t ServoMaxPulseUs = 2500;

}


// -------------------------------------------------------------
// Constructor
// -------------------------------------------------------------

Esp32ArduinoHal::Esp32ArduinoHal()
{
}


// -------------------------------------------------------------
// INITIALIZE
// -------------------------------------------------------------

Core::Result Esp32ArduinoHal::initialize()
{
    // ---------------------------------------------------------
    // STEP pins
    // ---------------------------------------------------------

    pinMode(MotorAStepPin, OUTPUT);
    pinMode(MotorBStepPin, OUTPUT);


    // ---------------------------------------------------------
    // DIR pins start in OPEN state
    // ---------------------------------------------------------

    pinMode(MotorADirectionPin, INPUT);
    pinMode(MotorBDirectionPin, INPUT);


    // ---------------------------------------------------------
    // Limit switch inputs
    //
    // OPEN   = LOW
    // ACTIVE = HIGH
    // ---------------------------------------------------------

    pinMode(XMinLimitPin, INPUT_PULLUP);
    pinMode(XMaxLimitPin, INPUT_PULLUP);
    pinMode(YMinLimitPin, INPUT_PULLUP);
    pinMode(YMaxLimitPin, INPUT_PULLUP);


    // ---------------------------------------------------------
    // Servo
    // ---------------------------------------------------------

    pinMode(ServoPin, OUTPUT);

    digitalWrite(ServoPin, LOW);


    // ---------------------------------------------------------
    // STEP inactive
    // ---------------------------------------------------------

    digitalWrite(MotorAStepPin, LOW);
    digitalWrite(MotorBStepPin, LOW);


    // ---------------------------------------------------------
    // Initial pen position = UP
    // ---------------------------------------------------------

    m_servoAngle = LiftUpAngle;


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// ENABLE MOTOR
// -------------------------------------------------------------

Core::Result Esp32ArduinoHal::enableMotor(
    Core::Motor motor)
{
    // DM542 ENA- is permanently connected to GND.
    // No ESP32 enable pin is required.

    (void)motor;

    return Core::Result::Ok;
}


// -------------------------------------------------------------
// DISABLE MOTOR
// -------------------------------------------------------------

Core::Result Esp32ArduinoHal::disableMotor(
    Core::Motor motor)
{
    // DM542 ENA- is permanently connected to GND.
    // No ESP32 enable pin is required.

    (void)motor;

    return Core::Result::Ok;
}


// -------------------------------------------------------------
// SET DIRECTION
// -------------------------------------------------------------

Core::Result Esp32ArduinoHal::setDirection(
    Core::Motor motor,
    Core::Direction direction)
{
    const int pin =
        (motor == Core::Motor::A)
            ? MotorADirectionPin
            : MotorBDirectionPin;


    /*
    -----------------------------------------------------------
    DM542 DIR control:

    Positive:
        GPIO -> OUTPUT -> LOW
        Circuit closed to GND.

    Negative:
        GPIO -> INPUT
        Circuit open.

    This is the proven machine configuration.
    -----------------------------------------------------------
    */

    if (direction == Core::Direction::Positive)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
    else
    {
        pinMode(pin, INPUT);
    }


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// STEP ONE MOTOR
// -------------------------------------------------------------

Core::Result Esp32ArduinoHal::stepMotor(
    Core::Motor motor)
{
    const int pin =
        (motor == Core::Motor::A)
            ? MotorAStepPin
            : MotorBStepPin;


    digitalWrite(pin, HIGH);

    delayMicroseconds(
        StepPulseWidthUs);

    digitalWrite(pin, LOW);

    delayMicroseconds(
        StepPulseWidthUs);


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// STEP BOTH MOTORS
// -------------------------------------------------------------

Core::Result Esp32ArduinoHal::stepMotors(
    bool stepA,
    bool stepB)
{
    /*
    -----------------------------------------------------------
    Coordinated STEP pulse.

    Both selected STEP pins are raised before the pulse
    duration starts.
    -----------------------------------------------------------
    */

    if (stepA)
    {
        digitalWrite(
            MotorAStepPin,
            HIGH);
    }

    if (stepB)
    {
        digitalWrite(
            MotorBStepPin,
            HIGH);
    }


    delayMicroseconds(
        StepPulseWidthUs);


    if (stepA)
    {
        digitalWrite(
            MotorAStepPin,
            LOW);
    }

    if (stepB)
    {
        digitalWrite(
            MotorBStepPin,
            LOW);
    }


    delayMicroseconds(
        StepPulseWidthUs);


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// LIMIT INPUT
// -------------------------------------------------------------

bool Esp32ArduinoHal::isLimitActive(
    Limit limit) const
{
    int pin = -1;


    switch (limit)
    {
        case Limit::XMin:
            pin = XMinLimitPin;
            break;

        case Limit::XMax:
            pin = XMaxLimitPin;
            break;

        case Limit::YMin:
            pin = YMinLimitPin;
            break;

        case Limit::YMax:
            pin = YMaxLimitPin;
            break;
    }


    if (pin < 0)
    {
        return false;
    }


    /*
    -----------------------------------------------------------
    Actual machine logic:

    OPEN   = LOW
    ACTIVE = HIGH
    -----------------------------------------------------------
    */

    return digitalRead(pin) == HIGH;
}


// -------------------------------------------------------------
// SERVO PULSE
// -------------------------------------------------------------

void Esp32ArduinoHal::servoPulse(
    int angle)
{
    /*
    -----------------------------------------------------------
    Convert angle to pulse width.

    0°   -> 500 us
    180° -> 2500 us
    -----------------------------------------------------------
    */

    const std::uint32_t pulseWidth =
        ServoMinPulseUs +
        (
            (
                static_cast<std::uint32_t>(angle) *
                (
                    ServoMaxPulseUs -
                    ServoMinPulseUs
                )
            ) / 180
        );


    digitalWrite(
        ServoPin,
        HIGH);

    delayMicroseconds(
        pulseWidth);

    digitalWrite(
        ServoPin,
        LOW);

    delayMicroseconds(
        ServoPeriodUs -
        pulseWidth);
}


// -------------------------------------------------------------
// LIFT UP
// -------------------------------------------------------------

Core::Result Esp32ArduinoHal::liftUp()
{
    m_servoAngle = LiftUpAngle;


    /*
    -----------------------------------------------------------
    Send several complete servo frames.

    This gives the MG90S enough time to reach the position.
    -----------------------------------------------------------
    */

    for (int i = 0; i < 25; ++i)
    {
        servoPulse(
            m_servoAngle);
    }


    return Core::Result::Ok;
}


// -------------------------------------------------------------
// LIFT DOWN
// -------------------------------------------------------------

Core::Result Esp32ArduinoHal::liftDown()
{
    m_servoAngle = LiftDownAngle;


    /*
    -----------------------------------------------------------
    Send several complete servo frames.
    -----------------------------------------------------------
    */

    for (int i = 0; i < 25; ++i)
    {
        servoPulse(
            m_servoAngle);
    }


    return Core::Result::Ok;
}


} // namespace LogosRobotics::Hal