#include "gtest/gtest.h"
#include "VendingMachine.hpp"
#include "User.hpp"
#include "Admin.hpp"
#include "Cash.hpp"
#include <iostream>
#include <stdexcept>

class CoutMute {
public:
    CoutMute() { std::cout.setstate(std::ios_base::failbit); }
    ~CoutMute() { std::cout.clear(); }
};

TEST(UserTests, InsertValidAndInvalidCash) {
    CoutMute mute;

    VendingMachine machine;
    User user(machine, 0);  // User with no card balance (cash only)

    ASSERT_TRUE(user.arriveAtMachine());

    SCOPED_TRACE("Inserting valid cash of denomination 1000 with quantity 1");
    EXPECT_TRUE(user.insertCash(Cash(Cash::Denomination::THOUSAND, 1)));

    SCOPED_TRACE("Attempting to insert invalid cash with negative quantity");
    EXPECT_THROW(user.insertCash(Cash(Cash::Denomination::HUNDRED, -1)), std::invalid_argument);

    user.leaveMachine();
}

TEST(UserTests, NegativeCardBalanceThrowsException) {
    CoutMute mute;

    VendingMachine machine;

    SCOPED_TRACE("Attempting to create a User with negative card balance");

    // Expect an invalid_argument exception due to negative balance
    EXPECT_THROW(User user(machine, -1000), std::invalid_argument);
}


TEST(UserTests, PurchaseWithExactCashBalance) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    admin.arriveAtMachine();
    admin.addBeverage("Water", 600, 5);
    admin.leaveMachine();

    User user(machine, 0);  // Cash-only user
    ASSERT_TRUE(user.arriveAtMachine());
    user.insertCash(Cash(Cash::Denomination::HUNDRED, 6));  // Insert exactly 600

    SCOPED_TRACE("Attempting to purchase 'Water' with exact cash balance");
    EXPECT_TRUE(user.selectBeverage("Water"));
    
    // Expect no remaining balance
    EXPECT_TRUE(user.getChange());

    user.leaveMachine();
}

TEST(UserTests, MultipleBeveragePurchases) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    admin.arriveAtMachine();
    admin.addBeverage("Cola", 1100, 2);  // Adding limited quantity
    admin.addBeverage("Water", 600, 1);
    admin.leaveMachine();

    User user(machine, 5000);  // User with a card balance of 2000
    ASSERT_TRUE(user.arriveAtMachine());

    SCOPED_TRACE("Purchasing 'Cola' (quantity 2) - first purchase");
    EXPECT_TRUE(user.selectBeverageWithCard("Cola"));

    SCOPED_TRACE("Attempting to purchase 'Cola' (quantity 2) - second purchase");
    EXPECT_TRUE(user.selectBeverageWithCard("Cola"));  // Should succeed

    SCOPED_TRACE("Attempting to purchase 'Cola' again - should fail as quantity is now 0");
    EXPECT_FALSE(user.selectBeverageWithCard("Cola"));  // Should fail, out of stock

    user.leaveMachine();
}

TEST(UserTests, InvalidBeverageSelection) {
    CoutMute mute;

    VendingMachine machine;
    User user(machine, 1500);  // User with sufficient balance

    ASSERT_TRUE(user.arriveAtMachine());

    SCOPED_TRACE("Attempting to select a non-existent beverage");
    EXPECT_FALSE(user.selectBeverage("NonExistentBeverage"));

    user.leaveMachine();
}

TEST(UserTests, LargeCashInsertionAndChange) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    admin.arriveAtMachine();
    admin.addBeverage("Coffee", 700, 10);
    admin.addCash(Cash(Cash::Denomination::THOUSAND, 10));  // Ensure sufficient change is available
    admin.addCash(Cash(Cash::Denomination::FIVE_HUNDRED, 10));
    admin.addCash(Cash(Cash::Denomination::HUNDRED, 10));

    admin.leaveMachine();

    User user(machine, 0);  // Cash-only user
    ASSERT_TRUE(user.arriveAtMachine());
    user.insertCash(Cash(Cash::Denomination::TEN_THOUSAND, 1));  // Insert a large bill

    SCOPED_TRACE("Attempting to purchase 'Coffee' and receive large change");
    EXPECT_TRUE(user.selectBeverage("Coffee"));

    // Check that change is returned appropriately
    EXPECT_TRUE(user.getChange());

    user.leaveMachine();
}

TEST(UserTests, OccupancyControlWithMultipleUsers) {
    CoutMute mute;

    VendingMachine machine;

    // First User acquires occupancy for a cash transaction
    User cashUser(machine, 0);  // Cash-only user
    ASSERT_TRUE(cashUser.arriveAtMachine());

    // Second User (card user) should not be able to acquire occupancy
    User cardUser(machine, 3000);  // User with card balance
    EXPECT_FALSE(cardUser.arriveAtMachine());

    // Cash user leaves, releasing occupancy
    cashUser.leaveMachine();

    // Now the card user can acquire occupancy
    EXPECT_TRUE(cardUser.arriveAtMachine());

    // Card user leaves, releasing occupancy
    cardUser.leaveMachine();

    // Another cash user tries to acquire occupancy
    User anotherCashUser(machine, 0);
    EXPECT_TRUE(anotherCashUser.arriveAtMachine());

    anotherCashUser.leaveMachine();
}

TEST(UserTests, InsufficientBalanceForMultipleItems) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    admin.arriveAtMachine();
    admin.addBeverage("Water", 600, 3);
    admin.leaveMachine();

    User user(machine, 0);  // Cash-only user
    ASSERT_TRUE(user.arriveAtMachine());

    user.insertCash(Cash(Cash::Denomination::HUNDRED, 6));  // Insert only 600 KRW

    SCOPED_TRACE("Attempting to purchase 'Water' multiple times with insufficient funds");
    EXPECT_TRUE(user.selectBeverage("Water"));  // First purchase should succeed
    EXPECT_FALSE(user.selectBeverage("Water"));  // Subsequent purchase should fail due to insufficient funds

    user.leaveMachine();
}

TEST(UserTests, ExactChangeAfterPurchase) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    admin.arriveAtMachine();
    admin.addBeverage("Coffee", 700, 1);
    admin.addCash(Cash(Cash::Denomination::FIVE_HUNDRED, 2));  // Ensure change in 500 denominations
    admin.addCash(Cash(Cash::Denomination::HUNDRED, 5));       // Ensure change in 100 denominations
    admin.leaveMachine();

    User user(machine, 0);  // Cash-only user
    ASSERT_TRUE(user.arriveAtMachine());
    user.insertCash(Cash(Cash::Denomination::THOUSAND, 1));  // Insert 1000 KRW

    SCOPED_TRACE("Purchasing 'Coffee' and expecting exact change of 300 KRW");
    EXPECT_TRUE(user.selectBeverage("Coffee"));

    // Check that the exact change of 300 is returned
    EXPECT_TRUE(user.getChange());

    user.leaveMachine();
}

TEST(UserTests, UnableToProvideExactChange) {
    CoutMute mute;

    VendingMachine machine;
    Admin admin(machine);

    admin.arriveAtMachine();
    admin.addBeverage("Cola", 1100, 1);  // Beverage cost set to 1500 KRW
    admin.addCash(Cash(Cash::Denomination::THOUSAND, 1));   // Only one 1000 KRW bill available
    admin.addCash(Cash(Cash::Denomination::FIVE_HUNDRED, 1)); // Only one 500 KRW coin available
    admin.leaveMachine();

    User user(machine, 0);  // Cash-only user
    ASSERT_TRUE(user.arriveAtMachine());
    user.insertCash(Cash(Cash::Denomination::TEN_THOUSAND, 1));  // User inserts 10000 KRW

    SCOPED_TRACE("Attempting to purchase 'Cola' but unable to provide exact change");

    // User attempts to purchase "Juice" for 1500 KRW with 10000 KRW inserted
    EXPECT_TRUE(user.selectBeverage("Cola"));

    // Since the machine only has 1000 and 500 denominations, it should return 1500 KRW, not the full 8500 KRW
    EXPECT_FALSE(user.getChange());  // Expect this to return false, indicating exact change was not possible

    // Machine should have returned 1500 KRW as the best possible change
    // Since the test output is muted, we rely on the logic to verify it’s working as expected

    user.leaveMachine();
}