#include "Card.hpp"

Card::Card(int initialBalance) : m_Balance(initialBalance) {
    if (initialBalance < 0) {
        throw std::invalid_argument("Initial balance cannot be negative");
    }
}

int Card::getBalance() const {
    return m_Balance;
}

bool Card::hasSufficientBalance(int amount) const {
    return m_Balance >= amount;
}

void Card::deduct(int amount) {
    if (amount > m_Balance) {
        throw std::runtime_error("Insufficient card balance");
    }
    m_Balance -= amount;
}
