#include "gtest/gtest.h"
#include "VendingMachine.hpp"
#include "Admin.hpp"
#include "Cash.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>

class CoutMute {
public:
    CoutMute() { std::cout.setstate(std::ios_base::failbit); }
    ~CoutMute() { std::cout.clear(); }
};

TEST(AdminTests, AddAndRemoveBeverage) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    // Admin arrives at the machine
    ASSERT_TRUE(admin.arriveAtMachine());

    SCOPED_TRACE("Adding valid beverage 'Water'");
    EXPECT_TRUE(admin.addBeverage("Water", 600, 10));

    SCOPED_TRACE("Removing existing beverage 'Water'");
    EXPECT_TRUE(admin.removeBeverage("Water"));
    
    SCOPED_TRACE("Attempting to remove non-existent beverage 'Nonexistent'");
    EXPECT_FALSE(admin.removeBeverage("Nonexistent"));

    // Admin leaves the machine
    admin.leaveMachine();
}

TEST(AdminTests, AddInvalidBeverage) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    ASSERT_TRUE(admin.arriveAtMachine());

    // Attempt to add a beverage with invalid price and quantity
    SCOPED_TRACE("Adding a beverage with negative price");
    EXPECT_THROW(admin.addBeverage("Cola", -100, 10), std::invalid_argument);


    SCOPED_TRACE("Adding a beverage with zero price");
    EXPECT_THROW(admin.addBeverage("Coffee", 0, 10), std::invalid_argument);

    SCOPED_TRACE("Adding a beverage with invalid price");
    EXPECT_THROW(admin.addBeverage("Coffee", 50, 10), std::invalid_argument);

    SCOPED_TRACE("Adding a beverage with invalid name");
    EXPECT_THROW(admin.addBeverage("Invalid", 1000, 5), std::invalid_argument);

    SCOPED_TRACE("Adding a beverage with zero quantity");
    EXPECT_TRUE(admin.addBeverage("Water", 600, 0));

    admin.leaveMachine();
}

TEST(AdminTests, OccupancyControl) {
    CoutMute mute;

    VendingMachine machine;

    // First Admin arrives and acquires occupancy
    Admin admin1(machine);
    ASSERT_TRUE(admin1.arriveAtMachine());

    // Second Admin should not be able to acquire occupancy
    Admin admin2(machine);
    EXPECT_FALSE(admin2.arriveAtMachine());

    // First Admin leaves, releasing occupancy
    admin1.leaveMachine();

    // Now the second admin can acquire occupancy
    EXPECT_TRUE(admin2.arriveAtMachine());
    admin2.leaveMachine();
}

TEST(AdminTests, AddAndRemoveCash) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    ASSERT_TRUE(admin.arriveAtMachine());

    SCOPED_TRACE("Adding valid cash of denomination 1000 with quantity 5");
    EXPECT_TRUE(admin.addCash(Cash(Cash::Denomination::THOUSAND, 5)));

    SCOPED_TRACE("Removing valid cash of denomination 1000 with quantity 2");
    EXPECT_TRUE(admin.removeCash(Cash(Cash::Denomination::THOUSAND, 2)));

    SCOPED_TRACE("Attempting to remove more cash than available");
    EXPECT_FALSE(admin.removeCash(Cash(Cash::Denomination::THOUSAND, 10)));

    admin.leaveMachine();
}

TEST(AdminTests, RemoveNonexistentCash) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    ASSERT_TRUE(admin.arriveAtMachine());

    SCOPED_TRACE("Attempting to remove cash from an empty machine");
    EXPECT_FALSE(admin.removeCash(Cash(Cash::Denomination::FIVE_HUNDRED, 1)));

    admin.leaveMachine();
}

TEST(AdminTests, AddLargeQuantityOfCash) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    ASSERT_TRUE(admin.arriveAtMachine());

    SCOPED_TRACE("Adding a large quantity of 1000 KRW cash");
    EXPECT_TRUE(admin.addCash(Cash(Cash::Denomination::THOUSAND, 1000000)));

    admin.leaveMachine();
}

TEST(AdminTests, AddAndRemoveMaximumBeverageQuantity) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    ASSERT_TRUE(admin.arriveAtMachine());

    SCOPED_TRACE("Adding beverage 'Coffee' with maximum quantity");
    EXPECT_TRUE(admin.addBeverage("Coffee", 700, std::numeric_limits<int>::max()));

    SCOPED_TRACE("Removing the maximum quantity of 'Coffee'");
    EXPECT_TRUE(admin.removeBeverage("Coffee"));

    admin.leaveMachine();
}

TEST(AdminTests, RemoveCashBoundaryCondition) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    ASSERT_TRUE(admin.arriveAtMachine());

    SCOPED_TRACE("Adding 2 of 500 KRW denomination");
    EXPECT_TRUE(admin.addCash(Cash(Cash::Denomination::FIVE_HUNDRED, 2)));

    SCOPED_TRACE("Removing exactly 2 of 500 KRW denomination");
    EXPECT_TRUE(admin.removeCash(Cash(Cash::Denomination::FIVE_HUNDRED, 2)));

    SCOPED_TRACE("Attempting to remove cash again should fail as it's now empty");
    EXPECT_FALSE(admin.removeCash(Cash(Cash::Denomination::FIVE_HUNDRED, 1)));

    admin.leaveMachine();
}

TEST(AdminTests, AddDuplicateBeverages) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    ASSERT_TRUE(admin.arriveAtMachine());

    SCOPED_TRACE("Adding 'Water' with price 600 and quantity 10");
    EXPECT_TRUE(admin.addBeverage("Water", 600, 10));

    EXPECT_EQ(machine.getBevQuantity("Water"), 10);

    SCOPED_TRACE("Adding 'Water' again with a same price should be accepted");
    EXPECT_TRUE(admin.addBeverage("Water", 600, 5));

    SCOPED_TRACE("Adding 'Water' again and quantity should be added");
    EXPECT_EQ(machine.getBevQuantity("Water"), 15);

    admin.leaveMachine();
}

TEST(AdminTests, AddCashBoundaryValues) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    ASSERT_TRUE(admin.arriveAtMachine());

    SCOPED_TRACE("Attempting to add negative cash quantity");
    EXPECT_THROW(admin.addCash(Cash(Cash::Denomination::THOUSAND, -5)), std::invalid_argument);

    SCOPED_TRACE("Attempting to add zero cash quantity");
    EXPECT_TRUE(admin.addCash(Cash(Cash::Denomination::THOUSAND, 0)));

    admin.leaveMachine();
}
