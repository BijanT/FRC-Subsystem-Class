#include "WPILib.h"
#include <queue>
#include "DriveTrain.h"
#include "AutonStep.h"

//This port numbers aren't real, they are just place holders
#define LEFT_DRIVE_PORT 0
#define RIGHT_DRIVE_PORT 1
#define LEFT_ENCO_A_PORT 0
#define LEFT_ENCO_B_PORT 1
#define RIGHT_ENCO_A_PORT 2
#define RIGHT_ENCO_B_PORT 3

#define GYRO_PORT 0



class RobotDemo : public SimpleRobot
{
DriveTrain* drive;
Gyro* gyro;

public:
	RobotDemo()
	{
		gyro = new Gyro(GYRO_PORT);
		
		drive = new DriveTrain(LEFT_DRIVE_PORT, RIGHT_DRIVE_PORT, LEFT_ENCO_A_PORT, LEFT_ENCO_B_PORT, RIGHT_ENCO_A_PORT, RIGHT_ENCO_B_PORT, gyro, "Drive Train");
	}


	void Autonomous()
	{
		//Create the things needed to add autonomous steps
		queue AutonSteps<AutonStep*> steps;
		AutonStep* step;
		AutonInstructions instr;
		
		//First step: Drive forwards 12 units
		instr.flags = DriveTrain::DRIVE;
		//These are all doubles so the need decimal points
		instr.param1 = 12.0;//Drive distance
		instr.param2 = 0.0;//Turn distance
		instr.param3 = 0.5;//Speed
		step = new AutonStep(drive, instr);
		steps.push(step);
		
		//Second step: Turn 90 degrees
		instr.flags = DriveTrain::TURN;
		instr.param1 = 0.0;//Even though we don't need it, always set it to something
		instr.param2 = 90.0;
		instr.param3 = 0.5;
		step = new AutonStep(drive, instr);
		steps.push(step);
		
		//Third step: Drive forwards 20 units while turning 45 degrees
		instr.flage = DriveTrain::DRIVE;
		instr.param1 = 20.0;
		instr.param2 = 45.0;
		instr.param3 = 0.5;
		step = new AutonStep(drive, instr);
		steps.push(step);
		
		while(IsAutonomous())
		{
			//Check if the queue is empty
			if(!steps.empty())
			{
				//Check if the current step is done
				if(!steps.front()->Auton())
				{
					//If it is done, move on to the next step in the queue
					steps.pop();
				}
			}
		}
	}
	void OperatorControl()
	{	

	}
	void Disabled()
	{
	
	}
	/**
	* Runs during test mode
	*/
	void Test() {
	}
};
START_ROBOT_CLASS(RobotDemo);