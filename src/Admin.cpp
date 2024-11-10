#include "Admin.hpp"
#include "Beverage.hpp"

Admin::Admin(VendingMachine& machine) : m_VendingMachine(machine) {}

void Admin::addBeverage(const std::string& name, int price, int quantity) {
    auto beverage = std::make_unique<Beverage>(name, price);
    m_VendingMachine.addBeverage(std::move(beverage), quantity);
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
