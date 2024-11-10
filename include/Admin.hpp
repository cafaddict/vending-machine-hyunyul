#pragma once

#include "VendingMachine.hpp"
#include "Cash.hpp"
#include <string>

class Admin {
private:
    VendingMachine& m_VendingMachine;

public:
    Admin(VendingMachine& machine);

    bool arriveAtMachine();
    void leaveMachine();
    bool addBeverage(const std::string& name, int price, int quantity);
    bool removeBeverage(const std::string& name);
    bool addCash(const Cash& cash);
    bool removeCash(const Cash& cash);
};
