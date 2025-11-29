#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <set>
#include <vector>
#include <ctime>    // para time()
#include <iomanip>  // setprecision
#include "PmergeMe.hpp"

unsigned int my_atoi(char * argumento) {
    std::stringstream ss;
    ss << argumento; // Insertamos la cadena en el stream
    
    unsigned int num;
    ss >> num;

	if (ss.fail() || !ss.eof())
	{
		throw std::runtime_error("Error");
	}
    return (num);
}
void ImprimirElemento(int n) {
    std::cout << n << "\t";
}
	
int main(int argc, char** argv)
{
	std::set<unsigned int> mySet;


	if (argc == 1)
	{
		std::cout << "Usage ./PmergeMe <list of differente positive integers>\n" << std::endl;
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


	// Copy to vector
	std::vector<unsigned int> vec(mySet.begin(), mySet.end());

	// Shuffle the vector. THen set sorted all.
	std::random_shuffle(vec.begin(), vec.end());
    

//	clock_t start_insert_v = clock();
	PmergeMe<unsigned int, std::vector<unsigned int> > v(vec);
	//v.insert(v.begin(), vec.begin(), vec.end());
//	clock_t end_insert_v = clock();

//	std::cout << "Vector content Before:  " ;
//	std::for_each(v.before_begin(), v.before_end(), ImprimirElemento);
//	std::cout << std::endl;
/*
	clock_t start_insert_d = clock();
	//d.insert(d.begin(),vec.begin(), vec.end());
*/	PmergeMe<unsigned int> d(vec);
/*	clock_t end_insert_d = clock();

	std::cout << "Deque content Before:   " ;
	std::for_each(d.before_begin(), d.before_end(), ImprimirElemento);
	std::cout << std::endl;

	std::cout << "------------------ INSERT TIMES ---------------------: " << std::endl ;

	std::cout << std::fixed;        // Use fixed-point notation (e.g., 0.000003)
	std::cout << std::setprecision(6);
    std::cout << "Vector insert Time : " ;
    std::cout << (double) 1000000.0 *  (end_insert_v - start_insert_v) / CLOCKS_PER_SEC  << "µs" << std::endl;
	std::cout << "Deque insert Time : " ;
    std::cout << (double) 1000000.0 *  (end_insert_d - start_insert_d) / CLOCKS_PER_SEC  << "µs" << std::endl;


	std::cout << "------------------ SORT STL TIMES ---------------------: " << std::endl ;
	PmergeMe<unsigned int, std::vector<unsigned int> > vSTL(vec);
	PmergeMe<unsigned int> dSTL(vec);
	clock_t start_sortSTL_v = clock();
	vSTL.sortSTL();
	clock_t end_sortSTL_v = clock();
	clock_t start_sortSTL_d = clock();
	dSTL.sortSTL();
	clock_t end_sortSTL_d = clock();

	std::cout << "Vector sort Time : " ;
    std::cout << (double) 1000000.0 *  (end_sortSTL_v - start_sortSTL_v) / CLOCKS_PER_SEC  << "µs" << std::endl;
	std::cout << "Deque sort Time : " ;
    std::cout << (double) 1000000.0 *  (end_sortSTL_d - start_sortSTL_d) / CLOCKS_PER_SEC  << "µs" << std::endl;


	std::cout << "------------------ SORT TIMES ---------------------: " << std::endl ;
	clock_t start_sort_v = clock();
*///	v.sort();
/*	clock_t end_sort_v = clock();
	clock_t start_sort_d = clock();
*/	d.sort();
/*	clock_t end_sort_d = clock();
*/
//	std::cout << "Vector content After:\t" ;
//	std::for_each(v.after_begin(), v.after_end(), ImprimirElemento);
//	std::cout << std::endl;
	std::cout << "Deque content After:\t" ;
	std::for_each(d.after_begin(), d.after_end(), ImprimirElemento);
	std::cout << std::endl;
/*

	std::cout << "Vector sort Time : " ;
    std::cout << (double) 1000000.0 *  (end_sort_v - start_sort_v) / CLOCKS_PER_SEC  << "µs" << std::endl;
	std::cout << "Deque sort Time : " ;
    std::cout << (double) 1000000.0 *  (end_sort_d - start_sort_d) / CLOCKS_PER_SEC  << "µs" << std::endl;
	



	std::cout << "Time to process a range of " << v.size() ;
	std::cout << " elements with std::vector<unsigned int> : " << std::endl;
	std::cout << "Time to process a range of " << v.size() ;
	std::cout << " elements with std::deque<unsigned int> : " << std::endl;
	*/
}
