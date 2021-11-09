#include "control/control_operator_interface_edu.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/drivers.hpp"
#include "tap/drivers_singleton.hpp"

namespace control
{
float ControlOperatorInterfaceEdu::getChassisLeftTankInput()
{
    return drivers->remote.getChannel(tap::Remote::Channel::LEFT_VERTICAL);
}

float ControlOperatorInterfaceEdu::getChassisRightTankInput()
{
    return drivers->remote.getChannel(tap::Remote::Channel::RIGHT_VERTICAL);
}
}  // namespace control
