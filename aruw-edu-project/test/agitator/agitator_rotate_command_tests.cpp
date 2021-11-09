#include <gmock/gmock.h>

#include "tap/drivers.hpp"

#include "control/agitator/agitator_rotate_command.hpp"
#include "mock/agitator_subsystem_mock.hpp"

using control::agitator::AgitatorRotateCommand;
using namespace testing;

TEST(AgitatorRotateCommand, initialize_sets_desired_angle_when_agitator_calibrated)
{
    tap::Drivers d;
    mock::AgitatorSubsystemMock subMock(&d);
    AgitatorRotateCommand cmd(&subMock, 10.0f);
    EXPECT_CALL(subMock, calibrated).WillOnce(Return(true));
    EXPECT_CALL(subMock, setDesiredAngle(10.0f));
    EXPECT_CALL(subMock, getAngle).WillOnce(Return(0));

    cmd.initialize();
}

TEST(AgitatorRotateCommand, initialize_does_not_set_desired_angle_when_agitator_not_calibrated)
{
    tap::Drivers d;
    mock::AgitatorSubsystemMock subMock(&d);
    AgitatorRotateCommand cmd(&subMock, 10.0f);
    EXPECT_CALL(subMock, calibrated).WillOnce(Return(false));
    EXPECT_CALL(subMock, getAngle).Times(0);

    cmd.initialize();
}

TEST(
    AgitatorRotateCommand,
    isFinished_returns_false_if_desired_and_current_angle_not_within_tolerance)
{
    tap::Drivers d;
    mock::AgitatorSubsystemMock subMock(&d);
    AgitatorRotateCommand cmd(&subMock, 10.0f);
    EXPECT_CALL(subMock, getAngle).WillRepeatedly(Return(10.0f));
    EXPECT_CALL(subMock, getDesiredAngle).WillOnce(Return(0));

    EXPECT_FALSE(cmd.isFinished());
}

TEST(AgitatorRotateCommand, isFinished_returns_true_if_desired_and_current_angle_within_tolerance)
{
    tap::Drivers d;
    mock::AgitatorSubsystemMock subMock(&d);
    AgitatorRotateCommand cmd(&subMock, 10.0f);
    EXPECT_CALL(subMock, getAngle).WillRepeatedly(Return(10.0f));
    EXPECT_CALL(subMock, getDesiredAngle).WillOnce(Return(10.0f));

    EXPECT_TRUE(cmd.isFinished());
}

TEST(AgitatorRotateCommand, end_sets_desired_angle_to_current_angle)
{
    tap::Drivers d;
    mock::AgitatorSubsystemMock subMock(&d);
    AgitatorRotateCommand cmd(&subMock, 10.0f);
    EXPECT_CALL(subMock, getAngle).Times(2).WillRepeatedly(Return(10.0f));
    EXPECT_CALL(subMock, setDesiredAngle(10.0f)).Times(2);

    cmd.end(false);
    cmd.end(true);
}
