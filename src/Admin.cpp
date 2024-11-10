#include "Admin.hpp"
#include <iostream>
#include <memory>

Admin::Admin(VendingMachine& machine) : m_VendingMachine(machine) {}

bool Admin::arriveAtMachine() {
    if (m_VendingMachine.acquireOccupancy()) {
        std::cout << "Admin has acquired occupancy of the vending machine.\n";
        return true;
    } else {
        std::cerr << "Vending machine is currently occupied.\n";
        return false;
    }
}

void Admin::leaveMachine() {
    std::cout << "Admin is leaving the vending machine.\n";
    m_VendingMachine.resetTransaction();
    m_VendingMachine.releaseOccupancy();
}

bool Admin::addBeverage(const std::string& name, int price, int quantity) {
    auto beverage = std::make_unique<Beverage>(name, price);
    if (m_VendingMachine.addBeverage(std::move(beverage), quantity)) {
        std::cout << "Added " << quantity << " of " << name << " at " << price << " KRW each.\n";
        return true;
    }
    return false;
}

bool Admin::removeBeverage(const std::string& name) {
    if (m_VendingMachine.removeBeverage(name)) {
        std::cout << "Removed beverage: " << name << std::endl;
        return true;
    }
    return false;
}

bool Admin::addCash(const Cash& cash) {
    if (m_VendingMachine.addBalance(cash)) {
        std::cout << "Added " << cash.getQuantity() << " of " << static_cast<int>(cash.getDenomination()) << " KRW.\n";
        return true;
    }
    return false;
}

bool Admin::removeCash(const Cash& cash) {
    if (m_VendingMachine.removeCash(cash)) {
        return true;
    } else {
        std::cerr << "Unable to remove specified cash." << std::endl;
        return false;
    }
}
