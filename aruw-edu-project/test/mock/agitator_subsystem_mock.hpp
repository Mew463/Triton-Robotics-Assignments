#ifndef AGITATOR_SUBSYSTEM_MOCK_HPP_
#define AGITATOR_SUBSYSTEM_MOCK_HPP_

#include <gmock/gmock.h>

#include "control/agitator/agitator_subsystem.hpp"

namespace mock
{
class AgitatorSubsystemMock : public control::agitator::AgitatorSubsystem
{
public:
    AgitatorSubsystemMock(tap::Drivers *drivers) : control::agitator::AgitatorSubsystem(drivers) {}
    MOCK_METHOD(void, refresh, (), (override));
    MOCK_METHOD(void, setDesiredAngle, (float newAngle), (override));
    MOCK_METHOD(float, getAngle, (), (const override));
    MOCK_METHOD(bool, calibrated, (), (const override));
    MOCK_METHOD(float, getDesiredAngle, (), (const override));
    MOCK_METHOD(const tap::motor::DjiMotor &, getMotor, (), (const override));
};  // class AgitatorSubsystemMock
}  // namespace mock

#endif  // AGITATOR_SUBSYSTEM_MOCK_HPP_
