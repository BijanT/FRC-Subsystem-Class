#include "AutonStep.h"

AutonStep::AutonStep(Subsystem* subsystem, AutonInstructions instruction)
{
	subsystems.push_back(subsystem);
	instructions.push_back(instruction);
	firstLoop = true;
}

AutonStep::~AutonStep()
{
	subsystems.clear();
	instructions.clear();
}

//Add another thing to do during the autonomous step
void AutonStep::AddSubsystem(Subsystem* subsystem, AutonInstruction instruction)
{
	subsystems.push_back(subsystem);
	instructions.push_back(instruction);
}

bool AutonStep::PerformAuton()
{
	//This variable will be or'ed together with each part of the autonomous step and if it is true, the step is still going on, but if it is false, that means the step is done
	bool performing = false;
	
	//Check if it is the first time going through this step, if it is, set up the autonomous step for all of the subsystems
	if(firstLoop)
	{
		for(int i = 0; i < subsystems.size(); i++) //this is actually a "bad" way to loop through a vector, but I think it is the easiest way to do it in this situation
		{
			subsystems.at(i)->SetUpAuton(instructions.at(i));
		}
		//Change firstLoop to false because we are done setting up this step
		firstLoop = false;
	}
	
	//loop through all of the subsystems so they can do their thang
	for(int i = 0; i < subsystems.size(); i++) //this is actually a "bad" way to loop through a vector, but I think it is the easiest way to do it in this situation
	{
		performing = (performing || (bool)subsystems.at(i)->Auton(instructions.at(i)));
	}
}