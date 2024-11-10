#pragma once
#include <stdexcept>
#include <vector>

class Cash {
public:
    enum Denomination {
        HUNDRED = 100,
        FIVE_HUNDRED = 500,
        THOUSAND = 1000,
        FIVE_THOUSAND = 5000,
        TEN_THOUSAND = 10000
    };

private:
    Denomination m_Denomination;
    int m_Quantity;

public:
    Cash(Denomination denom, int qty = 1) {
        if (qty <= 0) {
            throw std::invalid_argument("Quantity must be positive");
        }
        m_Denomination = denom;
        m_Quantity = qty;
    }

    Denomination getDenomination() const { return m_Denomination; }
    int getQuantity() const { return m_Quantity; }

    static std::vector<Denomination> getDenominations() {
        return { TEN_THOUSAND, FIVE_THOUSAND, THOUSAND, FIVE_HUNDRED, HUNDRED };
    }
};