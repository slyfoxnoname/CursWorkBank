#include "Bank.h"
#include <iostream>
using namespace std;

int main() {
    // Створення клієнтів
    Client client1("Олександр", 10000);
    Client client2("Марiя", 15000);

    // Додавання вкладів клієнтам
    Deposit deposit("Термiновий", 5000, 5.0, 2); // 5% на 2 роки
    Deposit deposit("Термiновий", 3000, 4.0, 3);   // 4% на 3 роки

    client1.addDeposit(deposit1);
    client2.addDeposit(deposit2);

    // Виведення інформації про клієнтів
    cout << "=== Початковий стан банку ===" << endl;
    vector<Client> clients = {client1, client2};
    printBankState(clients);

    // Розрахунок прибутку по вкладу
    cout << "=== Розрахунок прибутку ===" << endl;
    calculateProfit(deposit1);
    calculateProfit(deposit2);

    // Робота з цінними паперами
    vector<Stock> stocks;
    buyStock(stocks, "Акцiї Apple", 150.0, 10);
    buyStock(stocks, "Акцiї Tesla", 250.0, 5);

    cout << "\n=== Оновлення цiн цiнних паперiв ===" << endl;
    updateStockPrices(stocks, 10.0); // Підвищення ціни на 10%
    for (const auto& stock : stocks) {
        cout << "Назва: " << stock.name << ", Цiна: " << stock.price
             << ", Кiлькiсть: " << stock.quantity << endl;
    }

    // Збереження даних у CSV
    cout << "\n=== Збереження у CSV ===" << endl;
    saveToCSV("clients.csv", clients);

    // Завантаження даних із CSV
    cout << "\n=== Завантаження з CSV ===" << endl;
    vector<Client> loadedClients;
    loadFromCSV("clients.csv", loadedClients);
    printBankState(loadedClients);

    return 0;
}
