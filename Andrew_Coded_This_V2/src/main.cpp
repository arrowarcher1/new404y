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

  bool blueSide;
  bool redSide;
  bool protectedSide;
  bool unProtectedSide;

void pre_auton(void) {
  vexcodeInit();

  //// Controller Based Auton Selection, Changes variable based on input
    Controller1.Screen.setCursor(1, 2);
    Controller1.Screen.print("BLUE SIDE");
    Controller1.Screen.setCursor(1, 10);
    Controller1.Screen.print("RED SIDE");
    Controller1.Screen.setCursor(4, 2);
    Controller1.Screen.print("Protected");
    Controller1.Screen.setCursor(4, 10);
    Controller1.Screen.print("unProtected");

  if(Controller1.ButtonA.pressing()){
    blueSide = true;
    redSide = false;
    Controller1.Screen.clearLine(2);
    Controller1.Screen.setCursor(2, 2);
    Controller1.Screen.print(blueSide);
    Controller1.Screen.setCursor(2, 10);
    Controller1.Screen.print(redSide);    
    Controller1.rumble(rumbleShort); 
  }
  if(Controller1.ButtonB.pressing()){
    redSide = true;
    blueSide = false;
    Controller1.Screen.clearLine(2);
    Controller1.Screen.setCursor(2, 2);
    Controller1.Screen.print(blueSide);
    Controller1.Screen.setCursor(2, 10);
    Controller1.Screen.print(redSide);  
    Controller1.rumble(rumbleShort); 

  }
  if(Controller1.ButtonLeft.pressing()){
    protectedSide = true;
    unProtectedSide = false;
    Controller1.Screen.clearLine(4);
    Controller1.Screen.setCursor(4, 2);
    Controller1.Screen.print(protectedSide);
    Controller1.Screen.setCursor(4, 10);
    Controller1.Screen.print(unProtectedSide);
    Controller1.rumble(rumbleShort); 

  }
  if(Controller1.ButtonRight.pressing()){
    unProtectedSide = true;
    protectedSide = false;
    Controller1.Screen.clearLine(4);
    Controller1.Screen.setCursor(4, 2);
    Controller1.Screen.print(protectedSide);
    Controller1.Screen.setCursor(4, 10);
    Controller1.Screen.print(unProtectedSide);
    Controller1.rumble(rumbleShort); 
  }
}

//////////////Variables And Functions////////////////////

bool intakeCur = true;
bool scoreCur = false;
int errorTray;  
int trayVoltage = 0;
double kpTray = -.4175;
int targetTray = -450;
int positionTray;

void intake(){
  intakeLeft.spin(forward, -12, volt);
  intakeRight.spin(forward, -12, volt);
}
void outtake(){
  intakeLeft.spin(forward, 12, volt);
  intakeRight.spin(forward, 12, volt);
}
void intakeCurOn(){
  intakeLeft.spin(forward, -1, volt);
  intakeRight.spin(forward, -1, volt);
}
void intakeCurOff(){
  intakeLeft.spin(forward, 0, volt);
  intakeRight.spin(forward, 0, volt); 
}
void trayCalculations(){
  positionTray = trayMotor.position(degrees);
  errorTray = targetTray + positionTray;
  trayVoltage = (errorTray * kpTray);
}
void resetTrayEncoder(){
  trayMotor.resetPosition();
}
void trayUp(){
  scoreCur = true;
  trayMotor.spin(forward, trayVoltage, volt);
}
void trayDown(){
  scoreCur = false;
  trayMotor.spin(forward, -12, volt);
}
void trayDownCur(){
  trayMotor.spin(forward, -2, volt);
  scoreCur = false;
}
void armUp(){
  armMotor.spin(forward, 12, volt);
  intakeCur = false;
}
void armDown(){
  armMotor.spin(forward, -12, volt);
  intakeCur = true;
}
void armCurUp(){
  armMotor.spin(forward, 1, volt);
}
void armCurDown(){
  armMotor.spin(forward, -2, volt);
}


//////////////END OF Variables And Functions/////////////////////


void autonomous(void) {
if(blueSide == true && protectedSide == true){
  //Run Blue Protected Side Code
}
if(blueSide == true && unProtectedSide == true){
  //Run Blue Unprotected Side Code
}
if(redSide == true && protectedSide == true){
  //Run Red Protected Side Code

  // Still need to code in tray deployment, but not sure how were going to fold up our tray yet //
  intake();
  Drivetrain.setDriveVelocity(90, pct);
  Drivetrain.driveFor(forward, 11.5, inches);
  Drivetrain.turnFor(-6, degrees);
  Drivetrain.driveFor(forward, 24, inches);
  Drivetrain.turnFor(-.5, degrees);
  Drivetrain.driveFor(forward, 10.2, inches);
  Drivetrain.turnFor(-89.1, degrees);
  Drivetrain.driveFor(forward, 22.16, inches);
  Drivetrain.turnFor(-90.8, degrees);
  Drivetrain.driveFor(forward, 39.5, inches);
  intakeCurOff(); // turns off intake, using a function from driver control
  Drivetrain.turnFor(-45, degrees);
  Drivetrain.driveFor(forward, 15.7, inches);
  intakeLeft.spin(forward, 1, volt);
  intakeRight.spin(forward, 1, volt);
  trayMotor.setVelocity(70, pct);
  trayMotor.spinFor(forward, 90, degrees);
  wait(4, seconds);
  Drivetrain.driveFor(reverse, 5, inches);

}
if(redSide == true && unProtectedSide == true){
  //Run Red UnProtected Side Code

  // Still need to code in tray deployment, but not sure how were going to fold up our tray yet //
  intake();
  Drivetrain.setDriveVelocity(90, pct);
  Drivetrain.driveFor(forward, 37.2, inches);
  Drivetrain.turnFor(-42.9, degrees);
  Drivetrain.driveFor(forward, 15.72, inches);
  intakeCurOff(); // turns off intake, using a function from driver control
  Drivetrain.driveFor(reverse, 15.72, inches);
  Drivetrain.turnFor(-155.2, degrees);
  Drivetrain.driveFor(forward, 24, inches);
  Drivetrain.setDriveVelocity(60, pct);
  Drivetrain.driveFor(forward, 24, inches);
  intakeLeft.spin(forward, 1, volt);
  intakeRight.spin(forward, 1, volt);
  trayMotor.setVelocity(70, pct);
  trayMotor.spinFor(forward, 90, degrees);  
  wait(4, seconds);
  Drivetrain.driveFor(reverse, 5, inches);

}

}




void usercontrol(void) {
while (1) {
/////////////////INTAKE CONTROLS//////////////////
if(Controller1.ButtonR2.pressing()){
  intake();
}else if(Controller1.ButtonR1.pressing()){
  outtake();
}else if(intakeCur == true){
  intakeCurOn();  
}else if(intakeCur == false){
  intakeCurOff(); 
}else{
  intakeCurOn();
}

//////Run Tray Calculations///////////
trayCalculations();

////////Manual Tray Reset Button///////
if(Controller1.ButtonDown.pressing()){
resetTrayEncoder();
}

///////////Tray Controls////////////
if(Controller1.ButtonL1.pressing()){
  trayUp();
}else if(Controller1.ButtonL2.pressing()){
  trayDown();
}else{
  trayDownCur();
}

///////////Arm Controls///////////////
if(Controller1.ButtonX.pressing()){
armUp();
}else if (Controller1.ButtonB.pressing()){
armDown();
}else{
  if(armMotor.position(degrees) > 10){
    armCurUp();
  }else{
    armCurDown();
  }}



////////////NOTE TO SELF DONT DELETE THESE//////////
    wait(20, msec);
  }
}
////////////NOTE TO SELF DONT DELETE THESE//////////



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
