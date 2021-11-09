#ifndef CHASSIS_SUBSYSTEM_MOCK_HPP_
#define CHASSIS_SUBSYSTEM_MOCK_HPP_

#include <gmock/gmock.h>

#include "control/chassis/chassis_subsystem.hpp"

namespace control
{
namespace chassis
{
class ChassisSubsystemMock : public ChassisSubsystem
{
public:
    ChassisSubsystemMock(tap::Drivers *drivers) : ChassisSubsystem(drivers) {}
    MOCK_METHOD(
        void,
        setDesiredOutput,
        (int16_t leftSideOutput, int16_t rightSideOutput),
        (override));
};  // class ChassisSubsystemMock
}  // namespace chassis
}  // namespace control

#endif  // CHASSIS_SUBSYSTEM_MOCK_HPP_
