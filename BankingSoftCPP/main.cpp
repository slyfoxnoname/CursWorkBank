#include "Bank.h"
using namespace std;

int main() {
    setlocale (LC_CTYPE, "");
    vector<Client> clients;
    vector<Stock> stocks;
    int choice;

    cout << "Виберiть операцiю:\n";
    cout << "1. Завантажити данi з файлу\n";
    cout << "2. Ввести данi вручну\nВведiть номер: ";
    cin >> choice;

    if (choice == 1) {
        string filename;
        cout << "Введiть iм'я файлу для завантаження: ";
        cin >> filename;
        loadFromCSV(filename, clients);
    } else if (choice == 2) {
        int numClients;
        cout << "Введiть кiлькiсть клiєнтiв для додавання: ";
        cin >> numClients;

        for (int i = 0; i < numClients; ++i) {
            string name;
            double balance;
            cout << "Введiть iм'я клiєнта: ";
            cin >> name;
            cout << "Введiть баланс клiєнта: ";
            cin >> balance;
            Client client(name, balance);

            int numDeposits;
            cout << "Введiть кiлькiсть вкладiв: ";
            cin >> numDeposits;

            for (int j = 0; j < numDeposits; ++j) {
                Deposit deposit;
                cout << "Введiть тип вкладу: ";
                cin >> deposit.type;
                cout << "Введiть суму вкладу: ";
                cin >> deposit.amount;
                cout << "Введiть процентну ставку: ";
                cin >> deposit.interest_rate;
                cout << "Введiть строк вкладу (в роках): ";
                cin >> deposit.duration;
                client.addDeposit(deposit);
            }

            clients.push_back(client);
        }
    } else {
        cout << "Невiрний вибiр!" << endl;
        return 1;
    }

    // Додавання цінних паперів
    int numStocks;
    cout << "Введiть кiлькiсть цiнних паперiв: ";
    cin >> numStocks;

    for (int i = 0; i < numStocks; ++i) {
        string name;
        double price;
        int quantity;
        cout << "Введiть iм'я цiнного паперу: ";
        cin >> name;
        cout << "Введiть цiну: ";
        cin >> price;
        cout << "Введiть кiлькiсть: ";
        cin >> quantity;
        stocks.push_back(Stock(name, price, quantity));
    }

    // Відображення стану банку
    cout << "\n=== Стан банку ===\n";
    printBankState(clients);

    // Оновлення цін на цінні папери
    double percentIncrease;
    cout << "Введiть вiдсоток збiльшення цiн на цiннi папери: ";
    cin >> percentIncrease;
    updateStockPrices(stocks, percentIncrease);

    // Виведення оновлених цін
    cout << "\n=== Оновленi цiни на цiннi папери ===\n";
    for (const auto& stock : stocks) {
        cout << "Цiнний папiр: " << stock.name << ", Цiна: " << stock.price << ", Кiлькiсть: " << stock.quantity << endl;
    }

    // Приклад розрахунку прибутку по першому депозиту (якщо він існує)
    if (!clients.empty()) {
        cout << "\nРозрахунок прибутку по першому депозиту:\n";
        calculateProfit(clients[0].deposits[0]);
    }

    // Збереження даних у файл
    string filename;
    cout << "Введiть iм'я файлу для збереження даних: ";
    cin >> filename;
    saveToCSV(filename, clients);

    return 0;
}
