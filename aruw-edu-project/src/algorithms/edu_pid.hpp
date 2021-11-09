#ifndef EDU_PID_HPP_
#define EDU_PID_HPP_

#include <cstdint>

namespace algorithms
{
/**
 * A base PID controller that uses current error to calculate some desired output.
 * To use, declare an EduPid class then in a loop, call the runControllerDerivativeError
 * function over and over, feeding in the current error between the setpoint and actual
 * value and the time since the last call to runControllerDerivativeError.
 */
class EduPid
{
public:
    EduPid(float kp, float ki, float kd, float maxICumulative, float maxOutput)
        : kp(kp),
          ki(ki),
          kd(kd),
          maxICumulative(maxICumulative),
          maxOutput(maxOutput)
    {
    }

    /**
     * Updates the PID controller. Takes one step of the following form:
     *
     * \f$ u(t) = K_p e(t) + K_i \sum_{x=0}^t e(x) \Delta_t + K_d \Delta_t (e(t)-e(t-1) \f$
     *
     * Where \f$u(t)\f$ is the output, \f$K_p, K_i, K_d\f$ are the proportionality constants,
     * and \f$\Delta_t\f$ is the time step between the previous and current iteration.
     *
     * @param[in] error the error between the desired and actual value.
     * @param[in] dt the time difference between the previous and current iteration.
     * @see tap::arch::clock for measuring time.
     * @return the new output calculated by the PID controller.
     */
    float runControllerDerivateError(float error, float dt);

    /**
     * @return the last output calculated during `runControllerDerivativeError`.
     */
    float getOutput() const { return output; }

    /**
     * Zeros the p, i, d, and output terms.
     */
    void reset();

private:
    // Gains and constants, to be set by the user.
    const float kp;
    const float ki;
    const float kd;
    const float maxICumulative;
    const float maxOutput;

    // While these could be local, debugging pid is much easier if they are not.
    float currErrorP = 0.0f;
    float currErrorI = 0.0f;
    float currErrorD = 0.0f;
    float output = 0.0f;
    float prevError = 0.0f;
};  // class EduPid
}  // namespace algorithms

#endif  // EDU_PID_HPP_
