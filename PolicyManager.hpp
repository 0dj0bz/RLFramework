// PolicyManager.hpp

#pragma once

const double GAMMA = 0.95;

class PolicyManager
{

	public:

		boost::uuids::uuid environmentId;

		PolicyManager(boost::uuids::uuid environmentId);
		~PolicyManager();

		void updatePolicy(State s, Action a, double);
		Action selectAction(State s);

	private:

		// so, the key to the policy table is the state-action pair
		//.       x.            y.           Action. Value.
		std::map<int, std::map<int, std::map<Action, PolicyBody> > > map;

		Action selectOptimalAction(State s);

		int loadMap(boost::uuids::uuid environmentId);
		int saveMap(boost::uuids::uuid environmentId);

};

PolicyManager::PolicyManager(boost::uuids::uuid environmentId)
{
	this->environmentId = environmentId;
	loadMap(environmentId);

}

PolicyManager::~PolicyManager()
{

	saveMap(this->environmentId);

}

Action PolicyManager::selectOptimalAction(State s)
{
	//std::cout << "PolicyManager::selectOptimalAction - entry" << std::endl;


	if (this->map[s.loc.x][s.loc.y].size() > 0)
	{
		Action bestAct = Action::down; // arbitrarily set it to down
		double bestReward = -1000.0;

		for (auto iter = this->map[s.loc.x][s.loc.y].begin(); iter != this->map[s.loc.x][s.loc.y].end(); ++iter)
		{

//			std::cout << "Policy 0,0 Action : " << iter->first << " value: " << m2[0][0][iter->first] << std::endl;
			double reward;

			double sov = this->map[s.loc.x][s.loc.y][iter->first].sumOfValues;
			double noc = this->map[s.loc.x][s.loc.y][iter->first].numberOfComponents;

			reward = sov / noc;

			if ((sov/noc) > bestReward)
			{
				bestReward = reward;
				bestAct = iter->first;
			}

		}

//		std::cout << "Policy (" << s.loc.x << "," << s.loc.y << ") Action : " << static_cast<int>(bestAct) << " value: " << bestReward << std::endl;

		return bestAct;
	}
	else
		return Action::invalid;


}

void PolicyManager::updatePolicy(State s, Action a, double reward)
{

	this->map[s.loc.x][s.loc.y][a].sumOfValues += reward;
	this->map[s.loc.x][s.loc.y][a].numberOfComponents++;

//	std::cout << "sumOfValues: " << this->map[s.loc.x][s.loc.y][a].sumOfValues << std::endl;
//	std::cout << "numberOfComponents: " << this->map[s.loc.x][s.loc.y][a].numberOfComponents << std::endl;

}


Action PolicyManager::selectAction(State s)
{

	// TODO: selectAction should look at the policy map for the current location 
	// and either select the current best policy or with some degree of randomness
	// select an alternate action

	// accessing a map location that hasn't been initialized gives a 0 value, so 
	// we can use that as a gauge for an untried policy

	Action selAct;

	// if (map[s.loc.x][s.loc.y].size() == 0), then the only choice is to make a random selection
	// also, every so often, select a random action

	if ( ( (RlUtil::oneIn100()%5)==0) || this->map[s.loc.x][s.loc.y].empty())
	{

		selAct = static_cast<Action>((RlUtil::oneIn100()%4)+1);
		//std::cout << RlUtil::timestamp() << " PolicyManager::selectAction - selected random Action: " << static_cast<int>(selAct) << std::endl;		

	}
	else
	{
		// TODO: select the current "best" policy for the state
		//selAct = static_cast<Action>(RlUtil::oneIn100()%4+1);
		selAct = this->selectOptimalAction(s);
		//std::cout << RlUtil::timestamp() << " PolicyManager::selectAction - selected Action: " << static_cast<int>(selAct) << std::endl;
	}

	return selAct;

}


int PolicyManager::loadMap(boost::uuids::uuid environmentId)
{

	std::cout << RlUtil::timestamp() << " PolicyManager::loadMap - environmentId: " << environmentId << std::endl;

	return 0;
}

int PolicyManager::saveMap(boost::uuids::uuid environmentId)
{

	std::cout << RlUtil::timestamp() << " PolicyManager::saveMap - environmentId: " << environmentId << std::endl;

	return 0;
}

