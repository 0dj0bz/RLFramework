
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

enum Action {best=0, up=1, down=2, left=3, right=4};

// template<class T>

// void printMap(const T& m)
// {
//     for (auto& [key, value] : m) {
//         std::cout << "Key: " << key << ", Value: " << value.front() << std::endl;
//     }
//     std::cout << "-------" << std::endl;
// }


int main(int argc, char * argv[])
{
	
	// std::map<int, std::vector<std::string> > m;

	// m[0].push_back("Panda");
	// m[1].push_back("Dammer");
	// m[2].push_back("Casey");
	// m[3].push_back("Raven");
	// m[4].push_back("Sable");
	// m[5].push_back("Samson");


	// printMap(m);


	std::map<int, std::map<int, std::map<Action, double> > > m2;

	std::map<Action, double> subm;

	m2[0][0][up] = 0.1;
	m2[0][0][right] = 0.2;	

	// std::cout << "Policy 0,0 Action up: value: " << m2[0][0][up] << std::endl;

	// std::cout << "Policy 0,0 Action down: value: " << m2[0][0][down] << std::endl;


	subm =  m2[0][0];

	std::cout << "subm[up]: " << subm[up] << std::endl;

	std::cout << "m2[0][0].size(): " << m2[0][0].size() << std::endl;

	for (auto iter = m2[0][0].begin(); iter != m2[0][0].end(); ++iter)
	{

		std::cout << "Policy 0,0 Action : " << iter->first << " value: " << m2[0][0][iter->first] << std::endl;

		double bestScore = -999;

		if (iter->first != 0)
		{
			if (m2[0][0][iter->first] > best)
			{
				bestScore = m2[0][0][iter->first];
				m2[0][0][best] = bestScore;
			}
		}

	}
	std::cout << "m2[0][0][best]: " << m2[0][0][best] << std::endl;

	std::cout << "m2[99][0].size() 0 before: " << m2[99][0].size() << std::endl;

	std::cout << "m2[99][0].empty() 0 before: " << m2[99][0].empty() << std::endl;
	

	std::cout << "Policy 99,0 Action down: value: " << m2[99][0][down] << std::endl;

	std::cout << "m2[99][0].size() 0 after: " << m2[99][0].size() << std::endl;		

	std::cout << "m2[99][0].empty() 0 before: " << m2[99][0].empty() << std::endl;

	m2[99][0][best] = 0.3;






}