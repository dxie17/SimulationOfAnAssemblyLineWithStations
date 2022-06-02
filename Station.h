#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_
#include <string>
#include "Utilities.h"
namespace sdds{

    class Station{
        unsigned int m_id=0;
        std::string m_name{};
        std::string m_description{};
        unsigned int m_serialNumber = 0;
        unsigned int m_numOfItems = 0;
        static unsigned int m_widthField;
        static unsigned int id_generator;
    public:
        Station();
        Station(const std::string& oneLine);  
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}
#endif