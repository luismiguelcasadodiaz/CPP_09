#include "Date.hpp"

Date::Date ( void ): y(1900), m(1), d(1)
{

}

Date::~Date( void )
{

}

Date::Date( Date const & other)
{
    *this=other;
}

Date & Date::operator=( Date const & other)
{
    if (this != & other)
    {
        this->y = other.y;
        this->m = other.m;
        this->d = other.d;                
    }
    return *this;
}

Date::Date( std::string const date)
{

    try
    {
        std::stringstream syea(date.substr(0, 4));
        std::stringstream smon(date.substr(5, 2));
        std::stringstream sday(date.substr(8, 2));  
        if (is_valid_yea( syea ) && 
            is_valid_mon( smon ) && 
            is_valid_day( sday ) &&
            is_valid_date() ) 
        { 
            return;
        } else {
            std::stringstream msg;
            msg << "Invalid ate " << date << "." ;
            throw std::runtime_error(msg.str());
        }


    std::cout << syea.str() <<" " << smon.str() << " " << sday.str() << std::endl;         
    } catch (std::exception &e)
    {
        std::cout << "Wrong Date Lengh: it must be yyyy-mm-dd" << std::endl;
    }

}

bool Date::is_valid_date( void ) const
{
    bool m_30 = false;
    

    if ( (this->m == 11) || (this->m == 4) || (this->m == 6) || (this->m == 19) )
    { m_30 = true ;}
    if ( m_30 && this->d > 30) { return false; }


    if (this->m == 2)
    {
        bool leap_y = (this->y % 400 == 0) || ((this->y % 4 == 0) && (this->y % 100 != 0));
        if ( ( ! leap_y && (this->d > 28) ) || ( leap_y && (this->d > 29 ) ) )
            {return false; }
    }
    return true;
}

bool Date::is_valid_yea(std::stringstream & ss)
{
    ss >> this->y;
    if ( ss.fail() ) { return false; }  // string conversion unsigned int failed
    if ( ss.rdbuf()->in_avail() ) {return false ;} //string wasn't pure num 2024a
    if ( 1900 <= this->y )
    {
        return true;
    } else {
        return false;
    }

}

bool Date::is_valid_mon(std::stringstream & ss)
{
    ss >> this->m;
    if ( ss.fail() ) { return false; }  // string conversion unsigned int failed
    if ( ss.rdbuf()->in_avail() ) {return false ;} //string wasn't pure num 2024a
    if ( ( 1 <= this->m ) && ( this->m <= 12) )
    {
        return true;
    } else {
        return false;
    }

}
bool Date::is_valid_day(std::stringstream & ss)
{
    ss >> this->d;
    if ( ss.fail() ) { return false; }  // string conversion unsigned int failed
    if ( ss.rdbuf()->in_avail() ) {return false ;} //string wasn't pure num 2024a
    if ( ( 1 <= this->d ) && ( this->d <= 31) )
    {
        return true;
    } else {
        return false;
    }

}

bool Date::operator<(Date const & rhs) const{
    bool result = false;
    if (this->y < rhs.y)
    { result = true; }
    else if ( (this->y == rhs.y) && (this->m < rhs.m ) )
    { result = true; }
    else if ( (this->y == rhs.y) && (this->m == rhs.m ) && (this->d < rhs.d ) )
    { result = true; }
    return (result) ;
}

bool Date::operator==(Date const & rhs) const{
    return ( (this->y == rhs.y) && (this->m == rhs.m ) && (this->d == rhs.d ) ) ;
}

std::string Date::get_d( void ) const
{
    std::stringstream ss;
    // 1. Establecer el carácter de relleno (padding character) a '0'
    ss << std::setfill('0');
    
    // 2. Establecer el ancho mínimo del campo (field width) a 2
    ss << std::setw(2); 

    // 3. Insertar el valor del día (this->m)
    ss << this->d;
    return ss.str();
}   
std::string Date::get_m( void ) const
{
    std::stringstream ss;
    // 1. Establecer el carácter de relleno (padding character) a '0'
    ss << std::setfill('0');
    
    // 2. Establecer el ancho mínimo del campo (field width) a 2
    ss << std::setw(2); 

    // 3. Insertar el valor del mes (this->m)
    ss << this->m;
    return ss.str();
}   
std::string Date::get_y( void ) const
{
    std::stringstream ss;
    ss << this->y;
    return ss.str();
}    

std::ostream & operator<<(std::ostream & os, Date const & d)
{
    os << d.get_d() << "-" << d.get_m() << "-" << d.get_y() ;
    return os;
}