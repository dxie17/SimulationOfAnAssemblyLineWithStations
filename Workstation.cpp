#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Workstation.h"
#include "CustomerOrder.h"

using namespace std;
namespace sdds{

    std::deque<CustomerOrder> pending;
    std::deque<CustomerOrder> completed;
    std::deque<CustomerOrder> incomplete;

    Workstation::Workstation() {}

    Workstation::Workstation(const std::string& str):Station(str) {
    }

    void Workstation::fill(std::ostream& os) {
        if (m_orders.size())
            m_orders.front().fillItem(*this, os);  
    }

    bool Workstation::attemptToMoveOrder() {
        bool isMoved = false;
        if (m_orders.size()) {
            if (m_orders.front().isFilled()) {
                isMoved = true;
                if (getNextStation())
                    *m_pNextStation += move(m_orders.front());
                else
                    completed.push_back(move(m_orders.front()));
                m_orders.pop_front();
            }
            else if (m_orders.front().isItemFilled(getItemName())
                || !(m_orders.front().isItemFilled(getItemName())||getQuantity())) {
                isMoved = true;
                if (getNextStation())
                    *m_pNextStation += std::move(m_orders.front());
                else
                    incomplete.push_back(move(m_orders.front()));
                m_orders.pop_front();
            }
      }
        return isMoved;
    }

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(move(newOrder));
        return *this;
    }

    void Workstation::display(std::ostream& os) const {
        if (getNextStation())
            os << getItemName() <<" --> " << getNextStation()->getItemName() << endl;
        else if(!getNextStation())
            os << getItemName() << " --> End of Line"<<endl;
    }
}