#pragma once
#include "VendingMachine.hpp"
#include <memory>

class Admin {
private:
    VendingMachine& m_VendingMachine;

public:
    Admin(VendingMachine& machine);

    void addBeverage(const std::string& name, int price, int quantity);
    void removeBeverage(const std::string& name);

    void addCash(const Cash& cash);
    void removeCash(const Cash& cash);
};


