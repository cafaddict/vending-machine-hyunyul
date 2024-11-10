#pragma once
#include <stdexcept>

class Card {
private:
    int m_Balance;

public:
    explicit Card(int initialBalance);

    int getBalance() const;
    bool hasSufficientBalance(int amount) const;
    void deduct(int amount);
};
