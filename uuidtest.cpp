#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>



int main()
{
	boost::uuids::uuid tag;

	tag = boost::uuids::random_generator()();

	std::cout << tag << std::endl;
}




