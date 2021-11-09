#ifndef CONTROL_OPERATOR_INTERFACE_EDU_MOCK_HPP_
#define CONTROL_OPERATOR_INTERFACE_EDU_MOCK_HPP_

#include <gmock/gmock.h>

#include "control/control_operator_interface_edu.hpp"

namespace control
{
class ControlOperatorInterfaceEduMock : public ControlOperatorInterfaceEdu
{
public:
    ControlOperatorInterfaceEduMock(tap::Drivers *drivers) : ControlOperatorInterfaceEdu(drivers) {}
    MOCK_METHOD(float, getChassisLeftTankInput, (), (override));
    MOCK_METHOD(float, getChassisRightTankInput, (), (override));
};
}  // namespace control

#endif  // CONTROL_OPERATOR_INTERFACE_EDU_MOCK_HPP_
