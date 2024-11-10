// User.cpp
#include "User.hpp"

bool User::insertCash(const Cash& cash) {
    m_VendingMachine.addBalance(cash);
    return true; // You may adjust this based on whether the insertion was successful
}

bool User::selectBeverage(const std::string& name) {
    return m_VendingMachine.selectBeverage(name); // Return the bool value
}

void User::getChange() {
    m_VendingMachine.returnChange();
}
