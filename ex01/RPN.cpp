#include "RPN.hpp"
#include <iostream>
#include <stdexcept>

RPN::RPN( void ): s()
{

}

RPN::~RPN( void )
{

}

RPN::RPN( RPN const & other )
{
	*this = other;
}

RPN & RPN::operator=( RPN const & other )
{
	if (this != & other)
	{
		this->s = other.s;
	}
	return *this;
}
        

void RPN::sum (void)
{
	if (this->s.size() > 1)
	{
		int op1 = this->s.top();
		this->pop();
		int op2 = this->s.top();
		this->pop();
		this->s.push ( op1 + op2 );
	} else {
		throw std::runtime_error("Not enough values in the stack");
    }
}

void RPN::dif (void)
{
	if (this->s.size() > 1)
	{
		int sustraendo = this->s.top();
		this->pop();
		int minuendo = this->s.top();
		this->pop();
		this->s.push ( minuendo - sustraendo );
	} else {
		throw std::runtime_error("Not enough values in the stack");
    }
}

void RPN::mul (void)
{
	if (this->s.size() > 1)
	{
		int op1 = this->s.top();
		this->pop();
		int op2 = this->s.top();
		this->pop();
		this->s.push ( op1 * op2 );
	} else {
		throw std::runtime_error("Not enough values in the stack");
    }
}

void RPN::div (void)
{
	if (this->s.size() > 1)
	{
		int divisor = this->s.top();
		if ( divisor != 0)
		{
			this->pop();
			int dividen = this->s.top();
			this->pop();
			this->s.push ( dividen / divisor );
		} else {
			throw std::runtime_error("Try division with divisor = 0");
		}
	} else {
		throw std::runtime_error("Not enough values in the stack");
    }
}

int &  RPN::top (void)
{
	return this->s.top();
}

void RPN::pus (int const & num)
{
	this->s.push( num );
	//std::cout << num << std::endl;
}

void RPN::pop (void)
{
	this->s.pop();
}

