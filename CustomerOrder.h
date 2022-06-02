#ifndef SDDS_CUSTOMERORDER_H_
#define SDDS_CUSTOMERORDER_H_
#include <string>
#include "Station.h"
namespace sdds{

    struct Item{
        std::string m_itemName;
        size_t m_serialNumber{ 0 };
        bool m_isFilled{ false };
        Item(const std::string& src) : m_itemName(src) {};
        Item(){};
    };

    class CustomerOrder{
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem=0;
        Item** m_lstItem=nullptr;
        static size_t m_widthField;
    public:
        CustomerOrder();
        CustomerOrder(const std::string& str);
        CustomerOrder(const CustomerOrder& co);
        CustomerOrder& operator=(const CustomerOrder&) = delete;
        CustomerOrder(CustomerOrder&&co)noexcept;
        CustomerOrder& operator=(CustomerOrder&&co) noexcept;
        ~CustomerOrder();
        bool isFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}
#endif