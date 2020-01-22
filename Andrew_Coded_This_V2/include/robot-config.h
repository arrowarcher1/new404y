using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern controller Controller1;
extern motor intakeRight;
extern motor intakeLeft;
extern motor armMotor;
extern motor trayMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );