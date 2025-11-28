#ifndef DATE_HH
#define DATE_HH

#include <string>
#include <sstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <iomanip>
class Date 
{
        public:
            Date( void );
            ~Date( void );            
            Date( Date const & other );            
            Date & operator=( Date const & other );
            Date(std::string const date);
            bool operator==(Date const & rhs) const;                  
            //bool operator!=(Date & const rhs) const;  
            bool operator<(Date const & rhs) const;
            std::string get_d( void ) const;
            std::string get_m( void ) const;
            std::string get_y( void ) const;                        
        private:
            unsigned int y;
            unsigned int m;
            unsigned int d;
            bool is_valid_date( void ) const;
            bool is_valid_yea( std::stringstream & ss);            
            bool is_valid_mon( std::stringstream & ss);                        
            bool is_valid_day( std::stringstream & ss);                        
};

std::ostream & operator<<(std::ostream & os, Date const & d);
#endif