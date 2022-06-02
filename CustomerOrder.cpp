#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;
namespace sdds
{
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder() {}

    CustomerOrder::CustomerOrder(const std::string& str) {
        Utilities utility;
        size_t nextPosition = 0;
        bool exist = true;
        if (str != "") {
            m_name = utility.extractToken(str, nextPosition, exist);
            if (exist) {
                m_product = utility.extractToken(str, nextPosition, exist);
                string temp = str.substr(nextPosition,str.length()- nextPosition+1);
                size_t count = 0;
                for (size_t i = 0; i < temp.length(); i++) {
                    if (temp[i] == utility.getDelimiter())
                        count++;
                }
                m_lstItem = new Item * [count+1];
                while (exist) {
                    string temp = utility.extractToken(str, nextPosition, exist);
                    m_lstItem[m_cntItem] = new Item(temp);
                    m_cntItem++;
                }
            }
        }
        CustomerOrder::m_widthField < utility.getFieldWidth() ? CustomerOrder::m_widthField = utility.getFieldWidth()
            : CustomerOrder::m_widthField;
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& co){
        throw "Not Allowed";
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept{
        * this = move(co);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&&co) noexcept{
        if (this != &co) {
            for (size_t i = 0; i < m_cntItem; i++)
                delete m_lstItem[i];
            delete[] m_lstItem;
            m_name = co.m_name;
            m_product = co.m_product;
            m_cntItem = co.m_cntItem;
            m_lstItem = move(co.m_lstItem);
            co.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder(){
        if (m_lstItem) {
            for (size_t i = 0; i < m_cntItem; i++)
                delete m_lstItem[i];  
            delete[] m_lstItem;
        }
    }

    bool CustomerOrder::isFilled() const{
        bool isTrue = true;
        for (size_t i = 0; isTrue && i < m_cntItem; i++)
            isTrue = isTrue && m_lstItem[i]->m_isFilled;
        return isTrue;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const{
        bool isTrue = true;
        for (size_t i = 0; isTrue && i < m_cntItem; i++) {
            if(itemName== m_lstItem[i]->m_itemName)
                isTrue = isTrue && m_lstItem[i]->m_isFilled;
        }
        return isTrue;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os){
        for (size_t i = 0; i < m_cntItem; i++) {
  
            if (!m_lstItem[i]->m_isFilled&& station.getItemName() == m_lstItem[i]->m_itemName) {
       
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product
                        << " [" << m_lstItem[i]->m_itemName << "]" << endl;
                } 
                else
                    os << "    Unable to fill " << m_name << ", " << m_product 
                    << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }  
        }
    }

    void CustomerOrder::display(std::ostream& os) const{
        os << m_name << " - " << m_product << endl;
        for (size_t i = 0; i < m_cntItem; i++)
            os << "[" << setw(6) << right << setfill('0') << m_lstItem[i]->m_serialNumber << "] "
            << setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName
            << " - " << (m_lstItem[i]->m_serialNumber ? "FILLED" : "TO BE FILLED") << endl;
    }
}