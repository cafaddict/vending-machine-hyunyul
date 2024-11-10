#include "gtest/gtest.h"
#include "VendingMachine.hpp"
#include "Admin.hpp"
#include "Cash.hpp"
#include <iostream>

class CoutMute {
public:
    CoutMute() { std::cout.setstate(std::ios_base::failbit); }
    ~CoutMute() { std::cout.clear(); }
};

TEST(VendingMachineAdminTests, AddAndRemoveLargeAmountsOfCash) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    admin.addCash(Cash(Cash::Denomination::TEN_THOUSAND, 1000));
    EXPECT_NO_THROW(admin.removeCash(Cash(Cash::Denomination::TEN_THOUSAND, 500)));
    EXPECT_ANY_THROW(admin.removeCash(Cash(Cash::Denomination::TEN_THOUSAND, 600))); // Exceeds available cash
}

TEST(VendingMachineAdminTests, AddNegativeCashQuantity) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    EXPECT_THROW(admin.addCash(Cash(Cash::Denomination::FIVE_HUNDRED, -1)), std::invalid_argument);
}
