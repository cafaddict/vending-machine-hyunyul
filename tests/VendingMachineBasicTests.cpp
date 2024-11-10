#include "gtest/gtest.h"
#include "VendingMachine.hpp"
#include "Admin.hpp"
#include <iostream>

class CoutMute {
public:
    CoutMute() { std::cout.setstate(std::ios_base::failbit); }
    ~CoutMute() { std::cout.clear(); }
};

TEST(VendingMachineBasicTests, AddAndRemoveBeverage) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    admin.addBeverage("Juice", 1200, 10);
    EXPECT_NO_THROW(admin.removeBeverage("Juice")); // Should succeed
    EXPECT_NO_THROW(admin.removeBeverage("Nonexistent Beverage")); // Should not throw even if beverage doesn’t exist
}

TEST(VendingMachineBasicTests, DisplayBeverages) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    admin.addBeverage("Coffee", 2000, 5);
    testing::internal::CaptureStdout();
    machine.displayBeverages();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Coffee - 2000 KRW, Quantity: 5"), std::string::npos);
}
