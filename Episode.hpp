// Episode.hpp
//
// Requires Boost libraries v. 1.70.0 - see https://boost.org for details
//

#pragma once


class Episode
{

	public:

		// data
		boost::uuids::uuid environmentId;
		boost::uuids::uuid episodeId;
		long epochCount=0;

		// methods
		Episode(boost::uuids::uuid environmentId);		

		~Episode();

		int logStateInfo(SAR sar);

		long mapLen();

		std::map<long, SAR> map;

	private:
		std::vector<SAR> episodeLog;

		int loadMap(boost::uuids::uuid environmentId);
		int saveMap(boost::uuids::uuid environmentId);
};

Episode::Episode(boost::uuids::uuid environmentId)
{
	this->epochCount = 0;
	this->environmentId = environmentId;
	this->episodeId = boost::uuids::random_generator()();
}

Episode::~Episode()
{

}

/*---------------------------------------------------------------------------
  Episode::logStateInfo(RewardState rsInfo)

  Logs the current state info into the Episode graph. Each invocation adds
  a new vertex and edge to the graph.

  Returns:
    0 			- Success
    Otherwise 	- Error
---------------------------------------------------------------------------*/
int Episode::logStateInfo(SAR sar)
{

	map[epochCount] = sar;

	this->epochCount++;

	return 0;
}

long Episode::mapLen()
{

	return map.size();
}

