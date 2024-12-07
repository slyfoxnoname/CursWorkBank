#include "Bank.h"
using namespace std;

int main() {
    setlocale (LC_CTYPE, "");
    vector<Client> clients;
    vector<Stock> stocks;
    int choice;

    cout << "�����i�� ������i�:\n";
    cout << "1. ����������� ���i � �����\n";
    cout << "2. ������ ���i ������\n����i�� �����: ";
    cin >> choice;

    if (choice == 1) {
        string filename;
        cout << "����i�� i�'� ����� ��� ������������: ";
        cin >> filename;
        loadFromCSV(filename, clients);
    } else if (choice == 2) {
        int numClients;
        cout << "����i�� �i���i��� ��i���i� ��� ���������: ";
        cin >> numClients;

        for (int i = 0; i < numClients; ++i) {
            string name;
            double balance;
            cout << "����i�� i�'� ��i����: ";
            cin >> name;
            cout << "����i�� ������ ��i����: ";
            cin >> balance;
            Client client(name, balance);

            int numDeposits;
            cout << "����i�� �i���i��� �����i�: ";
            cin >> numDeposits;

            for (int j = 0; j < numDeposits; ++j) {
                Deposit deposit;
                cout << "����i�� ��� ������: ";
                cin >> deposit.type;
                cout << "����i�� ���� ������: ";
                cin >> deposit.amount;
                cout << "����i�� ��������� ������: ";
                cin >> deposit.interest_rate;
                cout << "����i�� ����� ������ (� �����): ";
                cin >> deposit.duration;
                client.addDeposit(deposit);
            }

            clients.push_back(client);
        }
    } else {
        cout << "���i���� ���i�!" << endl;
        return 1;
    }

    // ��������� ������ ������
    int numStocks;
    cout << "����i�� �i���i��� �i���� �����i�: ";
    cin >> numStocks;

    for (int i = 0; i < numStocks; ++i) {
        string name;
        double price;
        int quantity;
        cout << "����i�� i�'� �i����� ������: ";
        cin >> name;
        cout << "����i�� �i��: ";
        cin >> price;
        cout << "����i�� �i���i���: ";
        cin >> quantity;
        stocks.push_back(Stock(name, price, quantity));
    }

    // ³���������� ����� �����
    cout << "\n=== ���� ����� ===\n";
    printBankState(clients);

    // ��������� ��� �� ���� ������
    double percentIncrease;
    cout << "����i�� �i������ ��i������� �i� �� �i��i ������: ";
    cin >> percentIncrease;
    updateStockPrices(stocks, percentIncrease);

    // ��������� ��������� ���
    cout << "\n=== �������i �i�� �� �i��i ������ ===\n";
    for (const auto& stock : stocks) {
        cout << "�i���� ���i�: " << stock.name << ", �i��: " << stock.price << ", �i���i���: " << stock.quantity << endl;
    }

    // ������� ���������� �������� �� ������� �������� (���� �� ����)
    if (!clients.empty()) {
        cout << "\n���������� �������� �� ������� ��������:\n";
        calculateProfit(clients[0].deposits[0]);
    }

    // ���������� ����� � ����
    string filename;
    cout << "����i�� i�'� ����� ��� ���������� �����: ";
    cin >> filename;
    saveToCSV(filename, clients);

    return 0;
}
