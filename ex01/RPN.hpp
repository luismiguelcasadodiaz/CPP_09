#ifndef RPN_HH
#define RPN_HH
#include <stack>

class RPN
{
    private:
        std::stack<int> s;
    public:
        RPN( void );
        ~RPN( void );
        RPN( RPN const & other );
        RPN & operator=( RPN const & other );        

        void sum (void);
        void dif (void);
        void mul (void);
        void div (void);
        int &  top (void);
        void pus (int const & num);
        void pop (void);
		int size (void) const ;
};

#endif
