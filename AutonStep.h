#ifndef AUTOSTEP_H
#define AUTOSTEP_H

#include "Subsystem.h"
#include <vector>

using namespace std;

//This class will be in charge of keeping track of one step of the autonomous routine
class AutonStep
{
private:
	//We need vectors to hold all of the subsystems and instructions to be used in a step 
	vector<Subsystem*> subsystems;
	vector<AutonInstructions> instructions;
	
	bool firstLoop;//This variable keeps track of if it is the first time we are looping through this step
	
public:
	AutonStep(Subsystem* subsystem, AutonInstructions instructions);//This class will require at least 1 set of subsystems and instructions
	~AutonStep();
	
	//For when the auton routine requires two things to be happening at once
	void AddSubsystem(Subsystem* subsystem, AutonInstructions instructions);
	
	//This function will be the one that actually performs the autonomous step
	//It will return true if it is still performing and false when it is not
	bool PerformAuton();
};

#endif