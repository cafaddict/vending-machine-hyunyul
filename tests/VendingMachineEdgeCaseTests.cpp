#include "gtest/gtest.h"
#include "VendingMachine.hpp"
#include "Admin.hpp"
#include "User.hpp"
#include "Cash.hpp"
#include <iostream>
#include <string>

class CoutMute {
public:
    CoutMute() { std::cout.setstate(std::ios_base::failbit); }
    ~CoutMute() { std::cout.clear(); }
};

TEST(VendingMachineEdgeCaseTests, ZeroPriceBeverage) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);
    User user(machine);

    admin.addBeverage("Free Drink", 0); // Add a beverage with zero price
    EXPECT_TRUE(user.selectBeverage("Free Drink")); // User should be able to get it without cash
}

TEST(VendingMachineEdgeCaseTests, HighDenominationChangeReturn) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);
    User user(machine);

    admin.addBeverage("Tea", 1200);
    admin.addCash(Cash(Cash::Denomination::TEN_THOUSAND, 1));

    user.insertCash(Cash(Cash::Denomination::TEN_THOUSAND, 1));
    EXPECT_TRUE(user.selectBeverage("Tea"));

    testing::internal::CaptureStdout();
    user.getChange();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Returning change: 8800 KRW"), std::string::npos);
}

TEST(VendingMachineEdgeCaseTests, MaximumCapacityOfCashStorage) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    EXPECT_NO_THROW(admin.addCash(Cash(Cash::Denomination::HUNDRED, 1000)));
}