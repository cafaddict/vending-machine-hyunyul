#include "Cash.hpp"
#include <stdexcept>

Cash::Cash(Denomination denom, int quantity) : m_Denomination(denom), m_Quantity(quantity) {
    if (quantity < 0) {
        throw std::invalid_argument("Quantity cannot be negative");
    }
}

Cash::Denomination Cash::getDenomination() const {
    return m_Denomination;
}

int Cash::getQuantity() const {
    return m_Quantity;
}

bool Cash::isValidDenomination(int amount) {
    return amount == 100 || amount == 500 || amount == 1000 || amount == 5000 || amount == 10000;
}
