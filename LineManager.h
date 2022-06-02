#ifndef SDDS_LINEMANAGER_H_
#define SDDS_LINEMANAGER_H_
#include <string>
#include <vector>
#include "Workstation.h"
#include "Utilities.h"

namespace sdds{

    class LineManager{
        std::vector<Workstation*> activeLine{};
        size_t m_cntCustomerOrder=0;
        Workstation* m_firstStation=nullptr;
    public:
        LineManager();
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void linkStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}
#endif