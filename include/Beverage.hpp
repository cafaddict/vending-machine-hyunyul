#pragma once
#include <string>

class Beverage {
private:
    std::string m_Name;
    int m_Price;

public:
    Beverage(const std::string& beverageName, int beveragePrice) 
        : m_Name(beverageName), m_Price(beveragePrice) {}

    std::string getName() const { return m_Name; }
    int getPrice() const { return m_Price; }

    void setPrice(int newPrice) { m_Price = newPrice; }
};