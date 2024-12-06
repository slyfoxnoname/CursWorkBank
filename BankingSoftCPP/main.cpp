#include "Bank.h"
using namespace std;

int main() {
    setlocale (LC_CTYPE, "");
    vector<Client> clients;
    vector<Stock> stocks;
    int choice;


    cout << " Виберiть операцiю\n";
    cout << "====================\n";

    cout << "1. Завантажити данi з файлу\n";
    cout << "2. Ввести данi вручну\n" << "====================\n" << "Введiть номер: ";
    cin >> choice;

    if (choice == 1) {
        string filename;
        cout << "Введiть iм'я файлу для завантаження: ";
        cin >> filename;
        loadFromCSV(filename, clients);
         printBankState(clients);
    } else if (choice == 2) {
    int numClients;
    cout << "\n====================\n";
    cout << "Введiть кiлькiсть клiєнтiв для додавання: ";
    cin >> numClients;

    // Лічильник клієнтів
    int clientCount = 0;

    for (int i = 0; i < numClients; ++i) {
        string name;
        double balance;
        cout << "\n====================\n";
        cout << "\nВведiть iм'я клiєнта без пробiлiв: ";
        cin >> name;
        cout << "\nВведiть баланс клiєнта: ";
        cin >> balance;
        Client client(name, balance);

        int numDeposits;
        cout << "\nВведiть кiлькiсть вкладiв: ";
        cin >> numDeposits;

        // Лічильник вкладів (цінних паперів) для кожного клієнта
        int depositCount = 0;

        for (int j = 0; j < numDeposits; ++j) {
            Deposit deposit;
            cout << "\n====================\n";
            cout << "\nВведiть тип вкладу: ";
            cin >> deposit.type;
            cout << "\nВведiть суму вкладу: ";
            cin >> deposit.amount;
            cout << "\nВведiть процентну ставку: ";
            cin >> deposit.interest_rate;
            cout << "\nВведiть строк вкладу (в роках): ";
            cin >> deposit.duration;
            client.addDeposit(deposit);
            depositCount++; // Збільшуємо лічильник вкладів
        }

        clients.push_back(client);
        clientCount++; // Збільшуємо лічильник клієнтів
        cout << "Кількість вкладів для цього клієнта: " << depositCount << endl;
    }

    // Виведення загальної кількості клієнтів
    cout << "\nЗагальна кількість клієнтів: " << clientCount << endl;
} else {
    cout << "\nНевiрний вибiр!" << endl;
    return 1;
}


    // Додавання цінних паперів
    int numStocks;
    cout << "\n====================\n";
    cout << "Введiть кiлькiсть цiнних паперiв: ";
    cin >> numStocks;

    for (int i = 0; i < numStocks; ++i) {
        string name;
        double price;
        int quantity;
        cout << "\nВведiть iм'я цiнного паперу: ";
        cin >> name;
        cout << "\nВведiть цiну: ";
        cin >> price;
        cout << "\nВведiть кiлькiсть: ";
        cin >> quantity;
        stocks.push_back(Stock(name, price, quantity));
    }

    // Відображення стану банку
    cout << "\n========= Стан банку =========\n";
    printBankState(clients);

    // Оновлення цін на цінні папери
    double percentIncrease;
    cout << "\nВведiть вiдсоток збiльшення цiн на цiннi папери: ";
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

    int answer;
    cout << "=============================\n";
    cout << "\nХочете зберегти даннi у файл?\n" << "1.Так,зберегти у файл.\n" << "2. Нi, не зберiгати.\n" << "Введiть номер:";
    cin >> answer;

    if (answer == 1){
        cout << "Введiть iм'я файлу для збереження даних: ";
        cin >> filename;
        saveToCSV(filename, clients);
    } else if (answer == 2){
        exit(1);
        }

    return 0;
}
