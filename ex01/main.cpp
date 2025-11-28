#include "RPN.hpp"
#include <iostream>

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage ./RPN \"Reversal polish notation expression\" " <<
		std::endl;
	}
	try
	{
		RPN c;
		int idx = -1;
		while (argv[1][++idx] != '\0')
		{
			if ( ( 32 <= argv[1][idx] ) && ( argv[1][idx] <= 57 ) )
			{
				if ( argv[1][idx] == '+' ) {c.sum(); continue; }
				if ( argv[1][idx] == '-' ) {c.dif(); continue; }
				if ( argv[1][idx] == '*' ) {c.mul(); continue; }
				if ( argv[1][idx] == '/' ) {c.div(); continue; }
				if ( ( 48 <= argv[1][idx] ) && ( argv[1][idx] <= 57 ) )
				{
					c.pus( argv[1][idx] - '0' );
					continue;
				}
				if ( argv[1][idx] != ' ')
				{
					std::cout << "Error" << std::endl;
					return (0);
				}

			} else {
				std::cout << "Error" << std::endl;
			}
		}
		std::cout << c.top() << std::endl;
	} catch (std::exception &e)
	{
		std::cout << e.what() << std::endl ;
	}
	return (0);
}
