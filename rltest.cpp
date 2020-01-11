
#include "rlframework.hpp"


long iterations=500000L;

long episodeCount=1L;

long bestScore=999999999999999L;

bool abortFlag = false;

int main(int argc, char **argv)
{

	bool verbose = false;

	if (argc == 2)
		if (strcmp(argv[1], "--verbose") == 0)
			verbose = true;

	EnvironmentManager em = EnvironmentManager("20123cc2-7c29-49c6-9dc1-88a0bd31e18c");



	PolicyManager pm = PolicyManager(em.environmentId);

	// request an initial state from the environment to get started

	State curState = em.getInitialState();

	//std::cout << RlUtil::timestamp() << " rltest_cpp - curState - loc(x,y): (" << curState.loc.x << "," << curState.loc.y << ")" 
	//	<< " - terminal: " << curState.isTerminal << std::endl;


	bool win = false;

	Reward reward;
	State state;
	Action action;
	long epLen;


	if (verbose)
		std::cout << RlUtil::timestamp() << " rltest_cpp - main - episodeCount: " << episodeCount << std::endl;

	// this episode continues until we get a terminal state from the environment
	while (iterations-- > 0)
	{

		Episode ep = Episode(em.environmentId);
		ep.epochCount = 1;
		epLen = 0;

		win = false;

		while (!curState.isTerminal)
		{

			Action  a = pm.selectAction(curState);

			RewardState rs = em.submitAction(curState, a);

			SAR sar; 

			sar.s = curState;
			sar.a = a;
			sar.r = rs.reward;
			sar.s.curEpoch = epLen;

			ep.logStateInfo(sar);

			curState = rs.nextState;

			reward = rs.reward;
			state = rs.nextState;
			action = a;
			epLen = ep.mapLen();

			if (epLen > MAX_WIDTH*MAX_WIDTH*50)
			{
				abortFlag = true;
				break;
			}
	
		}

		// we have hit a terminal state for the current episode
		

	//	std::cout << "Episode map length: " << epLen << std::endl;	



		if (reward == 10.0)
		{
			win = true;


			//std::cout << RlUtil::timestamp() << " rltest_cpp - =======WIN=======WIN=======WIN=======" << std::endl;
		}
		//else
			//std::cout << RlUtil::timestamp() << " rltest_cpp - =======LOSE======LOSE======LOSE======" << std::endl;


		// need to apply the score across the episode and update the policy map / q functions
		// so, we go backward through the episode applying a discounted reward to each step

		int count = 1;

		if (!abortFlag)
		{
			for (auto iter = (ep.map.end()); iter != ep.map.begin(); --iter)
			{
				if (iter != ep.map.end())
				{

					double discountedRwd = reward * pow(GAMMA, static_cast<double>(count));

					ep.map[(iter->first)].r = discountedRwd;
					pm.updatePolicy(ep.map[iter->first].s, ep.map[iter->first].a, ep.map[iter->first].r);

					count++;

				}
			}
		}

		abortFlag = false; // reset abort flag

		if (verbose)
			std::cout << RlUtil::timestamp() << " rltest_cpp - ******* RESTART ********" << std::endl;

		curState = em.getInitialState();

		episodeCount++;

		if (verbose)
			std::cout << RlUtil::timestamp() << " rltest_cpp - main - episodeCount: " << episodeCount << std::endl;

		if (win && (epLen < bestScore))
		{
			bestScore = epLen;
			std::cout << RlUtil::timestamp() << " Episode " << episodeCount << " - best path len: " << bestScore << std::endl;
		}
	}
}



