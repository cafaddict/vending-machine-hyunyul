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

    admin.addBeverage("Water", 1000, 10);
    admin.addCash(Cash(Cash::Denomination::THOUSAND, 5));

    user.insertCash(Cash(Cash::Denomination::THOUSAND, 1));
    EXPECT_TRUE(user.selectBeverage("Water"));
}

TEST(VendingMachineTransactionTests, InsufficientBalance) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);
    User user(machine);

    admin.addBeverage("Coffee", 2000, 5);

    user.insertCash(Cash(Cash::Denomination::THOUSAND, 1));
    EXPECT_FALSE(user.selectBeverage("Coffee"));
}

TEST(VendingMachineTransactionTests, ReturnChange) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);
    User user(machine);

    admin.addCash(Cash(Cash::Denomination::THOUSAND, 3));
    user.insertCash(Cash(Cash::Denomination::THOUSAND, 1));

    // Capture and verify output
    testing::internal::CaptureStdout();
    user.getChange();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Returning change: 1000 KRW"), std::string::npos);
}
