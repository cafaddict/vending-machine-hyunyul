#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

class VendingMachine {
public:
    VendingMachine();
    ~VendingMachine();

    void insertCoin(int coin);
    void selectItem(std::string item);
    void cancelTransaction();
    void displayItems();
    void displayCoins();
    void displayInsertedCoins();
    void displayTotalInsertedCoins();
    void displayTotalCoins();
    void displayTotalSales();

private:
    std::unordered_map<std::string, int> items;
    std::unordered_map<int, int> coins;
    std::unordered_map<int, int> insertedCoins;
    int totalInsertedCoins;
    int totalCoins;
    int totalSales;
    int currentCoin;
    std::string currentItem;

    void addItem(std::string item, int price);
    void addCoin(int coin, int count);
    void addInsertedCoin(int coin);
    void addTotalInsertedCoins(int coin);
    void addTotalCoins(int coin);
    void addTotalSales(int price);
    void removeInsertedCoin(int coin);
    void removeTotalInsertedCoins(int coin);
    void removeTotalCoins(int coin);
    void removeTotalSales(int price);
    void returnCoins();
    void returnInsertedCoins();
    void returnTotalInsertedCoins();
    void returnTotalCoins();
    void returnTotalSales();
    void resetInsertedCoins();
    void resetTotalInsertedCoins();
    void resetTotalCoins();
    void resetTotalSales();
    void resetCurrentCoin();
    void resetCurrentItem();
    void resetItems();
    void resetCoins();
    void reset();
    void displayItem(std::string item, int price);
    void displayCoin(int coin, int count);
    void displayInsertedCoin(int coin);
    void displayTotalInsertedCoin(int coin);
    void displayTotalCoin(int coin);
    void displayTotalSale(int price);
    void displayMessage(std::string message);
    void displayError(std::string error);
    void displaySuccess(std::string success);
    void displayWarning(std::string warning);
    void displayPrompt(std::string prompt);
    void displayPrompt(std::string prompt, std::string item);
    void displayPrompt(std::string prompt, int coin);
    void displayPrompt(std::string prompt, std::string item, int price);
    void displayPrompt(std::string prompt, std::string item, int price, int coin);
    void displayPrompt(std::string prompt, int coin, int count);
    void displayPrompt(std::string prompt, int coin, int count, int total);
    void displayPrompt(std::string prompt, int coin, int count, int total, int price);
    void displayPrompt(std::string prompt, int coin, int count, int total, int price, std::string item);
    void displayPrompt(std::string prompt, int coin, int count, int total, int price, std::string item
}