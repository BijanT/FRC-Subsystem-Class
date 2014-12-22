#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "RobotDrive.h"
#include "Encoder.h"
#include "Gyro.h"
#include "RobotBase.h"
#include "Subsystem.h"

#define 

class DriveTrain : public Subsystem
{
private:
	RobotDrive* drive;
	Encoder* leftEnco;
	Encoder* rightEnco;
	Gyro* gyro;
	
public:
	//Define the autonomous flags - these have to be powers of 2
	static const int DRIVE = 1; //For when you are driving forward in auto
	static const int TURN = 2; //For when you are turning in auto
	
	//Define the constructors
	DriveTrain(int leftDrivePort, int rightDrivePort, int leftEncoA, int leftEncoB, int rightEncoA, int rightEncoB, Gyro* robotGyro, string name);
	~DriveTrain();
	
	//Driving functions
	void Drive(float left, float right);
	bool GyroTurn(float desiredTurnAngle, float turnSpeed);
	bool GyroDrive(float desiredDriveAngle, float speed, int desiredDistance);
	
	//For setting up the encoders
	void SetDistancePerPulse(double distance);
	
	//Accessor methods
	float getLeftEnco(){return leftEnco->GetDistance()};
	float getRightEnco(){return rightEnco->GetDistance()};
	float getAngle(){return gyro->GetAngle();}
	
	//Autonomous functions
	void SetUpAuton(AutonInstructions instructions);
	int Auton(AutonInstructions instructions());
};

#endif