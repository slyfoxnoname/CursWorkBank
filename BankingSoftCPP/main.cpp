#include <iostream>
#include "Bank.h"
#include <locale>
#include <vector>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "rus");

    // ����������� �����
    double initial_cash = 1000000; //��������� ���� ���i��� ��� �����
    vector<Client> clients;  // ������ ��� �볺���
    vector<Stock> stocks;    // ������ ��� ������ ������

    // ����
    int choice;
    do {
        cout << "\n====================\n";
        cout << "       ����\n";
        cout << "====================\n";
        cout << "\n1. ������ ��i����\n";
        cout << "\n2. ������ �i���� ���i�\n";
        cout << "3. ������� �i�� �i���� �����i�\n";
        cout << "4. ������ �i���� ���i�\n";
        cout << "5. ������� �i���� ���i�\n";
        cout << "\n6. ������� �������� ��i���i�\n";
        cout << "7. ������� ���� �����\n";
        cout << "\n8. �������� ���i ����� � ����\n";
        cout << "9. ����������� ���i ����� � �����\n";
        cout << "\n0. ���i�\n";
        cout << "\n====================\n";
        cout << "��� ���i�: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                double deposit, rate;
                int duration;
                cout << "\n====================\n";
                cout << "\n����i�� i�'� ��i����: ";
                cin >> name;
                cout << "\n����i�� ���������� �������: ";
                cin >> deposit;
                cout << "\n����i�� �i��� �i�������� ������: ";
                cin >> rate;
                cout << "\n����i�� ����� �������� (�i���i�): ";
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
                cout << "\n����i�� ����� �i����� ������: ";
                cin >> name;
                cout << "\n����i�� �i��: ";
                cin >> price;
                cout << "\n����i�� �i���i���: ";
                cin >> quantity;
                cout << "\n����i�� ��� (���i�(Stock)/���i���i�(Bond)): ";
                cin >> type;
                stocks.push_back(Stock(name, price, quantity));
                break;
            }
            case 3:
                {
                    double percentIncrease;
                    cout << "\n====================\n";
                    cout << "����i�� ��������� ��������� �i���� �����i�: ";
                    cin >> percentIncrease;
                    updateStockPrices(stocks, percentIncrease);
                    cout << "�i�� �i���� �����i� ��������.\n";
                    break;
                }
            case 4: {
                string name;
                int quantity;
                double price;
                cout << "\n====================\n";
                cout << "����i�� ����� �i����� ������ ��� �������: ";
                cin >> name;
                cout << "����i�� �i���i��� ��� �������: ";
                cin >> quantity;
                cout << "����i�� �i�� ��� �������: ";
                cin >> price;
                buyStock(stocks, name, price, quantity);
                break;
            }
            case 5: {
                string name;
                int quantity;
                cout << "\n====================\n";
                cout << "����i�� ����� �i����� ������ ��� �������: ";
                cin >> name;
                cout << "����i�� �i���i��� ��� �������: ";
                cin >> quantity;
                sellStock(stocks, name, quantity);
                break;
            }
            case 6:
                {
                    double percentIncrease;
                    cout << "\n====================\n";
                    cout << "����i�� ��������� ��������� ��������: ";
                    cin >> percentIncrease;
                    for (auto& client : clients) {
                        for (auto& deposit : client.deposits) {
                            deposit.amount += deposit.amount * percentIncrease / 100;
                        }
                    }
                    cout << "�������� ��i���i� ��������.\n";
                    break;
                }
            case 7:
                printBankState(clients);
                break;
            case 8: {
                string filename;
                cout << "\n====================\n";
                cout << "����i�� ����� ����� ��� ����������: ";
                cin >> filename;
                saveToCSV(filename, clients);
                break;
            }
            case 9: {
                string filename;
                cout << "\n====================\n";
                cout << "����i�� ����� �����: ";
                cin >> filename;
                loadFromCSV(filename, clients);
                printBankState(clients);
                break;
            }
            case 0:
                cout << "���������� ��������.\n";
                break;
            default:
                cout << "\n===============================\n";
                cout << "���i���� ���i�, ��������� �� ���.\n";
                cout << "\n===============================\n";
        }
    } while (choice != 0);

    return 0;
}
