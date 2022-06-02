#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Station.h"

using namespace std;
namespace sdds{

    unsigned int Station::m_widthField = 0;
    unsigned int Station::id_generator = 0;

    Station::Station() {
        id_generator++;
        m_id = id_generator;
    }

    Station::Station(const std::string& oneLine){
        Utilities utility;
        size_t nextPosition = 0;
        bool exist = true;
        if (oneLine != "") {
            m_name = utility.extractToken(oneLine, nextPosition, exist);
            if (exist) {
                m_serialNumber = stoi(utility.extractToken(oneLine, nextPosition, exist));
                if (exist) {
                    m_numOfItems = stoi(utility.extractToken(oneLine, nextPosition, exist));
                    m_widthField < utility.getFieldWidth()? m_widthField= utility.getFieldWidth(): m_widthField;
                    if (exist)
                        m_description = utility.extractToken(oneLine, nextPosition, exist);
                }
            }
        }
        id_generator++;
        m_id = id_generator;
    }

    const std::string& Station::getItemName() const{
        return m_name;
    }

    size_t Station::getNextSerialNumber(){
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const{
        return m_numOfItems;
    }

    void Station::updateQuantity(){
        m_numOfItems > 0 ? m_numOfItems-- : m_numOfItems;
    }

    void Station::display(std::ostream& os, bool full) const{
        if (full)
            os << "[" << setw(3)<<right<<setfill('0') << m_id << "]" <<
            " Item: " << setw(m_widthField) << setfill(' ') <<left<< m_name
            << " [" << setw(6) << setfill('0') <<right<< m_serialNumber << "]"
            <<" Quantity: " << setw(m_widthField) << setfill(' ') <<left<< m_numOfItems
            <<" Description: "<<m_description << endl;
        else
            os << "[" << setw(3) <<right<< setfill('0') << m_id << "]" <<
            " Item: " << setw(m_widthField) << setfill(' ') << left << m_name
            << " [" << setw(6) << setfill('0') <<right<< m_serialNumber << "]" << endl;
    }
}