#ifndef RPN_HH
#define RPN_HH

class Rpn
{
    private:
        std::stack<int> s;
    public:
        Rpn( void );
        Rpn( void );
        Rpn( Rpn const ^ other );
        Rpn( void );        

        void sum (void);
        void dif (void);
        void mul (void);
        void div (void);
};

#end_if