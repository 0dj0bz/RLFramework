// EnvironmentManager.hpp

#pragma once

const int MIN_WIDTH = 0;
const int MAX_WIDTH = 40;
const int MIN_HEIGHT = 0;
const int MAX_HEIGHT = 40;

Location goal = {.x=15, .y=2};


class EnvironmentManager
{
	
	public:
		EnvironmentManager();
		EnvironmentManager(boost::uuids::uuid environmentId);
		EnvironmentManager(std::string environmentId);			

		~EnvironmentManager();

		boost::uuids::uuid environmentId;

		RewardState submitAction(State s, Action a);
		State getInitialState();

	private:
		int loadMap(boost::uuids::uuid environmentId);
		int saveMap(boost::uuids::uuid envrionmentId);
		double scoreAction(State s, Action a);
};

// this version of the constructor generates a new environment,
// creates an empty map, and continues on.
EnvironmentManager::EnvironmentManager()
{

	this->environmentId = boost::uuids::random_generator()();

	loadMap(this->environmentId);
}


// this version of the constructor takes a UID
// of a known Environment and uses that to load the environment map
// if it exists.  If it doesn't exist, it creates an empty map for the
// environment and continues on.
EnvironmentManager::EnvironmentManager(boost::uuids::uuid environmentId)
{

	this->environmentId = environmentId;

	loadMap(this->environmentId);
}

// this version of the constructor takes a string that represents a UID
// of a known Environment and uses that to load the environment map
// if it exists.  If it doesn't exist, it creates an empty map for the
// environment and continues on.
EnvironmentManager::EnvironmentManager(std::string environmentId)
{
	boost::uuids::string_generator gen;
	//boost::uuids::uuid u1 = gen("{01234567-89ab-cdef-0123-456789abcdef}");

	this->environmentId = gen(environmentId);

	loadMap(this->environmentId);
}


// the destructor for the class always saves the environment map on the
// way out
EnvironmentManager::~EnvironmentManager()
{

	saveMap(this->environmentId);

}

// ::getInitialState returns the initial state to the agent after the
// environment has been loaded
State EnvironmentManager::getInitialState()
{
	State initState;

	// TODO:  This is arbitrary.  It should draw a random
	// non-terminal starting location from the environment
	// and return to the agent.

	initState.loc.x = 1;
	initState.loc.y = 3;
	initState.isTerminal = false;

	return initState;
}

// ::loadMap attempts to load the environment map for a specified environment
// from the base directory.  It returns 0 if successful and -1 if an error
// occurred.  The format of the filename is <uid>.map
int EnvironmentManager::loadMap(boost::uuids::uuid environmentId)
{

	std::cout << RlUtil::timestamp() << " EnvironmentManager::loadMap - environmentId: " << environmentId << std::endl;

	return 0;
}

// ::saveMap attempts to save the environment map for a specified environment
// to the base directory.  It returns 0 if successful and -1 if an error
// occurred.  The format of the filename is <uid>.map
int EnvironmentManager::saveMap(boost::uuids::uuid environmentId)
{
	std::cout << RlUtil::timestamp() << " EnvironmentManager::saveMap - environmentId: " << environmentId << std::endl;

	return 0;
}

RewardState EnvironmentManager::submitAction(State s, Action a)
{

	double score = EnvironmentManager::scoreAction(s, a);

	Location nextLoc = s.loc;

	switch(a)
	{
		case static_cast<int>(Action::up): 
			nextLoc.y++;
			break;

		case static_cast<int>(Action::down):
			nextLoc.y--;
			break;

		case static_cast<int>(Action::left):
			nextLoc.x--;
			break;	

		case static_cast<int>(Action::right):
			nextLoc.x++;
			break;	
	}

	RewardState rs;

	State nextState;

	if (score == -1.0)
	{
		nextState.isTerminal = true;
		nextState.loc = nextLoc;

		rs.nextState = nextState;
		rs.isReward = true;
		rs.reward = score;	
	}

	 else if (score == 10.0)
	{
		nextState.isTerminal = true;
		nextState.loc = nextLoc;
		
		rs.nextState = nextState;
		rs.isReward = true;
		rs.reward = score;	
	}
		
	else 
	{
		nextState.isTerminal = false;
		nextState.loc = nextLoc;
		
		rs.nextState = nextState;
		rs.isReward = false;
		rs.reward = score;	

	}

	return rs;

}

double EnvironmentManager::scoreAction(State s, Action a)
{

	// For our base implementation, this should return
	// 10.0 if the Action a results in the agent moving to the
	// target location, 0.0 if a valid non-target location, and
	// a -10 if the agent crosses a boundary location (wall)

	Location nextLoc = s.loc;

	switch(a)
	{
		case static_cast<int>(Action::up): 
			nextLoc.y++;
			break;

		case static_cast<int>(Action::down):
			nextLoc.y--;
			break;

		case static_cast<int>(Action::left):
			nextLoc.x--;
			break;	

		case static_cast<int>(Action::right):
			nextLoc.x++;
			break;	
	}

	if (nextLoc.y == MIN_HEIGHT || 
		nextLoc.y == MAX_HEIGHT || 
		nextLoc.x == MIN_WIDTH || 
		nextLoc.x == MAX_WIDTH)
	{
		return -1.0;		
	}
	else if (nextLoc.x == goal.x && nextLoc.y == goal.y)
	{
		return 10.0;
	}
	else
		return 0.0;

}

