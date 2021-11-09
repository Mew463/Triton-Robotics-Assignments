#include <gtest/gtest.h>

#include "algorithms/edu_pid.hpp"

using algorithms::EduPid;

static constexpr float KP = 10;
static constexpr float KI = 10;
static constexpr float KD = 10;
static constexpr float MAX_I = 100;
static constexpr float MAX_OUT = 1000;

TEST(EduPid, zero_error_zero_output)
{
    EduPid pid(KP, KI, KD, MAX_I, MAX_OUT);

    EXPECT_EQ(0, pid.runControllerDerivateError(0, 1));
}

TEST(EduPid, zero_dt_no_output)
{
    EduPid pid(KP, KI, KD, MAX_I, MAX_OUT);

    EXPECT_EQ(0, pid.runControllerDerivateError(1, 0));
}

TEST(EduPid, zero_max_out_zero_output)
{
    EduPid pid(KP, KI, KD, MAX_I, 0);

    EXPECT_EQ(0, pid.runControllerDerivateError(100, 100));
}

TEST(EduPid, error_proportional_gain_only_proportional_to_gain)
{
    EduPid pid(KP, 0, 0, 0, MAX_OUT);

    EXPECT_EQ(KP, pid.runControllerDerivateError(1, 1));
    EXPECT_EQ(10 * KP, pid.runControllerDerivateError(10, 1));
    EXPECT_EQ(-KP, pid.runControllerDerivateError(-1, 1));
    EXPECT_EQ(-10 * KP, pid.runControllerDerivateError(-10, 1));
}

TEST(EduPid, error_integral_gain_only_sums_error_over_time)
{
    EduPid pid(0, KI, 0, MAX_I, MAX_OUT);

    EXPECT_EQ(2 * KI, pid.runControllerDerivateError(1, 2));
    EXPECT_EQ(4 * KI, pid.runControllerDerivateError(1, 2));
    EXPECT_EQ(6 * KI, pid.runControllerDerivateError(1, 2));
    EXPECT_EQ(4 * KI, pid.runControllerDerivateError(-1, 2));
    EXPECT_EQ(2 * KI, pid.runControllerDerivateError(-1, 2));
    EXPECT_EQ(0, pid.runControllerDerivateError(-1, 2));
    EXPECT_EQ(-2 * KI, pid.runControllerDerivateError(-1, 2));
    EXPECT_EQ(-4 * KI, pid.runControllerDerivateError(-1, 2));
    EXPECT_EQ(-6 * KI, pid.runControllerDerivateError(-1, 2));
}

TEST(EduPid, integral_limited_by_max_error_integral)
{
    EduPid pid(0, KI, 0, MAX_I, MAX_OUT);

    EXPECT_EQ(MAX_I, pid.runControllerDerivateError(MAX_I, 2.0f));
}

TEST(EduPid, zero_i_accumulative_zero_integral_output)
{
    EduPid pid(0, KI, 0, 0, MAX_OUT);

    EXPECT_EQ(0, pid.runControllerDerivateError(100, 100));
}

TEST(EduPid, error_derivative_gain_only_proportional_to_step_derivative_of_error)
{
    EduPid pid(0, 0, KD, MAX_I, MAX_OUT);

    EXPECT_EQ(KD / 2.0f, pid.runControllerDerivateError(1, 2));
    EXPECT_EQ(10 * KD / 2.0f - KD / 2.0f, pid.runControllerDerivateError(10, 2));
}

TEST(EduPid, max_error_limited_by_max_output)
{
    EduPid pid(KP, KI, KD, MAX_I, MAX_OUT);

    EXPECT_EQ(MAX_OUT, pid.runControllerDerivateError(MAX_OUT, 2));
}
