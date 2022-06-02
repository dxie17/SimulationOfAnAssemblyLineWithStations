#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Utilities.h"
using namespace std;

namespace sdds{

    char Utilities::m_delimiter = '\n';

    Utilities::Utilities() {
        m_widthField = 1;
        
    }

    void Utilities::setFieldWidth(size_t newWidth){
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const{
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        string temp = "";
        if (str != "") {
            temp = str.substr(next_pos, str.length() - next_pos+1);
            if (temp.find_first_of(getDelimiter()) != string::npos) {
                if (temp[0] == getDelimiter()) {
                    more = false;
                    throw "ERROR: No token.";
                } 
                else {
                    temp = temp.substr(0, temp.find_first_of(getDelimiter()));
                    more = true;
                    next_pos = next_pos + temp.length()+1;
                }
            }
            else
                more = false;
        }
        temp.length() > m_widthField ? m_widthField = temp.length() : m_widthField;
        return temp;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}