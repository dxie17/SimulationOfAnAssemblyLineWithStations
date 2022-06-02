#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <memory>
#include "LineManager.h"

using namespace std;
namespace sdds{

    LineManager::LineManager() {}

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
        m_cntCustomerOrder = pending.size();
        fstream fin(file);
        if (!fin)
            throw string("Cannot open the file [") + file + "]";
        else {
            string oneLine = "";
            while (getline(fin, oneLine)) {
                if ((oneLine.find_first_of('|') == string::npos)) {
                    for_each(stations.cbegin(), stations.cend(), [&](Workstation *w) {
                        if (w->getItemName() == oneLine) {
                            activeLine.push_back(w);
                            activeLine.back()->setNextStation();
                        }                    
                    });
                }   
                else {
                    string firstPart = oneLine.substr(0, oneLine.find_first_of('|'));
                    string secondPart= oneLine.erase(0, oneLine.find_first_of('|') + 1);
                    for_each(stations.cbegin(), stations.cend(), [&](Workstation* w) {  
                        if (w->getItemName() == firstPart) {
                            activeLine.push_back(w);
                            for_each(stations.cbegin(), stations.cend(), [&](Workstation* w) {
                                if (w->getItemName() == secondPart)
                                    activeLine.back()->setNextStation(w);
                            });
                        };
                    });
                }
                oneLine = "";
            }
            fin.close();
            m_firstStation = activeLine.front();
        }
    }

    void LineManager::linkStations(){
        std::vector<Workstation*> temp{};
        if(m_firstStation)
            temp.push_back(m_firstStation);
        size_t cnt = 0u;
        while (cnt < activeLine.size() - 1) {
            if (temp[cnt]->getNextStation()) {
                for (auto i = 0u; i < activeLine.size(); i++) {
                    if (temp[cnt]->getNextStation()->getItemName() == activeLine[i]->getItemName()) {
                        temp.push_back(activeLine[i]);
                        cnt++;
                        i = activeLine.size();
                    }
                }
            }
            else
                cnt = activeLine.size();
        }
        activeLine = move(temp);
    }

    bool LineManager::run(std::ostream& os){
        static unsigned int count = 0;
        count++;
        os << "Line Manager Iteration: " << count << endl;
        if (pending.size()) {
            *activeLine.front() += move(pending.front());
            pending.pop_front();
        }
        for (auto i = 0u; i < activeLine.size(); i++) {
            activeLine[i]->fill(os);
        }
        for (auto i = 0u; i < activeLine.size(); i++) {
            activeLine[i]->attemptToMoveOrder();
        }
        return m_cntCustomerOrder == completed.size()+incomplete.size();
    }

    void LineManager::display(std::ostream& os) const{
        if (activeLine.size()) {
            for (auto i = 0u; i < activeLine.size(); i++)
                activeLine[i]->Workstation::display(os);
        }
    }
}