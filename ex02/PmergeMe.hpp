#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <cstddef>
#include <deque>
#include <vector>

void Imprimirme(int n) ;

template<typename T, typename Container = std::deque<T> >
class PmergeMe: public Container
{
    public:
        PmergeMe(void);
        ~PmergeMe(void);
        PmergeMe(std::vector<T> & data);

		//bool empty(void) const;
		size_t size(void) const;

		typedef typename Container::iterator iterator ;
		typedef typename Container::const_iterator const_iterator ;        
        iterator begin();
        iterator end();
        //const_iterator begin() const;
        //const_iterator end() const;
        void sortSTL(void);
        void sort(void);
    private:

        PmergeMe(PmergeMe const & other);
        PmergeMe & operator=(PmergeMe const & other);
        void insert_element(size_t rightPos, T newElement);
        void binary_insertion(size_t pend_i, size_t pend_e);
        void sortn(size_t n);        
        void sort5(void);
        void sort4(void);        
        void sort3(void);
        void sort2(void);
        void pair_eval(size_t i, size_t j, T * mij, T * Mij);
        void jacobsthal(size_t elements_to_insert);
        //void Imprimirme(int n);
                
        size_t _n;
        std::vector<T> J;
        // size_t _n_main;
        // size_t _main_i;
        // size_t _main_e;
        // size_t _pend_i;
        // size_t _pend_e;
        // size_t _n_new;                        
};
template<typename T, typename Container>
PmergeMe<T,Container>::PmergeMe(void) {
    this->_n = 0;
    // this->_n_main = 0;
    // this->_main_i = 0;
    // this->_main_e = 0;
    // this->_pend_i = 0;
    // this->_main_e = 0;   
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
    Container::insert(Container::begin(), data.begin(), data.end());
    this->_n = Container::size();
    // this->_n_main = this->_n;
    // this->_main_i = 1;
    // this->_main_e = _n_main;
    // this->_pend_i = _n_main;
    // this->_pend_e = _n_main;    
}


template<typename T, typename Container>
size_t PmergeMe<T,Container>::size(void) const
{
    return Container::size();
}

template<typename T, typename Container>
typename PmergeMe<T, Container>::iterator PmergeMe<T, Container>::begin()
{
	return Container::begin();
}
template<typename T, typename Container>
typename PmergeMe<T, Container>::iterator PmergeMe<T, Container>::end()
{
	return Container::end();
}


template<typename T, typename Container>
void PmergeMe<T,Container>::sortSTL(void)
{
    std::sort(Container::begin(), Container::end());
}

template<typename T, typename Container>
void PmergeMe<T,Container>::binary_insertion(size_t pend_i, size_t pend_e)
{

    PmergeMe<unsigned int, std::vector<unsigned int> > aux;
    aux.insert(aux.begin(),Container::begin() + pend_i,Container::begin() + pend_e);

    Container::erase(Container::begin() + pend_i, Container::begin() + pend_e);
    
    std::cout << "Into (0, " << pend_i - 1 << ")==> ";
    std::for_each(Container::begin(), Container::end(), Imprimirme);
    std::cout << std::endl;

    std::cout << "Insert ==> ";
    std::for_each(aux.begin(), aux.end(), Imprimirme);
    std::cout << std::endl;    
    
    this->jacobsthal((pend_e -1 ) - pend_i + 1);

    std::cout << "With Jacobsthal  ==> ";
    std::for_each(this->J.begin(),this->J.end(),Imprimirme  );
    std::cout << std::endl;  
    /*  
    size_t idx = 0;


    while (idx < (pend_i) ) 
    {
        std::cout << (*this)[idx++] << " ";
    }
    std::cout << " Inserting (" << pend_i << "," << pend_e - 1 <<") ==>";
    std::cout << std::endl;
*/
    /*
    while (pend_i < pend_e)
    {
        std::cout << "inserting " << (*this)[pend_i] << std::endl;
        this->insert_element(pend_i - 1,(*this)[pend_i]);
        Container::erase(Container::begin() + pend_i + 1);
        pend_i++;

    }
        */
       for (size_t i = 0; i < this->J.size() ; i++)
       { 
            std::cout << "rango insercion " << this->J[ i + 1 ] << ", " << this->J[ i ] << std::endl;
            for (size_t k = this->J[ i + 1 ];  this->J[ i ] < k; k--)
            {
                //std::cout << "inserting elemen[" << (pend_i - 1 )+ ( k) << "]=" << (*this)[ ( pend_i - 1 ) + ( k ) ] << std::endl;
                std::cout << "inserting elemen[" << (pend_i - 1 )+ ( k) << "]=" << aux[k - 1] << std::endl;
                this->insert_element(Container::size() - 1 , aux[k - 1] );                
                //this->insert_element(pend_i - 1,(*this)[ ( pend_i - 1 ) + ( k ) ] );
                //Container::erase(Container::begin() + pend_i + k);
            }
       }
    std::cout << "Resultado ==> ";
    std::for_each(Container::begin(), Container::end(), Imprimirme);
    std::cout << std::endl;
}

template<typename T, typename Container>
void PmergeMe<T,Container>::insert_element(size_t rightPos, T newElement)
{
    size_t leftPos = 0;
	
	// Binary search loop
	while (leftPos != rightPos)
	{
		size_t midPos = (leftPos + rightPos) / 2;
		
		//std::cout << "Checking: leftPos=" << leftPos << ", midPos=" << midPos 
		  //        << ", rightPos=" << rightPos << " -> v[" << midPos << "]=" << v[midPos] << std::endl;
		
		// Test if new element is greater or lower than middle element
		if (newElement < (*this)[midPos])
		{
			rightPos = midPos;
		}
		else
		{
			leftPos = midPos + 1;
		}
	}
	
	std::cout << "Insert position found: " << leftPos << std::endl;
	
	// Insert the new element
	Container::insert(Container::begin() + leftPos, newElement);


}


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

template<typename T, typename Container>
void PmergeMe<T,Container>::sort(void)
{
    this->sortn(this->_n);
}

template<typename T, typename Container>
void PmergeMe<T,Container>::sortn(size_t n)
{
    std::vector winner;
    std::vector loss;
    for(i= 0; i <= n/2; i+=2)
    {
    if ( (*this)[i] > (*this(i+1) )     {
        winner.push_back( (*this)[i] );
        losser.push_back( (*this[ i + 1]) );
    }else {
        winner.push_back( (*this)[i + 1] );
        losser.push_back( (*this)[ i ] );
    }
    if  ( (n % 2) == 1 ) {losser.push_back( (*this[ n - 1 ]) )}
    }
    if ( (winner.size() == 2 ) && (  winner.front() > winner.back() ) )
    {   
        winner.push_back( winner.front() );
        winner.erase(winner.begin());

    }
    else
    {
        

    }
    }

}
/*{
    size_t n_new;
    std::cout << "Sorting 1 ," << n << std::endl;    
    if (n >= 10)
    {
        n_new = n / 2;
        this->sortn(n_new);
        this->binary_insertion(n_new, n);

    } else if (n > 5)
    {
        sort5();
        binary_insertion(5, n);
    } else if (n == 5) {
        sort5();
    } else if (n == 4) {
        sort4();
    } else if (n == 3) {
        sort3();
    } else if (n == 2) {
        sort2();
    }
} */
#endif

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
/*
template<typename T, typename Container>
void PmergeMe<T,Container>::Imprimirme(int n) {
    std::cout << n << "\t";
*/

void Imprimirme(int n) {
    std::cout << n << "\t";
}