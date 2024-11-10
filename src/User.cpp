#include "User.hpp"
#include <iostream>

User::User(VendingMachine& machine, int cardBalance) : m_VendingMachine(machine), m_Card(cardBalance) {}

bool User::arriveAtMachine() {
    if (m_VendingMachine.acquireOccupancy()) {
        std::cout << "User has acquired occupancy.\n";
        return true;
    } else {
        std::cerr << "Vending machine is currently occupied.\n";
        return false;
    }
}

void User::leaveMachine() {
    m_VendingMachine.releaseOccupancy();
    m_VendingMachine.resetTransaction();
}

bool User::insertCash(const Cash& cash) {
    return m_VendingMachine.addBalance(cash);
}

bool User::selectBeverage(const std::string& name) {
    return m_VendingMachine.selectBeverage(name);
}

bool User::selectBeverageWithCard(const std::string& name) {
    int price = m_VendingMachine.getBeveragePrice(name);
    if (m_Card.hasSufficientBalance(price)) {
        m_Card.deduct(price);
        return m_VendingMachine.selectBeverageWithCard(name, m_Card.getBalance());
    }
    std::cerr << "Insufficient card balance.\n";
    return false;
}

bool User::getChange() {
    return m_VendingMachine.returnChange();
}
