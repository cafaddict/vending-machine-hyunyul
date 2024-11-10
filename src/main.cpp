#include "Admin.hpp"
#include "User.hpp"
#include "VendingMachine.hpp"
#include "Cash.hpp"
#include <iostream>

int main() {
    VendingMachine machine;

    // Create Admin and User
    Admin admin(machine);
    User user(machine);

    // Admin adds beverages to the vending machine
    admin.addBeverage("Cola", 1500);
    admin.addBeverage("Water", 1000);
    admin.addBeverage("Coffee", 2000);

    // Display available beverages in the machine
    std::cout << "Admin setting up vending machine:\n";
    machine.displayBeverages();
    std::cout << std::endl;

    // Admin adds initial cash to the vending machine for change
    admin.addCash(Cash(Cash::THOUSAND, 5));        // Adds 5 x 1000 KRW bills
    admin.addCash(Cash(Cash::FIVE_HUNDRED, 10));   // Adds 10 x 500 KRW coins

    // User interacts with the vending machine
    std::cout << "User interactions:\n";

    // User inserts cash
    user.insertCash(Cash(Cash::THOUSAND, 2));      // User inserts 2 x 1000 KRW
    user.insertCash(Cash(Cash::FIVE_HUNDRED, 1));  // User inserts 1 x 500 KRW

    // User selects a beverage
    user.selectBeverage("Cola");

    // User requests change
    user.getChange();

    // Display final state of available beverages
    std::cout << "\nFinal state of vending machine:\n";
    machine.displayBeverages();

    return 0;
}
