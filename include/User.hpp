#pragma once

#include "VendingMachine.hpp"

class User {
private:
    VendingMachine& m_VendingMachine;

public:
    User(VendingMachine& machine) : m_VendingMachine(machine) {}

    bool insertCash(const Cash& cash);
    bool selectBeverage(const std::string& name); // Changed return type to bool
    void getChange();
};
