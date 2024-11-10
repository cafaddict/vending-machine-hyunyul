#pragma once
#include "VendingMachine.hpp"

class Admin {
private:
    VendingMachine& m_VendingMachine;

public:
    Admin(VendingMachine& machine) : m_VendingMachine(machine) {}

    void addBeverage(const std::string& name, int price);
    void removeBeverage(const std::string& name);
    void addCash(const Cash& cash);
    void removeCash(const Cash& cash);
};


