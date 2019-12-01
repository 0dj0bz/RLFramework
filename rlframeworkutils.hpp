class RlUtil 

{

	public:

		// TODO: Eventually swap this out for boost::log OR
		// update to include millisecond - microsecond granularity
		static std::string timestamp()
		{
			time_t time = std::time(nullptr);
			tm time_tm = *std::localtime(&time);
			char buffer[256];
			strftime(buffer, sizeof(buffer), "%x %X", &time_tm);

			return(buffer); 
		}


		// TODO: Eventually swap all of this out to use boost::random
		static int oneIn4()
		{

			static std::random_device seeder;
			static const auto seed = seeder.entropy() ? seeder() : std::time(nullptr);

			static std::default_random_engine generator(
			static_cast<std::default_random_engine::result_type>(seed));

			static std::uniform_int_distribution<int> distribution(1, 4);

			return distribution(generator);

		}

		static int oneIn5()
		{

			static std::random_device seeder;
			static const auto seed = seeder.entropy() ? seeder() : std::time(nullptr);

			static std::default_random_engine generator(
			static_cast<std::default_random_engine::result_type>(seed));

			static std::uniform_int_distribution<int> distribution(1, 5);

			return distribution(generator);

		}

		static int oneIn100()
		{

			static std::random_device seeder;
			static const auto seed = seeder.entropy() ? seeder() : std::time(nullptr);

			static std::default_random_engine generator(
			static_cast<std::default_random_engine::result_type>(seed));

			static std::uniform_int_distribution<int> distribution(1, 100);

			return distribution(generator);

		}
};