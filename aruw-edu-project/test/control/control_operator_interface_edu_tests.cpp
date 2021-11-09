#include <gtest/gtest.h>

#include "tap/drivers.hpp"

#include "control/control_operator_interface_edu.hpp"

using namespace control;

TEST(ControlOperatorInterfaceEdu, getChassisLeftTankInput_zero_if_zero_remote_input)
{
    tap::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);

    EXPECT_EQ(0, operatorInterface.getChassisLeftTankInput());
}

TEST(
    ControlOperatorInterfaceEdu,
    getChassisLeftTankInput_positive_if_positive_left_vertical_remote_input)
{
    tap::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);
    ON_CALL(drivers.remote, getChannel(tap::Remote::Channel::LEFT_VERTICAL))
        .WillByDefault([](tap::Remote::Channel) { return 1; });

    EXPECT_EQ(1, operatorInterface.getChassisLeftTankInput());
}

TEST(
    ControlOperatorInterfaceEdu,
    getChassisLeftTankInput_negative_if_negative_left_vertical_remote_input)
{
    tap::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);
    ON_CALL(drivers.remote, getChannel(tap::Remote::Channel::LEFT_VERTICAL))
        .WillByDefault([](tap::Remote::Channel) { return -1; });

    EXPECT_EQ(-1, operatorInterface.getChassisLeftTankInput());
}

TEST(ControlOperatorInterfaceEdu, getChassisRightTankInput_zero_if_zero_remote_input)
{
    tap::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);

    EXPECT_EQ(0, operatorInterface.getChassisLeftTankInput());
}

TEST(
    ControlOperatorInterfaceEdu,
    getChassisRightTankInput_positive_if_positive_right_vertical_remote_input)
{
    tap::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);
    ON_CALL(drivers.remote, getChannel(tap::Remote::Channel::RIGHT_VERTICAL))
        .WillByDefault([](tap::Remote::Channel) { return 1; });

    EXPECT_EQ(1, operatorInterface.getChassisRightTankInput());
}

TEST(
    ControlOperatorInterfaceEdu,
    getChassisRightTankInput_negative_if_negative_right_vertical_remote_input)
{
    tap::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);
    ON_CALL(drivers.remote, getChannel(tap::Remote::Channel::RIGHT_VERTICAL))
        .WillByDefault([](tap::Remote::Channel) { return -1; });

    EXPECT_EQ(-1, operatorInterface.getChassisRightTankInput());
}
