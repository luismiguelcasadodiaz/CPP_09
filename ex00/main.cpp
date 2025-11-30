#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <climits>
#include <iomanip>
#include <limits>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include "Date.hpp"
#include "BitcoinExchange.hpp"

/*
std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// Elimina el espacio en blanco al final (right trim)
std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

void treat_as_f(std::stringstream & ss, float *value)
{
    double aux;
    ss >> aux;
    if (ss.fail())
    {
        std::cout << "Error: Empty Value string." << std::endl;
        *value = 0.0;
        return ;
    }
    if (ss.rdbuf()->in_avail())
    {
        std::cout << "Error: Value string does not represent a integer or a float." << std::endl;   
        *value = 0.0;
        return ;
    }
    if (aux < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        *value = 0.0;
        return ;           
    }
    if ( (double)std::numeric_limits<float>::max() < aux )
    {
        std::cout << "Error: too large number." << std::endl;
        *value = 0.0;
        return ;             
    }
    *value = static_cast<float>(aux);
}

void treat_as_i(std::stringstream & ss, float *value)
{
    unsigned int aux;
    if (ss.str() > "2147483647")
    {
        std::cout << "Error: too large number." << std::endl;
        *value = 0.0;
        return ;             
    }    
    ss >> aux;
    if (ss.fail())
    {
        std::cout << "Error: Empty Value string." << std::endl;
        *value = 0.0;
        return ;
    }
    if (ss.rdbuf()->in_avail())
    {
        std::cout << "Error: Value string does not represent a integer or a float." << std::endl;   
        *value = 0.0;
        return ;
    }
    if (aux < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        *value = 0.0;
        return ;           
    }
    if ( std::numeric_limits<unsigned int>::max() < aux )
    {
        std::cout << "Error: too large number." << std::endl;
        *value = 0.0;
        return ;             
    }
    *value = static_cast<float>(aux); 
}
*/
void showme(const std::pair<Date, float>& p) {
    std::cout << p.first << " -> " << p.second << std::endl;
}

int main(int argc , char **argv)
{
    try
    {
        BitcoinExchange bex("data.csv");
        if ( argc != 2)
        {
            std::cout << "Error: could not open file." << std::endl;
            return (0);
        }

        std::ifstream fd(argv[1]);
        if (!fd.is_open())
        {
            std::cout << "Error opening the " << argv[1] << " file." ;
            return (0);
        }
        std::string linea;
        std::getline(fd, linea); // Jump Header
        while (std::getline(fd, linea))
        {
            std::istringstream ss(linea);
            std::string date;
            std::string value;
            
            std::getline(std::getline(ss, date, '|'), value);
            std::stringstream ss_tof( bex.ltrim( bex.rtrim( value ) ) );
            float fvalue;
            if (value.find('-') != std::string::npos)
            {
                std::cout << "Error: not a positive number." << std::endl;
            }
            else 
            {
                if (value.find('.') != std::string::npos)
                bex.treat_as_f(ss_tof, &fvalue);
                    else
                bex.treat_as_i(ss_tof, &fvalue);
                if (fvalue != 0.0)
                {
                std::cout << date << " => " << fvalue << " = " << fvalue * bex.getChange(Date(date)) << std::endl;
                } else {
                    std::cout << " => " << date << std::endl;
                }
            }
        }

        fd.close();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
 }

 /*
    Date d1("2022-03-17");
    Date d2("2020-12-11");
    if (d1 < d2)
    {
        std::cout << d1 << " < " << d2 << std::endl;
    } else{
        std::cout << d1 << " >= " << d2 << std::endl;        
    }
    //std::for_each(bex.begin(), bex.end(), showme);
    float r = bex.getChange(d1);
    std::cout << "????" << d1 << " => " <<  r << std::endl;
 */
