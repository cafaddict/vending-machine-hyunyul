#pragma once
#include <string>

class Beverage {
    public:
    //NOTE: For now, Beverage types are limited to Cola, Water, and Coffee
    enum Type {
        Cola = 1100,
        Water = 600,
        Coffee = 700
    };
private:
    std::string m_Name;
    int m_Price;

public:
    Type beverageNameToType(const std::string& name) {
        if(name == "Cola") {
            return Type::Cola;
        } else if(name == "Water") {
            return Type::Water;
        } else if(name == "Coffee") {
            return Type::Coffee;
        } else {
            throw std::invalid_argument("Invalid beverage name");
        }
    }

    Beverage(const std::string& beverageName, int beveragePrice) 
        : m_Name(beverageName), m_Price(beveragePrice) {
            if(!(beverageName == "Cola" || beverageName == "Water" || beverageName == "Coffee")) {
                throw std::invalid_argument("Invalid beverage name: " + beverageName);
            }
            Type type = beverageNameToType(beverageName);
            if(beveragePrice != type) {
                throw std::invalid_argument("Invalid beverage price");
            }
        }

    std::string getName() const { return m_Name; }
    int getPrice() const { return m_Price; }

    void setPrice(int newPrice) { m_Price = newPrice; }
};