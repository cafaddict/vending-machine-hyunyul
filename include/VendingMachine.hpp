#pragma once
#include "Beverage.hpp"
#include "Cash.hpp"
#include <unordered_map>
#include <string>
#include <memory>

class VendingMachine {
private:
    std::unordered_map<std::unique_ptr<Beverage>, int> m_Beverages;
    std::unordered_map<Cash::Denomination, int> m_CashBalance;

    int getTotalBalance() const;
    void deductBalance(int amount);

public:
    VendingMachine();
    void addBeverage(std::unique_ptr<Beverage> beverage, int quantity);
    void removeBeverage(const std::string& name);
    void displayBeverages() const;
    bool selectBeverage(const std::string& name);
    void addBalance(const Cash& cash);
    void removeBalance(const Cash& cash);
    void returnChange();
};