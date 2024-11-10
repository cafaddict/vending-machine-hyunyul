#include "VendingMachine.hpp"
#include "Admin.hpp"
#include "User.hpp"
#include "Cash.hpp"
#include <iostream>

int main() {
    VendingMachine machine;

    // Admin adds beverages and cash to the machine
    Admin admin(machine);
    admin.addBeverage("Water", 1000, 10);
    admin.addBeverage("Soda", 1500, 5);
    admin.addCash(Cash(Cash::Denomination::THOUSAND, 5));
    admin.addCash(Cash(Cash::Denomination::FIVE_HUNDRED, 10));

    // Display available beverages
    std::cout << "\n--- Displaying Beverages ---\n";
    machine.displayBeverages();

    // User inserts cash and selects a beverage
    User user(machine);
    user.insertCash(Cash(Cash::Denomination::THOUSAND, 1));
    if (user.selectBeverage("Water")) {
        std::cout << "Successfully purchased Water.\n";
    }

    // Get remaining change
    std::cout << "\n--- Returning Change ---\n";
    user.getChange();

    return 0;
}
