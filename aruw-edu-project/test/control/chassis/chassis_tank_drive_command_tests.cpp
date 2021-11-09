#include <gtest/gtest.h>

#include "tap/drivers.hpp"

#include "control/chassis/chassis_tank_drive_command.hpp"
#include "mock/chassis_subsystem_mock.hpp"
#include "mock/control_operator_interface_edu_mock.hpp"

using namespace control::chassis;
using namespace testing;
using control::ControlOperatorInterfaceEduMock;

constexpr float DEFAULT_DESIRED_OUTPUT = 1;

TEST(ChassisTankDriveCommand, execute_zero_remote_input_zero_desired_output)
{
    tap::Drivers drivers;
    ChassisSubsystemMock cs(&drivers);
    ChassisTankDriveCommand ctd(&cs, &drivers);
    ON_CALL(drivers.controlOperatorInterfaceEdu, getChassisLeftTankInput).WillByDefault(Return(0));
    ON_CALL(drivers.controlOperatorInterfaceEdu, getChassisRightTankInput).WillByDefault(Return(0));
    EXPECT_CALL(drivers.controlOperatorInterfaceEdu, getChassisLeftTankInput);
    EXPECT_CALL(drivers.controlOperatorInterfaceEdu, getChassisRightTankInput);
    EXPECT_CALL(cs, setDesiredOutput(0, 0));

    ctd.execute();
}

TEST(ChassisTankDriveCommand, execute_positive_remote_input_positive_desired_output)
{
    tap::Drivers drivers;
    ChassisSubsystemMock cs(&drivers);
    ChassisTankDriveCommand ctd(&cs, &drivers);
    ON_CALL(drivers.controlOperatorInterfaceEdu, getChassisLeftTankInput)
        .WillByDefault(Return(DEFAULT_DESIRED_OUTPUT));
    ON_CALL(drivers.controlOperatorInterfaceEdu, getChassisRightTankInput)
        .WillByDefault(Return(DEFAULT_DESIRED_OUTPUT));
    EXPECT_CALL(drivers.controlOperatorInterfaceEdu, getChassisLeftTankInput);
    EXPECT_CALL(drivers.controlOperatorInterfaceEdu, getChassisRightTankInput);
    EXPECT_CALL(
        cs,
        setDesiredOutput(
            DEFAULT_DESIRED_OUTPUT * ChassisSubsystem::MAX_CURRENT_OUTPUT,
            DEFAULT_DESIRED_OUTPUT * ChassisSubsystem::MAX_CURRENT_OUTPUT));

    ctd.execute();
}

TEST(ChassisTankDriveCommand, execute_negative_remote_input_positive_desired_output)
{
    tap::Drivers drivers;
    ChassisSubsystemMock cs(&drivers);
    ChassisTankDriveCommand ctd(&cs, &drivers);
    ON_CALL(drivers.controlOperatorInterfaceEdu, getChassisLeftTankInput)
        .WillByDefault(Return(-DEFAULT_DESIRED_OUTPUT));
    ON_CALL(drivers.controlOperatorInterfaceEdu, getChassisRightTankInput)
        .WillByDefault(Return(-DEFAULT_DESIRED_OUTPUT));
    EXPECT_CALL(drivers.controlOperatorInterfaceEdu, getChassisLeftTankInput);
    EXPECT_CALL(drivers.controlOperatorInterfaceEdu, getChassisRightTankInput);
    EXPECT_CALL(
        cs,
        setDesiredOutput(
            -DEFAULT_DESIRED_OUTPUT * ChassisSubsystem::MAX_CURRENT_OUTPUT,
            -DEFAULT_DESIRED_OUTPUT * ChassisSubsystem::MAX_CURRENT_OUTPUT));

    ctd.execute();
}
