#include <iostream>
#include <string>
#include <memory>
#include "VendingMachine.hpp"
#include "User.hpp"
#include "Admin.hpp"
#include "Cash.hpp"

void displayUserMenu() {
    std::cout << "\nUser Menu:\n";
    std::cout << "1. Insert Cash\n";
    std::cout << "2. Purchase Beverage with Cash\n";
    std::cout << "3. Purchase Beverage with Card\n";
    std::cout << "4. Get Change\n";
    std::cout << "5. Leave Machine\n";
    std::cout << "6. Exit Program\n";
}

void displayAdminMenu() {
    std::cout << "\nAdmin Menu:\n";
    std::cout << "1. Add Beverage\n";
    std::cout << "2. Remove Beverage\n";
    std::cout << "3. Add Cash\n";
    std::cout << "4. Remove Cash\n";
    std::cout << "5. Leave Machine\n";
    std::cout << "6. Exit Program\n";
}

int main() {
    VendingMachine machine;
    bool running = true;

    while (running) {
        int roleChoice;
        std::cout << "\nSelect Role:\n1. User\n2. Admin\n3. Exit Program\n";
        std::cout << "Enter choice: ";
        std::cin >> roleChoice;

        if (roleChoice == 3) {
            running = false;
            break;
        }

        if (roleChoice == 1) { // User role
            int cardBalance;
            std::cout << "Enter initial card balance for User: ";
            std::cin >> cardBalance;
            User user(machine, cardBalance);

            if (!user.arriveAtMachine()) {
                std::cout << "Machine is currently occupied.\n";
                continue;
            }

            bool userSession = true;
            while (userSession) {
                displayUserMenu();
                int choice;
                std::cout << "Enter choice: ";
                std::cin >> choice;

                switch (choice) {
                    case 1: { // Insert Cash
                        int denom, quantity;
                        std::cout << "Enter denomination (100, 500, 1000, 5000, 10000): ";
                        std::cin >> denom;
                        std::cout << "Enter quantity: ";
                        std::cin >> quantity;
                        if (user.insertCash(Cash(static_cast<Cash::Denomination>(denom), quantity))) {
                            std::cout << "Cash inserted successfully.\n";
                        } else {
                            std::cout << "Failed to insert cash.\n";
                        }
                        break;
                    }
                    case 2: { // Purchase with Cash
                        machine.displayBeverages(); // Display available beverages
                        std::string beverageName;
                        std::cout << "Enter beverage name to purchase: ";
                        std::cin >> beverageName;
                        if (user.selectBeverage(beverageName)) {
                            std::cout << "Beverage purchased successfully with cash.\n";
                        } else {
                            std::cout << "Failed to purchase beverage. Insufficient funds or out of stock.\n";
                        }
                        break;
                    }
                    case 3: { // Purchase with Card
                        machine.displayBeverages(); // Display available beverages
                        std::string beverageName;
                        std::cout << "Enter beverage name to purchase: ";
                        std::cin >> beverageName;
                        if (user.selectBeverageWithCard(beverageName)) {
                            std::cout << "Beverage purchased successfully with card.\n";
                        } else {
                            std::cout << "Failed to purchase beverage. Insufficient card balance or out of stock.\n";
                        }
                        break;
                    }
                    case 4: // Get Change
                        user.getChange();
                        break;
                    case 5: // Leave Machine
                        user.leaveMachine();
                        userSession = false;
                        break;
                    case 6: // Exit Program
                        userSession = false;
                        running = false;
                        break;
                    default:
                        std::cout << "Invalid choice.\n";
                }
            }

        } else if (roleChoice == 2) { // Admin role
            Admin admin(machine);

            if (!admin.arriveAtMachine()) {
                std::cout << "Machine is currently occupied.\n";
                continue;
            }

            bool adminSession = true;
            while (adminSession) {
                displayAdminMenu();
                int choice;
                std::cout << "Enter choice: ";
                std::cin >> choice;

                switch (choice) {
                    case 1: { // Add Beverage
                        std::string name;
                        int price, quantity;
                        std::cout << "Enter beverage name: ";
                        std::cin >> name;
                        std::cout << "Enter price: ";
                        std::cin >> price;
                        std::cout << "Enter quantity: ";
                        std::cin >> quantity;
                        if (admin.addBeverage(name, price, quantity)) {
                            std::cout << "Beverage added successfully.\n";
                        } else {
                            std::cout << "Failed to add beverage.\n";
                        }
                        break;
                    }
                    case 2: { // Remove Beverage
                        std::string name;
                        std::cout << "Enter beverage name to remove: ";
                        std::cin >> name;
                        if (admin.removeBeverage(name)) {
                            std::cout << "Beverage removed successfully.\n";
                        } else {
                            std::cout << "Failed to remove beverage.\n";
                        }
                        break;
                    }
                    case 3: { // Add Cash
                        int denom, quantity;
                        std::cout << "Enter denomination (100, 500, 1000, 5000, 10000): ";
                        std::cin >> denom;
                        std::cout << "Enter quantity: ";
                        std::cin >> quantity;
                        if (admin.addCash(Cash(static_cast<Cash::Denomination>(denom), quantity))) {
                            std::cout << "Cash added successfully.\n";
                        } else {
                            std::cout << "Failed to add cash.\n";
                        }
                        break;
                    }
                    case 4: { // Remove Cash
                        int denom, quantity;
                        std::cout << "Enter denomination to remove (100, 500, 1000, 5000, 10000): ";
                        std::cin >> denom;
                        std::cout << "Enter quantity to remove: ";
                        std::cin >> quantity;
                        if (admin.removeCash(Cash(static_cast<Cash::Denomination>(denom), quantity))) {
                            std::cout << "Cash removed successfully.\n";
                        } else {
                            std::cout << "Failed to remove cash.\n";
                        }
                        break;
                    }
                    case 5: // Leave Machine
                        admin.leaveMachine();
                        adminSession = false;
                        break;
                    case 6: // Exit Program
                        adminSession = false;
                        running = false;
                        break;
                    default:
                        std::cout << "Invalid choice.\n";
                }
            }
        } else {
            std::cout << "Invalid role selection.\n";
        }
    }

    std::cout << "Exiting program. Goodbye!\n";
    return 0;
}
