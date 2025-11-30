#include "BitcoinExchange.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>

BitcoinExchange::BitcoinExchange( void ): data()
{}
BitcoinExchange::~BitcoinExchange( void )
{}
BitcoinExchange::BitcoinExchange( BitcoinExchange const & other )
{
    this->data = other.data;
}        
BitcoinExchange & BitcoinExchange::operator=( BitcoinExchange const & other )
{
    if (this != &other)
    {
        this->data = other.data ;
    }
    return *this;
}
BitcoinExchange::BitcoinExchange( std::string filename )
{
    std::ifstream fd(filename.c_str());
    if (!fd.is_open())
    {
        throw std::runtime_error("Error opening the " + filename + " file.");
        return;
    }
    std::string linea;
    std::getline(fd, linea);
    while (std::getline(fd, linea))
    {
        std::istringstream ss(linea);
        std::string date;
        std::string value;
        std::getline(std::getline(ss, date, ','), value);
        std::stringstream ss_tof( ltrim( rtrim( value ) ) );
        float fvalue;
        if (value.find('.') != std::string::npos)
            treat_as_f(ss_tof, &fvalue);
        else
            treat_as_i(ss_tof, &fvalue);
        //this->data.insert( {Date(date), fvalue} );
        
        if (fvalue != 0)
        {
            this->data[Date(date)] =  fvalue;        
        } else {
            //std::cout << Date(date) << " - " << fvalue << " Excluded from DB" << std::endl;
        }
    }

    fd.close();
}        

std::map<Date, float>::iterator  BitcoinExchange::begin(void)
{ return this->data.begin();}

std::map<Date, float>::iterator  BitcoinExchange::end(void)
{ return this->data.end();}


float BitcoinExchange::getChange( Date const & day) const
{
    // Search the first element bigger than the one searched
    std::map<Date, float>::const_iterator it = this->data.upper_bound(day);

    if ( it != this->data.begin() ) // it is not the first one
    {
        --it;   // this point to the lower or equal to the one searched
    }
    return it->second;
}
std::string& BitcoinExchange::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// Elimina el espacio en blanco al final (right trim)
std::string& BitcoinExchange::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

void BitcoinExchange::treat_as_f(std::stringstream & ss, float *value)
{
    double aux;
    std::stringstream & ss_back = ss;
    ss >> aux;
    if (ss.fail())
    {
        std::cout << "Error: Bad input." ;
        *value = 0.0;
        return ;
    }
    if (ss.rdbuf()->in_avail())
    {
        std::cout << "Error: Value " << ss_back.str() << " does not represent a integer or a float." << std::endl;   
        *value = 0.0;
        return ;
    }
    if (aux < 0)
    {
        std::cout << "Error: Value " << ss_back.str() << " not a positive number." << std::endl;
        *value = 0.0;
        return ;           
    }
    if ( (double)std::numeric_limits<float>::max() < aux )
    {
        std::cout << "Error: " << ss_back.str() << " too large number." << std::endl;
        *value = 0.0;
        return ;             
    }
    *value = static_cast<float>(aux);
}

void BitcoinExchange::treat_as_i(std::stringstream & ss, float *value)
{
    unsigned int aux;
    std::stringstream & ss_back = ss;
    if ( (ss.str().size() == 10 ) && (ss.str() > "2147483647") )
    {
        std::cout << "Error: too large number." ;
        *value = 0.0;
        return ;             
    }    
    ss >> aux;
    if (ss.fail())
    {
        std::cout << "Error: Bad input";
        *value = 0.0;
        return ;
    }
    if (ss.rdbuf()->in_avail())
    {
        std::cout << "Error: Value " << ss_back.str() << " does not represent a integer or a float." << std::endl;   
        *value = 0.0;
        return ;
    }
    if (aux < 0)
    {
        std::cout << "Error: Value " << ss_back.str() << " not a positive number." << std::endl;
        *value = 0.0;
        return ;           
    }
    if ( std::numeric_limits<unsigned int>::max() < aux )
    {
        std::cout << "Error: " << ss_back.str() << " too large number." << std::endl;
        *value = 0.0;
        return ;             
    }
    *value = static_cast<float>(aux); 
}
