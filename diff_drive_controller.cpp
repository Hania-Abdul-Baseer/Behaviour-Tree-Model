#include <webots/Robot.hpp>
// For defining motors and getMotor()
#include <webots/Motor.hpp> 
// For creating distance sensor objects
#include <webots/DistanceSensor.hpp>

// Defining a new continous time step of 64 mili-seconds
#define TIME_STEP 64

// Defining the speed of the motor as the max speed which is 6.28
#define MAX_SPEED 6.28

// All the webots classes are defined in the "webots" namespace
using namespace webots;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();

  // Defining the motors
  Motor *leftMotor = robot->getMotor("motor_1");
  Motor *rightMotor = robot->getMotor("motor_2");
  
  // Motors can be driven using either position or velocity in webots
  // I will be giving my robot velocity to drive the motors
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0);
  
  // Distance Sensor
  DistanceSensor *ds_left = robot->getDistanceSensor("ds_left");
  DistanceSensor *ds_right = robot->getDistanceSensor("ds_right");
  
  // Enabling sensor using time step
  ds_left->enable(TIME_STEP);
  ds_right->enable(TIME_STEP);
  
  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(TIME_STEP) != -1) {
    
    // Read the sensors:
    double ds_left_val = ds_left->getValue();
    double ds_right_val = ds_right->getValue();

    std::cout<<"Distance Sensor left: "<<ds_left_val;
    std::cout<<"Distance Sensor right: "<<ds_right_val;

    // Setting the velocity of the motors to a certain speed it can 
    // move during the simulation
    // To make it in a different pattern then the left and right 
    // motors can have different speed
    leftMotor->setVelocity(0.5*MAX_SPEED);
    rightMotor->setVelocity(MAX_SPEED);
  };

  delete robot;
  return 0;
}
