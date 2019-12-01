
#pragma once

enum class Action {invalid=-1, best=0, up=1, down=2, left=3, right=4};					// this is in the class to make it overridable	

typedef double Reward;

struct Location
{
	int x;
	int y;
};

struct State
{
	Location loc;
	bool isTerminal;
	long curEpoch;
	
};

struct SAR
{
	State  s;
	Action a;
	Reward r;
};


struct RewardState 
{

	bool isReward;
	double reward;
	State nextState;

};


struct Policy
{

	State s;
	Action a;

	double sumOfValues;			// current value for policy
	long numberOfComponents;	// the number of values included in the sum

};

struct PolicyBody
{

	double sumOfValues;			// current value for policy
	long numberOfComponents;	// the number of values included in the sum

};

