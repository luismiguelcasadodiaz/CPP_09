#ifndef BITCOINEXCHANGE_HH
#define BITCOINEXCHANGE_HH
#include <map>
#include <string>
#include "Date.hpp"


class BitcoinExchange
{
    private:
        std::map<Date, float> data;
    public:
        BitcoinExchange( void );
        ~BitcoinExchange( void );
        BitcoinExchange( BitcoinExchange const & other );        
        BitcoinExchange & operator=( BitcoinExchange const & other );
        BitcoinExchange( std::string filename );

        std::map<Date, float>::iterator  begin(void);
        std::map<Date, float>::iterator  end(void);        
        float getChange( Date const & day) const;
        std::string& ltrim(std::string& s);
        std::string& rtrim(std::string& s);
        void treat_as_f(std::stringstream & ss, float *value);
        void treat_as_i(std::stringstream & ss, float *value);
};
#endif