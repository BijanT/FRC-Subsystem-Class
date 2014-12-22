#include "DriveTrain.h"

DriveTrain::DriveTrain(int leftDrivePort, int rightDrivePort, int leftEncoA, int leftEncoB, int rightEncoA, int rightEncoB, Gyro* robotGyro, string name) :
	Subsystem(name)
{
	//Initialize the classes
	drive = new RobotDrive(leftDrivePort, rightDrivePort);
	leftEnco = new Encoder(leftEncoA, leftEncoB);
	rightEnco = new Encoder(rightEncoA, rightEncoB);
	gyro = robotGyro;
}

DriveTrain::~DriveTrain()
{
	delete drive;
	delete leftEnco;
	delete rightEnco;
	delete gyro;
}

void DriveTrain::Drive(float left, float right)
{
	drive->TankDrive(left, right);
}

bool DriveTrain::GyroTurn(float desiredTurnAngle, float turnSpeed)
{
	bool turning = true;
	float myAngle = gyro->getAngle();
	//normalizes angle from gyro to [-180,180) with zero as straight ahead
	while(myAngle >= 180)
	{
		GetWatchdog().Feed();
		myAngle = myAngle - 360;
	}
	while(myAngle < -180)
	{
		GetWatchdog().Feed();
		myAngle = myAngle + 360;
	}
	if(myAngle < (desiredTurnAngle - 2))// if robot is too far left, turn right a bit
	{
		myRobot->Drive(turnSpeed, -turnSpeed); //(right,left)
	}
	if(myAngle > (desiredTurnAngle + 2))// if robot is too far right, turn left a bit
	{
		myRobot->Drive(-turnSpeed, turnSpeed); //(right,left)
	}
	else
	{
		myRobot->Drive(0, 0);
		turning = false;
	}
	return turning;
}

bool GyroDrive(float desiredDriveAngle, float speed, int desiredDistance)
{
	bool driving = true;
	double encoderInchesTraveled = fabs(leftEnco->GetDistance());//absolute value distance
	float myAngle = gyro->GetAngle();
	//normalizes angle from gyro to [-180,180) with zero as straight ahead
	while(myAngle >= 180)
	{
		GetWatchdog().Feed();
		myAngle = myAngle - 360;
	}
	while(myAngle < -180)
	{
		GetWatchdog().Feed();
		myAngle = myAngle + 360;
	}
	float my_speed = 0.0;
	float turn = 0.0;
	if(speed > 0)
		//30.0 is the number you have to change to adjust properly
		turn = -((myAngle + desiredDriveAngle) / 30.0); //proportionally adjust turn. As the robot gets more off 0, the greater the turn will be
	else
		turn = (myAngle + desiredDriveAngle) / 30.0; //proportionally adjust turn. As the robot gets more off 0, the greater the turn will be
	if (encoderInchesTraveled < desiredDistance)
		my_speed = speed;
	else
	{
		my_speed = 0.0;
		driving = false;
	}
	drive->Drive(my_speed, turn);
	return driving;
}

void DriveTrain::SetDistancePerPulse(double distance)
{
	leftEnco->SetDistancePerPulse(distance);
	rightEnco->SetDistanceperPulse(distance);
}

void DriveTrain::SetUpAuton(AutonInstructions instructions)
{
	//Reset the encoders
	leftEnco->Reset();
	rightEnco->Reset();
}

//The autonomous routine
//flags: tells the robot to either drive or turn
//param1: the distance to drive if driving 
//param2: the distance to turn
//param3: speed
//It will return 0 if it is done or 1 if it is still turning/driving
int DriveTrain::Auton(AutonInstructions instructions)
{
	float distance = instructions.param1;
	float turnAngle = instructions.param2;
	float speed = instructions.param3;
	
	if((instructions.flags & DRIVE) == DRIVE)
	{
		return (int)GyroDrive(turnAngle, speed, distance);
	}
	else if((instructions.flags & TURN) == DRIVE)
	{
		return (int)GyroTurn(turnAngle, speed);
	}
	else
	{
		//there should be no other options than drive or turn, so if the flags didn't have one of them, do nothing and just return 0
		return 0;
	}
}