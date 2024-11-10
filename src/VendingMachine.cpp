#include "VendingMachine.hpp"
#include <iostream>
#include <memory>

VendingMachine::VendingMachine() {
    for (Cash::Denomination denom : Cash::getDenominations()) {
        m_CashBalance[denom] = 0;
    }
}

void VendingMachine::addBeverage(std::unique_ptr<Beverage> beverage, int quantity) {
    m_Beverages[std::move(beverage)] = quantity;
}

void VendingMachine::removeBeverage(const std::string& name) {
    for (auto it = m_Beverages.begin(); it != m_Beverages.end(); ++it) {
        if (it->first->getName() == name) {
            m_Beverages.erase(it);
            return;
        }
    }
    std::cout << "Beverage " << name << " not found." << std::endl;
}

void VendingMachine::displayBeverages() const {
    std::cout << "Available Beverages:" << std::endl;
    for (const auto& [beveragePtr, quantity] : m_Beverages) {
        std::cout << beveragePtr->getName() << " - " << beveragePtr->getPrice() << " KRW, Quantity: " << quantity << std::endl;
    }
}

bool VendingMachine::selectBeverage(const std::string& name) {
    for (auto& [beveragePtr, quantity] : m_Beverages) {
        if (beveragePtr->getName() == name) {
            if (getTotalBalance() >= beveragePtr->getPrice()) {
                deductBalance(beveragePtr->getPrice());
                quantity--;
                std::cout << "Dispensing " << name << std::endl;
                if (quantity <= 0) m_Beverages.erase(beveragePtr); // Remove if quantity is zero
                return true;
            } else {
                std::cout << "Insufficient balance for " << name << std::endl;
                return false;
            }
        }
    }
    std::cout << "Beverage " << name << " not found." << std::endl;
    return false;
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
