#pragma once

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
    Cash(Denomination denom, int quantity);

    Denomination getDenomination() const;
    int getQuantity() const;
    static bool isValidDenomination(int amount);

    static std::vector<Denomination> getDenominations() {

        return { Denomination::HUNDRED, Denomination::FIVE_HUNDRED, Denomination::THOUSAND, Denomination::FIVE_THOUSAND, Denomination::TEN_THOUSAND };

    }
};
