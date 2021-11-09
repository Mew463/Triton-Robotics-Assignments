#include "tap/control/command_mapper.hpp"
#include "tap/control/hold_repeat_command_mapping.hpp"
#include "tap/drivers_singleton.hpp"

#include "control/agitator/agitator_rotate_command.hpp"
#include "control/agitator/agitator_subsystem.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/chassis_tank_drive_command.hpp"

using tap::Remote;
using tap::control::CommandMapper;
using namespace tap::control;

/*
 * NOTE: We are using the DoNotUse_getDrivers() function here
 *      because this file defines all subsystems and command
 *      and thus we must pass in the single statically allocated
 *      Drivers class to all of these objects.
 */
static tap::driversFunc drivers = tap::DoNotUse_getDrivers;

namespace control
{
ControlOperatorInterfaceEdu controlOperatorInterfaceEdu(drivers());

/* define subsystems --------------------------------------------------------*/
chassis::ChassisSubsystem theChassis(drivers());
control::agitator::AgitatorSubsystem theAgitator(drivers());

/* define commands ----------------------------------------------------------*/
chassis::ChassisTankDriveCommand tankDrive(&theChassis, drivers());
control::agitator::AgitatorRotateCommand rotateCommand(&theAgitator, M_PI / 6);

/* define command mappings --------------------------------------------------*/
tap::control::HoldRepeatCommandMapping rightSwitchUp(
    drivers(),
    {&rotateCommand},
    RemoteMapState(Remote::Switch::RIGHT_SWITCH, Remote::SwitchState::UP));

/* register subsystems here -------------------------------------------------*/
void registerSoldierSubsystems(tap::Drivers *drivers)
{
    drivers->commandScheduler.registerSubsystem(&theChassis);
    drivers->commandScheduler.registerSubsystem(&theAgitator);
}

/* initialize subsystems ----------------------------------------------------*/
void initializeSubsystems() { theChassis.initialize(); }

/* set any default commands to subsystems here ------------------------------*/
void setDefaultSoldierCommands(tap::Drivers *) { theChassis.setDefaultCommand(&tankDrive); }

/* add any starting commands to the scheduler here --------------------------*/
void startSoldierCommands(tap::Drivers *) {}

/* register io mappings here ------------------------------------------------*/
void registerSoldierIoMappings(tap::Drivers *drivers)
{
    drivers->commandMapper.addMap(&rightSwitchUp);
}

void initSubsystemCommands(tap::Drivers *drivers)
{
    initializeSubsystems();
    registerSoldierSubsystems(drivers);
    setDefaultSoldierCommands(drivers);
    startSoldierCommands(drivers);
    registerSoldierIoMappings(drivers);
}

}  // namespace control
