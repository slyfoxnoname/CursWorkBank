#include <iostream>
#include "Bank.h"
#include <locale>
#include <vector>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "rus");

    // Ініціалізація банку
    double initial_cash = 1000000; //початкова сума готiвки для банку
    vector<Client> clients;  // Вектор для клієнтів
    vector<Stock> stocks;    // Вектор для цінних паперів

    // Меню
    int choice;
    do {
        cout << "\n====================\n";
        cout << "       МЕНЮ\n";
        cout << "====================\n";
        cout << "\n1. Додати клiєнта\n";
        cout << "\n2. Додати цiнний папiр\n";
        cout << "3. Оновити цiни цiнних паперiв\n";
        cout << "4. Купити цiнний папiр\n";
        cout << "5. Продати цiнний папiр\n";
        cout << "\n6. Оновити депозити клiєнтiв\n";
        cout << "7. Вивести стан банку\n";
        cout << "\n8. Зберегти данi банку у файл\n";
        cout << "9. Завантажити данi банку з файлу\n";
        cout << "\n0. Вихiд\n";
        cout << "\n====================\n";
        cout << "Ваш вибiр: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                double deposit, rate;
                int duration;
                cout << "\n====================\n";
                cout << "\nВведiть iм'я клiєнта: ";
                cin >> name;
                cout << "\nВведiть початковий депозит: ";
                cin >> deposit;
                cout << "\nВведiть рiчну вiдсоткову ставку: ";
                cin >> rate;
                cout << "\nВведiть строк депозиту (мiсяцiв): ";
                cin >> duration;
                clients.push_back(Client(name, deposit));
                clients.back().addDeposit(Deposit());
                break;
            }
            case 2: {
                string name, type;
                double price;
                int quantity;
                cout << "\n====================\n";
                cout << "\nВведiть назву цiнного паперу: ";
                cin >> name;
                cout << "\nВведiть цiну: ";
                cin >> price;
                cout << "\nВведiть кiлькiсть: ";
                cin >> quantity;
                cout << "\nВведiть тип (акцiя(Stock)/облiгацiя(Bond)): ";
                cin >> type;
                stocks.push_back(Stock(name, price, quantity));
                break;
            }
            case 3:
                {
                    double percentIncrease;
                    cout << "\n====================\n";
                    cout << "Введiть процентне збільшення цiнних паперiв: ";
                    cin >> percentIncrease;
                    updateStockPrices(stocks, percentIncrease);
                    cout << "Цiни цiнних паперiв оновлено.\n";
                    break;
                }
            case 4: {
                string name;
                int quantity;
                double price;
                cout << "\n====================\n";
                cout << "Введiть назву цiнного паперу для покупки: ";
                cin >> name;
                cout << "Введiть кiлькiсть для покупки: ";
                cin >> quantity;
                cout << "Введiть цiну для покупки: ";
                cin >> price;
                buyStock(stocks, name, price, quantity);
                break;
            }
            case 5: {
                string name;
                int quantity;
                cout << "\n====================\n";
                cout << "Введiть назву цiнного паперу для продажу: ";
                cin >> name;
                cout << "Введiть кiлькiсть для продажу: ";
                cin >> quantity;
                sellStock(stocks, name, quantity);
                break;
            }
            case 6:
                {
                    double percentIncrease;
                    cout << "\n====================\n";
                    cout << "Введiть процентне збільшення депозитів: ";
                    cin >> percentIncrease;
                    for (auto& client : clients) {
                        for (auto& deposit : client.deposits) {
                            deposit.amount += deposit.amount * percentIncrease / 100;
                        }
                    }
                    cout << "Депозити клiєнтiв оновлено.\n";
                    break;
                }
            case 7:
                printBankState(clients);
                break;
            case 8: {
                string filename;
                cout << "\n====================\n";
                cout << "Введiть назву файлу для збереження: ";
                cin >> filename;
                saveToCSV(filename, clients);
                break;
            }
            case 9: {
                string filename;
                cout << "\n====================\n";
                cout << "Введiть назву файлу: ";
                cin >> filename;
                loadFromCSV(filename, clients);
                printBankState(clients);
                break;
            }
            case 0:
                cout << "Завершення програми.\n";
                break;
            default:
                cout << "\n===============================\n";
                cout << "Невiрний вибiр, спробуйте ще раз.\n";
                cout << "\n===============================\n";
        }
    } while (choice != 0);

    return 0;
}
