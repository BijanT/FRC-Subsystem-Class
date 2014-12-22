#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include <string>

using namespace std;

struct AutonInstructions
{
	int flags;
	double param1;
	double param2;
	double param3;
}

class Subsystem
{
private:
	string subsystemName;
public:
	Subsystem(string name);
	~Subsystem();

	string getName(){return subsystemName;}
	virtual void SetUpAuton(AutonInstructions instructions)=0;//Having an =0 at the end of the function declaration makes a function a pure virtual function
	virtual int Auton(AutonInstructions instructions)=0;
};

#endif