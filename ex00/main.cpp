#include <iostream>

int main(int argc, char** argv)
{
	std::set<unsigned int> mySet;


	if (argc == 1)
	{
		std::cout << "Usage ./btc <file_name>\n" << std::endl;
		return (0);
	}

	while ( argc > 1)
	{
		std::stringstream ss;
		try {
			unsigned int num = my_atoi(argv[ argc - 1] );
			// 2. Check uniqueness
    		std::pair<std::set<unsigned int>::iterator, bool> result = mySet.insert(num);
    		if (result.second == false) { // duplicated
 				std::cout << "Error" << std::endl;
				return (0);
			}
		 } catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		argc--;
	}