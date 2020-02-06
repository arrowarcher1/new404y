/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Andrew Van Ostrand                                        */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Code 404Y                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2, 3, 5      
// Controller1          controller                    
// intakeRight          motor         4               
// intakeLeft           motor         9               
// armMotor             motor         10              
// trayMotor            motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global insta nces of motors and other devices here


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


void autonomous(void) {

}

void usercontrol(void) {

bool intakeCur = true;
bool scoreCur = false;
int errorTray;
int trayVoltage = 0;
double kpTray = -.4175;
int targetTray = -450;
int positionTray;

while (1) {
/////////////////INTAKE CONTROLS//////////////////
if(Controller1.ButtonR2.pressing()){
  //Intake
  intakeLeft.spin(forward, -127, volt);
  intakeRight.spin(forward, -127, volt);
}else if (Controller1.ButtonR1.pressing()){
  //outTake
  intakeLeft.spin(forward, 127, volt);
  intakeRight.spin(forward, 127, volt);
}else if(intakeCur == true){
  intakeLeft.spin(forward, -10, volt);
  intakeRight.spin(forward, -10, volt);  
}else if(intakeCur == false){
  intakeLeft.spin(forward, 0, volt);
  intakeRight.spin(forward, 0, volt);  
}else{
  intakeLeft.spin(forward, -10, volt);
  intakeRight.spin(forward, -10, volt);  
}

//////////////////Tray Encoder Stuff////////////////
positionTray = trayMotor.position(degrees);
errorTray = targetTray + positionTray;
trayVoltage = (errorTray * kpTray);


if(Controller1.ButtonDown.pressing()){
  trayMotor.resetPosition();
}

///////////Tray Controls////////////

if(Controller1.ButtonL1.pressing()){
  scoreCur = true;
  trayMotor.spin(forward, trayVoltage, volt);
}else if(Controller1.ButtonL2.pressing()){
  scoreCur = false;
  trayMotor.spin(forward, -127, volt);
}else{
  trayMotor.spin(forward, -5, volt);
  scoreCur = false;
}

///////////Arm Controls///////////////

if(Controller1.ButtonX.pressing()){

}else if (Controller1.ButtonB.pressing()){

}else{
  if(armMotor.position(degrees) > 10){
    armMotor.spin(forward, 10, volt);
  }else{
    armMotor.spin(forward, -5, volt);
  }}



////////////NOTE TO SELF DONT DELETE THESE//////////
    wait(20, msec);
  }
}
////////////NOTE TO SELF DONT DELETE THESE//////////



//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
