#include "Admin.hpp"
#include <iostream>

void Admin::addBeverage(const std::string& name, int price) {
    m_VendingMachine.addBeverage(Beverage(name, price));
}

void Admin::removeBeverage(const std::string& name) {
    m_VendingMachine.removeBeverage(name);
}

void Admin::addCash(const Cash& cash) {
    m_VendingMachine.addBalance(cash);
}

void Admin::removeCash(const Cash& cash) {
    m_VendingMachine.removeBalance(cash);
}

