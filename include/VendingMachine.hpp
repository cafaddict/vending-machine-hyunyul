#pragma once

#include "Beverage.hpp"
#include "Cash.hpp"
#include <map>
#include <memory>
#include <unordered_map>

class VendingMachine {
private:
    std::map<Cash::Denomination, int> m_CashBalance; // Cash available in the machine
    std::unordered_map<std::unique_ptr<Beverage>, int> m_Beverages; // Beverages and their stock
    int m_UserInsertedAmount = 0; // Tracks the user's inserted amount for each transaction
    int m_SelectedItemPrice = 0;   // Price of the selected item
    bool m_IsOccupied = false;     // Tracks if the machine is in use


public:
    VendingMachine();

    // Occupancy control
    bool acquireOccupancy();
    void releaseOccupancy();
    void resetTransaction(); // Resets transaction-related data

    // Beverage and cash management
    bool addBeverage(std::unique_ptr<Beverage> beverage, int quantity);
    bool removeBeverage(const std::string& name);
    void displayBeverages() const;

    // Payment methods
    bool selectBeverage(const std::string& name);                // Cash payment
    bool selectBeverageWithCard(const std::string& name, int cardBalance); // Card payment

    bool addBalance(const Cash& cash); // Add cash from user
    bool canReturnExactChange(int amount) const; // Check if exact change is possible
    bool returnChange();               // Return change to the user
    bool removeCash(const Cash& cash); // New method for cash removal
    int getTotalCash() const;          // Accessor for total cash in the machine

    // Accessor for beverage price
    int getBeveragePrice(const std::string& name) const;
    int getBevQuantity(const std::string& name) const;
    
private:
    void deductBalance(int amount);    // Deduct balance from machine cash reserves
};
