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

TEST(VendingMachineBasicTests, AddAndRemoveBeverage) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    admin.addBeverage("Juice", 1200);
    EXPECT_NO_THROW(admin.removeBeverage("Juice")); // Should succeed
    EXPECT_NO_THROW(admin.removeBeverage("Nonexistent Beverage")); // Should not throw even if beverage doesn’t exist
}
