#include "gtest/gtest.h"
#include "VendingMachine.hpp"
#include "Admin.hpp"
#include "User.hpp"
#include "Cash.hpp"
#include <iostream>

class CoutMute {
public:
    CoutMute() { std::cout.setstate(std::ios_base::failbit); }
    ~CoutMute() { std::cout.clear(); }
};

TEST(VendingMachineTransactionTests, PurchaseWithExactChange) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);
    User user(machine);

    admin.addBeverage("Water", 1000);
    admin.addCash(Cash(Cash::Denomination::THOUSAND, 5));

    user.insertCash(Cash(Cash::Denomination::THOUSAND, 1));
    EXPECT_TRUE(user.selectBeverage("Water"));
    user.getChange();
}

TEST(VendingMachineTransactionTests, InsufficientBalance) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);
    User user(machine);

    admin.addBeverage("Coffee", 2000);

    user.insertCash(Cash(Cash::Denomination::THOUSAND, 1));
    EXPECT_FALSE(user.selectBeverage("Coffee"));
}

TEST(VendingMachineTransactionTests, InsertCashAfterInsufficientBalance) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);
    User user(machine);

    admin.addBeverage("Snack", 1500);

    user.insertCash(Cash(Cash::Denomination::THOUSAND, 1));
    EXPECT_FALSE(user.selectBeverage("Snack"));

    user.insertCash(Cash(Cash::Denomination::FIVE_HUNDRED, 1));
    EXPECT_TRUE(user.selectBeverage("Snack"));
}
