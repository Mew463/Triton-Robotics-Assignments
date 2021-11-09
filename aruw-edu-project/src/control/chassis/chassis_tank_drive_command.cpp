#include "chassis_tank_drive_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/drivers.hpp"
#include "tap/errors/create_errors.hpp"

#include "control/control_operator_interface_edu.hpp"

using namespace tap::control;

namespace control
{
namespace chassis
{
ChassisTankDriveCommand::ChassisTankDriveCommand(
    ChassisSubsystem *const chassis,
    tap::Drivers *drivers)
    : chassis(chassis),
      drivers(drivers)
{
    if (chassis == nullptr)
    {
        return;
    }
    addSubsystemRequirement(chassis);
}

void ChassisTankDriveCommand::initialize() {}

void ChassisTankDriveCommand::execute()
{
    chassis->setDesiredOutput(ControlOperatorInterfaceEdu::getChassisLeftTankInput() * ChassisSubsystem::MAX_CURRENT_OUTPUT, ControlOperatorInterfaceEdu::getChassisRightTankInput()* ChassisSubsystem::MAX_CURRENT_OUTPUT);
    /// \todo
}

void ChassisTankDriveCommand::end(bool) { chassis->setDesiredOutput(0, 0); }

bool ChassisTankDriveCommand::isFinished() const { return false; }

}  // namespace chassis

}  // namespace control
