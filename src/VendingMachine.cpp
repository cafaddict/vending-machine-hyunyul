#include "VendingMachine.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>

VendingMachine::VendingMachine() {
    for (Cash::Denomination denom : Cash::getDenominations()) {
        m_CashBalance[denom] = 0;
    }
}

// Occupancy control
bool VendingMachine::acquireOccupancy() {
    if (m_IsOccupied ) {
        return false;
    }

    if (m_OutOfOrder) {
        std::cerr << "Vending machine is out of order." << std::endl;
        return false;
    }

    m_IsOccupied = true;
    return true;
}

void VendingMachine::releaseOccupancy() {
    m_IsOccupied = false;
}

// Reset transaction state
void VendingMachine::resetTransaction() {
    m_UserInsertedAmount = 0;
    m_SelectedItemPrice = 0;
}

// Add beverage with quantity
bool VendingMachine::addBeverage(std::unique_ptr<Beverage> beverage, int quantity) {
    if (!beverage) {
        std::cerr << "Invalid beverage." << std::endl;
        return false;
    }

    // Check if beverage already exists in the inventory
    for (auto& [existingBeverage, existingQuantity] : m_Beverages) {
        if (existingBeverage->getName() == beverage->getName()) {
            existingQuantity += quantity;  // Add to existing quantity
            return true;
        }
    }

    // If beverage doesn't exist, add it to the inventory
    m_Beverages[std::move(beverage)] = quantity;
    return true;
}


// Remove beverage by name
bool VendingMachine::removeBeverage(const std::string& name) {
    for (auto it = m_Beverages.begin(); it != m_Beverages.end(); ++it) {
        if (it->first->getName() == name) {
            m_Beverages.erase(it);
            return true;
        }
    }
    std::cerr << "Beverage " << name << " not found." << std::endl;
    return false;
}

// Display available beverages and quantities
void VendingMachine::displayBeverages() const {
    std::cout << "Available Beverages:" << std::endl;
    for (const auto& [beveragePtr, quantity] : m_Beverages) {
        std::cout << beveragePtr->getName() << " - " << beveragePtr->getPrice()
                  << " KRW, Quantity: " << quantity << std::endl;
    }
}

// Select beverage with cash
bool VendingMachine::selectBeverage(const std::string& name) {
    for (auto& [beverage, quantity] : m_Beverages) {
        if (beverage->getName() == name) {
            if (quantity <= 0) {
                std::cerr << "Sorry, " << name << " is out of stock." << std::endl;
                return false;
            }
            if (m_UserInsertedAmount >= beverage->getPrice()) {
                m_SelectedItemPrice = beverage->getPrice();
                m_UserInsertedAmount -= m_SelectedItemPrice;
                quantity--; // Decrement quantity
                std::cout << "Dispensing " << name << std::endl;
                return true;
            } else {
                std::cerr << "Insufficient cash balance for " << name << std::endl;
                return false;
            }
        }
    }
    std::cerr << "Beverage " << name << " not found." << std::endl;
    return false;
}

// Select beverage with card
bool VendingMachine::selectBeverageWithCard(const std::string& name, int cardBalance) {
    for (auto& [beverage, quantity] : m_Beverages) {
        if (beverage->getName() == name) {
            if (quantity <= 0) {
                std::cerr << "Sorry, " << name << " is out of stock." << std::endl;
                return false;
            }
            if (cardBalance >= beverage->getPrice()) {
                m_SelectedItemPrice = beverage->getPrice();
                quantity--; // Decrement quantity
                std::cout << "Dispensing " << name << " (Paid with Card)" << std::endl;
                return true;
            } else {
                std::cerr << "Insufficient card balance for " << name << std::endl;
                return false;
            }
        }
    }
    std::cerr << "Beverage " << name << " not found." << std::endl;
    return false;
}

// Add user cash
bool VendingMachine::addBalance(const Cash& cash) {
    m_UserInsertedAmount += cash.getQuantity() * cash.getDenomination();
    m_CashBalance[cash.getDenomination()] += cash.getQuantity();
    return true;
}

// Check if exact change is possible
bool VendingMachine::canReturnExactChange(int amount) const {
    int change = amount;
    for (auto it = m_CashBalance.rbegin(); it != m_CashBalance.rend(); ++it) {
        Cash::Denomination denom = it->first;
        int count = it->second;

        int numNotes = std::min(change / denom, count);
        change -= numNotes * denom;
        if (change == 0) break;
    }
    return change == 0;
}

// Return change
bool VendingMachine::returnChange() {
    int change = m_UserInsertedAmount;
    std::cout << "Returning change of " << change << " KRW." << std::endl;
    if (!canReturnExactChange(change)) {
        std::cerr << "Unable to provide exact change." << std::endl;
        std::cerr << "Please contact the admin for a refund." << std::endl;
        resetTransaction(); // Reset for next transaction
        return false;
    }
    std::map<Cash::Denomination, int> changeToGive;

    for (auto it = m_CashBalance.rbegin(); it != m_CashBalance.rend(); ++it) {
        Cash::Denomination denom = it->first;
        int count = it->second;

        if (change >= denom) {
            int numNotes = std::min(change / denom, count);
            change -= numNotes * denom;
            changeToGive[denom] = numNotes;
        }
    }

    for (const auto& [denom, numNotes] : changeToGive) {
        m_CashBalance[denom] -= numNotes;
        if (numNotes > 0) {
            std::cout << "Returned " << numNotes << " of " << denom << " KRW" << std::endl;
        }
    }
    
    resetTransaction(); // Reset for next transaction
    return true;
    
}

// Remove specific cash denomination
bool VendingMachine::removeCash(const Cash& cash) {
    Cash::Denomination denom = cash.getDenomination();
    int quantity = cash.getQuantity();

    if (m_CashBalance[denom] >= quantity) {
        m_CashBalance[denom] -= quantity; // Deduct cash directly from the denomination
        std::cout << "Removed " << quantity << " of " << denom << " KRW.\n";
        return true;
    } else {
        std::cerr << "Not enough cash of this denomination to remove." << std::endl;
        return false;
    }
}

// Private helper to deduct an amount from the total balance
void VendingMachine::deductBalance(int amount) {
    for (auto it = m_CashBalance.rbegin(); it != m_CashBalance.rend(); ++it) {
        Cash::Denomination denom = it->first;
        int denomValue = static_cast<int>(denom);

        while (amount >= denomValue && it->second > 0) {
            amount -= denomValue;
            --it->second;
        }
        if (amount == 0) break;
    }
}

// Get the price of a specific beverage by name
int VendingMachine::getBeveragePrice(const std::string& name) const {
    for (const auto& [beveragePtr, quantity] : m_Beverages) {
        if (beveragePtr->getName() == name) {
            return beveragePtr->getPrice();
        }
    }
    std::cerr << "Beverage not found" << std::endl;
    return 0;
    // throw std::runtime_error("Beverage not found");
}

// Get the quantity of a specific beverage by name
int VendingMachine::getBevQuantity(const std::string& name) const {
    for (const auto& [beveragePtr, quantity] : m_Beverages) {
        if (beveragePtr->getName() == name) {
            return quantity;
        }
    }
    std::cerr << "Beverage not found" << std::endl;
    return 0;
    // throw std::runtime_error("Beverage not found");
}
