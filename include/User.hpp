#pragma once

#include "VendingMachine.hpp"
#include "Cash.hpp"
#include "Card.hpp"
#include <string>

class User {
private:
    VendingMachine& m_VendingMachine;
    Card m_Card;

public:
    User(VendingMachine& machine, int cardBalance);

    bool arriveAtMachine();
    void leaveMachine();
    bool insertCash(const Cash& cash);
    bool selectBeverage(const std::string& name);
    bool selectBeverageWithCard(const std::string& name);
    bool getChange();
};
