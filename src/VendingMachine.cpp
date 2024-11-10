#include "VendingMachine.hpp"
#include <iostream>

VendingMachine::VendingMachine() {
    for (Cash::Denomination denom : Cash::getDenominations()) {
        m_CashBalance[denom] = 0;
    }
}

void VendingMachine::addBeverage(const Beverage& beverage) {
    m_Beverages[beverage.getName()] = std::make_shared<Beverage>(beverage);
}

void VendingMachine::removeBeverage(const std::string& name) {
    m_Beverages.erase(name);
}

void VendingMachine::displayBeverages() const {
    std::cout << "Available Beverages:" << std::endl;
    for (const auto& [name, beveragePtr] : m_Beverages) {
        std::cout << beveragePtr->getName() << " - " << beveragePtr->getPrice() << " KRW" << std::endl;
    }
}

bool VendingMachine::selectBeverage(const std::string& name) {
    auto it = m_Beverages.find(name);
    if (it != m_Beverages.end() && getTotalBalance() >= it->second->getPrice()) {
        deductBalance(it->second->getPrice());
        std::cout << "Dispensing " << name << std::endl;
        return true;
    } else {
        std::cout << "Insufficient balance or beverage not found." << std::endl;
        return false;
    }
}

void VendingMachine::addBalance(const Cash& cash) {
    m_CashBalance[cash.getDenomination()] += cash.getQuantity();
    std::cout << "Added " << cash.getQuantity() << " of " << cash.getDenomination() << " KRW" << std::endl;
}

void VendingMachine::removeBalance(const Cash& cash) {
    if (m_CashBalance[cash.getDenomination()] >= cash.getQuantity()) {
        m_CashBalance[cash.getDenomination()] -= cash.getQuantity();
        std::cout << "Removed " << cash.getQuantity() << " of " << cash.getDenomination() << " KRW" << std::endl;
    } else {
        std::cout << "Not enough cash of this denomination to remove." << std::endl;
    }
}

void VendingMachine::returnChange() {
    int totalBalance = getTotalBalance();
    std::cout << "Returning change: " << totalBalance << " KRW" << std::endl;

    for (Cash::Denomination denom : Cash::getDenominations()) {
        int count = 0;
        while (totalBalance >= denom && m_CashBalance[denom] > 0) {
            totalBalance -= denom;
            m_CashBalance[denom]--;
            count++;
        }
        if (count > 0) {
            std::cout << "Returned " << count << " of " << denom << " KRW" << std::endl;
        }
    }
}

int VendingMachine::getTotalBalance() const {
    int total = 0;
    for (const auto& [denom, count] : m_CashBalance) {
        total += denom * count;
    }
    return total;
}

void VendingMachine::deductBalance(int amount) {
    int remaining = amount;
    for (Cash::Denomination denom : Cash::getDenominations()) {
        while (remaining >= denom && m_CashBalance[denom] > 0) {
            remaining -= denom;
            m_CashBalance[denom]--;
        }
    }
}

