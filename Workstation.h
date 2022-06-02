#ifndef SDDS_WORKSTATION_H_
#define SDDS_WORKSTATION_H_
#include <string>
#include <deque>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"
namespace sdds{

    extern std::deque<CustomerOrder> pending;
    extern std::deque<CustomerOrder> completed;
    extern std::deque<CustomerOrder> incomplete;

    class Workstation: public Station{
        std::deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation = nullptr;
    public:
        Workstation();
        Workstation(const std::string& str);
        Workstation(const Workstation&)=delete;
        Workstation(Workstation&&) = delete;
        Workstation&operator=(const Workstation&) = delete;
        Workstation&operator=(Workstation&&) = delete;
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station=nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);

    };
}
#endif