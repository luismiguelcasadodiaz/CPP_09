#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <cstddef>
#include <deque>
#include <iterator>

template<typename T, typename Container = std::deque<T> >
class PmergeMe
{
    public:
        PmergeMe(void);
        ~PmergeMe(void);
        PmergeMe(std::vector<T> & data);

		//bool empty(void) const;
		size_t size(void) const;

		typedef typename Container::iterator iterator ;
		typedef typename Container::const_iterator const_iterator ;        
        iterator before_begin();
        iterator before_end();
        iterator after_begin();
        iterator after_end();
        //const_iterator begin() const;
        //const_iterator end() const;
        void sortSTL(void);
        void sort(void);
    private:

        PmergeMe(PmergeMe const & other);
        PmergeMe & operator=(PmergeMe const & other);
        void insert_element(Container & sorted, typename Container::iterator iterator, T newElement);
        void binary_insertion(Container & sorted, Container & main, Container & pend);
        void sortn(Container & sorted, Container & numbers);
        void jacobsthal(size_t elements_to_insert);       
        /*void sort5(void);
        void sort4(void);        
        void sort3(void);
        void sort2(void);
        void pair_eval(size_t i, size_t j, T * mij, T * Mij);
        */
                
        size_t _n;
        Container _numbers;
        Container _sorted;
        Container J;        

        // size_t _n_main;
        // size_t _main_i;
        // size_t _main_e;
        // size_t _pend_i;
        // size_t _pend_e;
        // size_t _n_new;                        
};
template<typename T, typename Container>
PmergeMe<T,Container>::PmergeMe(void): _numbers( T() ),	_sorted(T())
{
    this->_n = 0;
}

template<typename T, typename Container>
PmergeMe<T,Container>::~PmergeMe(void) {}

template<typename T, typename Container>
PmergeMe<T,Container>::PmergeMe(PmergeMe const & other)
{
	(void)other;
}

template<typename T, typename Container>
PmergeMe<T,Container> & PmergeMe<T,Container>::operator=(PmergeMe const & other)
{
	(void)other;
	return *this;
}



template<typename T, typename Container>
PmergeMe<T,Container>::PmergeMe(std::vector<T> & data)
{
    this->_numbers.insert(this->_numbers.begin(), data.begin(), data.end());
    this->_n = this->_numbers.size();
    this->jacobsthal(this->_n);
}


template<typename T, typename Container>
size_t PmergeMe<T,Container>::size(void) const
{
    return this->_numbers.size();
}

template<typename T, typename Container>
typename PmergeMe<T, Container>::iterator PmergeMe<T, Container>::before_begin()
{
	return this->_numbers.begin();
}
template<typename T, typename Container>
typename PmergeMe<T, Container>::iterator PmergeMe<T, Container>::before_end()
{
	return this->_numbers.end();
}

template<typename T, typename Container>
typename PmergeMe<T, Container>::iterator PmergeMe<T, Container>::after_begin()
{
	return this->_sorted.begin();
}
template<typename T, typename Container>
typename PmergeMe<T, Container>::iterator PmergeMe<T, Container>::after_end()
{
	return this->_sorted.end();
}

template<typename T, typename Container>
void PmergeMe<T,Container>::sortSTL(void)
{
    std::sort(this->_numbers.begin(), this->_numbers.end());
}

template<typename T, typename Container>
void PmergeMe<T,Container>::sort(void)
{
    this->sortn(this->_sorted, this->_numbers);
}

template<typename T, typename Container>
void PmergeMe<T,Container>::sortn(Container & sorted, Container & numbers)
{
    Container m ; // largest numbers
    Container p ; // Smallest numbers
    size_t n = numbers.size();
    for (size_t i = 0; i < n - 1 ; i += 2) // (0 vs 1) (2 vs 3) ....( n)
    {
        if ( numbers[ i ] < numbers[ i + 1 ])
        { 
            m.push_back( numbers[ i + 1 ] ) ;
            p.push_back( numbers[ i     ] ) ;           
        }
        else
        {
            m.push_back( numbers[ i     ] ) ;
            p.push_back( numbers[ i + 1 ] ) ;              
        }
    }
	if ( ( n % 2) == 1) // n was odd
    { 
        m.push_back( numbers[ n - 1 ] ) ;
    }
	if (n > 2)
    {
        this->sortn(sorted, m);
		//if ( ( n % 2) == 1) // n was odd
		//{ 
		//	this->insert_element(sorted, sorted.end(),  numbers[ n - 1 ] ) ;
		//}
        this->binary_insertion(sorted, m, p);
        //numbers.clear();
        //numbers.insert(numbers.begin(), m.begin(), m.end());
    }
    else if ( n == 2)
    { 
        sorted.push_back(p.back());
        sorted.push_back(m.back());
    } else {
        sorted.push_back(numbers.back());
    }
}





template<typename T, typename Container>
void  PmergeMe<T,Container>::jacobsthal(size_t elements_to_insert)
{
    if (this->J.size() > 0) { this->J.clear();}
    if (elements_to_insert > 0) {this->J.push_back(0);}
    if (elements_to_insert > 1) {this->J.push_back(1);}
    for (size_t i = 2; i < elements_to_insert; ++i)
    {
        this->J.push_back(this->J[ i - 1] + 2LL * this->J[ i - 2]);
        if ( elements_to_insert <= this->J.back() )
            break;
    }
}   
template<typename T, typename Container>
void PmergeMe<T,Container>::binary_insertion(Container & sorted, Container & main, Container & pend)
{
    
    size_t idx = 0;
	size_t p_size = pend.size();
/*	size_t m_size = main.size();
	size_t s_size = sorted.size();
   
    std::cout << "Into (0, " << s_size - 1 << ")==> ";

    while (idx < s_size ) 
    {
        std::cout << sorted[idx++] << " ";
    }
   std::cout << " Inserting (" << m_size << "," << m_size + p_size - 1 <<") ==>";
    
    idx = 0;
    while (idx < p_size ) 
    {
        std::cout << pend[idx++] << " ";
    }
    idx = 0;
    std::cout << " before big partners  ==>";
    while (idx < m_size ) 
    {
        std::cout << main[idx++] << " ";
    }
    std::cout << std::endl;
*/
    idx = 0;

	if ( p_size == 1 )
	{
    	this->insert_element(sorted, sorted.end() , pend[0]);
	} else {
    	this->insert_element(sorted, sorted.end() , pend[1]);
    	this->insert_element(sorted, sorted.end() , pend[0]);
		idx = 2;
		//while ( ( idx < ( this->J.size() - 1) ) && ( this->J[idx + 1] <= pend.size() ) )
		while ( ( idx < ( this->J.size() - 1) ) )
		{
			size_t lastone;
			if ( ( p_size - 1 ) <= this->J[ idx + 1 ] )
			{
				lastone = p_size - 1 ;
			}
			else
			{
				lastone = this->J[ idx + 1 ];
			}
			
			for (size_t i = lastone ; this->J[ idx ] < i; i--)
			{
			   // if (main[i] == *sorted.begin())
				//{
			//		//sorted.push_front(pend[i]) ;
			//		sorted.insert(sorted.begin(), pend[i]);
			//	} else {
					//typename Container::iterator it = upper_bound (sorted.begin(), sorted.end(), main[idx + 1]);
					typename Container::iterator it = upper_bound (sorted.begin(), sorted.end(), main[i]);
					//std::cout << "The big pair of "<<  pend[i] << " is i " << main[i] << std::endl;
					this->insert_element(sorted, it , pend[i]);            
			//	}
				//this->insert_element(sorted, sorted.end() , pend[i]);
			}
			idx++;
		}
	}
}

template<typename T, typename Container>
void PmergeMe<T,Container>::insert_element(Container & sorted, typename
Container::iterator rightPos, T newElement)
{
    typename Container::iterator leftPos = sorted.begin();
	
	// Binary search loop
	while (leftPos != rightPos)
	{
		typename Container::difference_type dist = std::distance(leftPos , rightPos);
        typename Container::iterator midPos = leftPos + dist  / 2;
		
		//std::cout << "Checking: leftPos=" << leftPos << ", midPos=" << midPos 
		  //        << ", rightPos=" << rightPos << " -> v[" << midPos << "]=" << v[midPos] << std::endl;
		
		// Test if new element is greater or lower than middle element
		if (newElement < *midPos)
		{
			rightPos = midPos;
		}
		else
		{
			leftPos = midPos;
            ++leftPos;
		}
	}
	
	//std::cout << "Insert "<< newElement<<" into position " << std::distance(sorted.begin(), leftPos) << std::endl;
	
	// Insert the new element
	sorted.insert(leftPos, newElement);


}

/*
template<typename T, typename Container>
void PmergeMe<T,Container>::pair_eval(size_t i, size_t j, T * a, T * b)
{
    if ( Container::operator[](i) < (*this)[j] ) // a < b
    {
        *a = (*this)[i];
        *b = this->operator[](j);
    }
    else                                         // b < a
    {
        *a = Container::operator[](j);
        *b = Container::operator[](i);
    }
}

template<typename T, typename Container>
void PmergeMe<T,Container>::sort2(void)
{
    T a;
    T b;
    std::cout << "Sorting 1 , 2"  << std::endl;   
    this->pair_eval(0, 1, &a, &b);               // a < b  
    (*this)[0] = a;
    (*this)[1] = b;
}
template<typename T, typename Container>
void PmergeMe<T,Container>::sort3(void)
{
    T a;
    T b;
    std::cout << "Sorting 1 , 3"  << std::endl;       
    this->pair_eval(0, 1, &a, &b);             // a < b
    if ( (*this)[2] < a )                        
    {                                         // v[2] < a < b  
        (*this)[0] = (*this)[2];        
        (*this)[1] = a;
        (*this)[2] = b;

    } else if ( (*this)[2] < b )
    {                                         //  a < v[2] < b
        (*this)[0] = a;       
        (*this)[1] = (*this)[2]; 
        (*this)[2] = b;

    } else  
    {                                         //  a < b < v[2]
        (*this)[0] = a;       
        (*this)[1] = b;
        (*this)[2] = (*this)[2]; 
    }
}
template<typename T, typename Container>
void PmergeMe<T,Container>::sort4(void)
{
    T a;
    T b;
    T c;
    T d;            
    T M01;
    T M23;
    std::cout << "Sorting 1 , 4"  << std::endl;
    this->pair_eval(0, 1, &a, &M01);
    this->pair_eval(2, 3, &c, &M23);
    if (M01 < M23){
        b = M01;
        d = M23;
    }   else {
        b = M23;
        d = M01;
    }
    // a < b < d && c < d
    std::cout << a << "," << b << "," << d << " & " << c << "," << d << std::endl;
    if (c < b)
    {
        if (c < a)
        {                                  // c < a < b < d
        (*this)[0] = c;       
        (*this)[1] = a;
        (*this)[2] = b;
        (*this)[3] = d; 
        }
        else // a < c
        {                                  // a < c < b < d
        (*this)[0] = a;       
        (*this)[1] = c;
        (*this)[2] = b;
        (*this)[3] = d; 
        }

    } else // b < c
    {                                     // a < b < c < d
        (*this)[0] = a;       
        (*this)[1] = b;
        (*this)[2] = c;
        (*this)[3] = d;       
    }
} 

template<typename T, typename Container>
void PmergeMe<T,Container>::sort5(void)
{
    T a;
    T b;
    T c;
    T d;
    T e;            
    T M01;
    T M23;
    std::cout << "Sorting 1 , 5"  << std::endl;

    // Pag 183 of book. FIgure 5
    this->pair_eval(0, 1, &a, &M01);
    this->pair_eval(2, 3, &c, &M23);
    if (M01 < M23){
        b = M01;
        d = M23;
    }   else {
        b = M23;
        d = M01;
    }
    if (b < a) {M01 = b; b = a; a = M01;}
    // Till here we know a < b < d && c < d
    std::cout << a << "," << b << "," << d << " & " << c << "," << d << std::endl;
    // Let's insert the 5th element
    e = (*this)[4];

    if ( e < b)
    {
        if ( e < a )           // e < a < b < d && c < d
        {
            if ( c < a)
            {
                if ( c < e)    // ---> c < e < a < b < d
                {
                    (*this)[0] = c;       
                    (*this)[1] = e;
                    (*this)[2] = a;
                    (*this)[3] = b;
                    (*this)[4] = d;                     
                }
                else           // ---> e < c < a < b < d
                {
                    (*this)[0] = e;       
                    (*this)[1] = c;
                    (*this)[2] = a;
                    (*this)[3] = b;
                    (*this)[4] = d;              
                }
            }
            else  // a < c            
            {
                if (c < b )    // ---> e < a < c < b < d
                {
                    (*this)[0] = e;       
                    (*this)[1] = a;
                    (*this)[2] = c;
                    (*this)[3] = b;
                    (*this)[4] = d;              
                }
                else           // ---> e < a < b < c < d
                {
                    (*this)[0] = e;       
                    (*this)[1] = a;
                    (*this)[2] = b;
                    (*this)[3] = c;
                    (*this)[4] = d;              
                }
            }
        }
        else // a < e          // a < e < b < d && c < d
        {////////////////////////////////////////////
            if ( c < a)         // ---> c < a < e < b < d
            {
                    (*this)[0] = c;       
                    (*this)[1] = a;
                    (*this)[2] = e;
                    (*this)[3] = b;
                    (*this)[4] = d;                
            }
            else  // a < c            
            {
                if (c < e )    // ---> a < c < e < b < d
                {
                    (*this)[0] = a;       
                    (*this)[1] = c;
                    (*this)[2] = e;
                    (*this)[3] = b;
                    (*this)[4] = d;                
                }
                else // e < c           
                {
                    if (c < b)       // ---> a < e < c < b < d
                    {
                        (*this)[0] = a;       
                        (*this)[1] = e;
                        (*this)[2] = c;
                        (*this)[3] = b;
                        (*this)[4] = d;
                    }
                    else // b < c  // ---> a < e < b < c < d
                    {
                        (*this)[0] = a;       
                        (*this)[1] = e;
                        (*this)[2] = b;
                        (*this)[3] = c;
                        (*this)[4] = d;
                    }
                }
            }
        }

    } else // b < e
    {
        if ( e < d)           // a < b < e < d && c < d
        {
            if ( c < a)
            {                // ---> c < a < b < e < d 
                    (*this)[0] = c;       
                    (*this)[1] = a;
                    (*this)[2] = b;
                    (*this)[3] = e;
                    (*this)[4] = d;                
            }
            else // a < c
            {
                if (c < b)
                {            // ---> a < c < b < e < d 
                    (*this)[0] = a;       
                    (*this)[1] = c;
                    (*this)[2] = b;
                    (*this)[3] = e;
                    (*this)[4] = d;                
                }
                else // b < c
                {                
                    if (c < e)
                    {           // ---> a < b < c < e < d 
                        (*this)[0] = a;       
                        (*this)[1] = b;
                        (*this)[2] = c;
                        (*this)[3] = e;
                        (*this)[4] = d;
                    }
                    else //e < c
                    {          // ---> a < b < e < c < d 
                        (*this)[0] = a;       
                        (*this)[1] = b;
                        (*this)[2] = e;
                        (*this)[3] = c;
                        (*this)[4] = d;
                    }             
                }
            }
        }
        else                  // a < b < d < e && c < d
        {
            if ( c < a )
            {                // ---> c < a < b < d < e
                    (*this)[0] = c;       
                    (*this)[1] = a;
                    (*this)[2] = b;
                    (*this)[3] = d;
                    (*this)[4] = e;                
            }
            else // a < c
            {
                if (c < b)
                {             // ---> a < c < b < d < e
                    (*this)[0] = a;       
                    (*this)[1] = c;
                    (*this)[2] = b;
                    (*this)[3] = d;
                    (*this)[4] = e;                
                }
                else // b < c
                {             // ---> a < b < c < d < e
                    (*this)[0] = a;       
                    (*this)[1] = b;
                    (*this)[2] = c;
                    (*this)[3] = d;
                    (*this)[4] = e;                                
                }
            }
        }

    }
}
*/
#endif
