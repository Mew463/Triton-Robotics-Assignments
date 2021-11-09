#ifndef AGITATOR_SUBSYSTEM_HPP_
#define AGITATOR_SUBSYSTEM_HPP_

#include "tap/communication/can/can.hpp"
#include "tap/control/subsystem.hpp"
#include "tap/motor/dji_motor.hpp"
#include "tap/util_macros.hpp"

#include "algorithms/edu_pid.hpp"

namespace control
{
namespace agitator
{
class AgitatorSubsystem : public tap::control::Subsystem
{
public:
    AgitatorSubsystem(tap::Drivers *drivers)
        : tap::control::Subsystem(drivers),
          pid(K_P, K_I, K_D, PID_MAX_I, PID_MAX_OUT),
          motor(drivers, tap::motor::MOTOR7, tap::can::CanBus::CAN_BUS1, false, "agitator")
    {
    }

    virtual ~AgitatorSubsystem() = default;

    void refresh() override;

    mockable void setDesiredAngle(float newAngle);

    mockable float getAngle() const;

    mockable bool calibrated() const { return isCalibrated; }

    mockable float getDesiredAngle() const { return desiredAngle; }

private:
    static constexpr float K_P = 170000.0f;
    static constexpr float K_I = 0.0f;
    static constexpr float K_D = 80.0f;
    static constexpr float PID_MAX_I = 0.0f;
    static constexpr float PID_MAX_OUT = 16000.0f;
    static constexpr float GEAR_RATIO = 19.0f;

    float desiredAngle = 0.0f;
    float actualAngle = 0.0f;
    bool isCalibrated = false;
    float agitatorCalibratedZeroAngle = 0.0f;
    int64_t prevTime = 0;
    int64_t prevDt = 0;  // todo this is my implementation, remove.

    algorithms::EduPid pid;

    tap::motor::DjiMotor motor;

    bool calibrateHere();

    float getUncalibratedAngle() const;
};  // AgitatorSubsystem
}  // namespace agitator
}  // namespace control

#endif  // AGITATOR_SUBSYSTEM_HPP_
