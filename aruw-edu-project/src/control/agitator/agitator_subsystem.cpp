#include "agitator_subsystem.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/architecture/clock.hpp"

namespace control
{
namespace agitator
{
void AgitatorSubsystem::refresh()
{
    if (isCalibrated)
    {
        actualAngle = getAngle();
        /// \todo run pid
    }
    else
    {
        calibrateHere();
    }
}

bool AgitatorSubsystem::calibrateHere()
{
    if (!motor.isMotorOnline())
    {
        return false;
    }
    agitatorCalibratedZeroAngle = getUncalibratedAngle();
    isCalibrated = true;
    return true;
}

float AgitatorSubsystem::getAngle() const
{
    if (!isCalibrated)
    {
        return 0.0f;
    }
    return getUncalibratedAngle() - agitatorCalibratedZeroAngle;
}

float AgitatorSubsystem::getUncalibratedAngle() const
{
    // position is equal to the following equation:
    // position = 2 * PI / encoder resolution * unwrapped encoder value / gear ratio
    return (2.0f * M_PI / static_cast<float>(tap::motor::DjiMotor::ENC_RESOLUTION)) *
           motor.getEncoderUnwrapped() / GEAR_RATIO;
}

void AgitatorSubsystem::setDesiredAngle(float newAngle) { desiredAngle = newAngle; }

}  // namespace agitator

}  // namespace control