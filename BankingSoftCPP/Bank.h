#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Структура для вкладу
struct Deposit {
    string type;         // Тип вкладу
    double amount;       // Сума
    double interest_rate; // Процентна ставка
    int duration;         // Строк (в роках)

    Deposit() : type("Термiновий"), amount(0), interest_rate(0), duration(0) {}
};

// Клас для клієнта
class Client {
public:
    string name;                 // Ім'я клієнта
    double balance;              // Баланс клієнта
    vector<Deposit> deposits;   // Список вкладів

    Client(string n = "", double b = 0) : name(n), balance(b) {}

    void addDeposit(const Deposit& deposit) {
        deposits.push_back(deposit);
    }

    void displayClientInfo() const {
        cout << "Клiєнт: " << name << "\nБаланс: " << balance << "\nВклади:\n";
        for (const auto& deposit : deposits) {
            cout << "Тип: " << deposit.type << ", Сума: " << deposit.amount
                 << ", Процентна ставка: " << deposit.interest_rate
                 << "%, Строк: " << deposit.duration << " рокiв\n";
        }
    }
};

// Структура для цінного паперу
struct Stock {
    string name;     // Ім'я цінного паперу
    double price;    // Поточна ціна
    int quantity;    // Кількість

    Stock(string n = "", double p = 0.0, int q = 0) : name(n), price(p), quantity(q) {}
};

void calculateProfit(const Deposit& deposit);

void saveToCSV(const string& filename, const vector<Client>& clients);

void loadFromCSV(const string& filename, vector<Client>& clients);

void printBankState(const vector<Client>& clients);

void updateStockPrices(vector<Stock>& stocks, double percentIncrease);

void buyStock(vector<Stock>& stocks, const string& stockName, double price, int quantity);

void sellStock(vector<Stock>& stocks, const string& stockName, int quantity);

#endif // BANK_H
