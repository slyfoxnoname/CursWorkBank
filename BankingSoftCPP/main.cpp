#include "Bank.h"
using namespace std;

int main() {
    setlocale(LC_CTYPE, "");
    vector<Client> clients;
    vector<Stock> stocks;
    int choice;

    cout << "�����i�� ������i�\n";
    cout << "====================\n";
    cout << "1. ����������� ���i � �����\n";
    cout << "2. ������ ���i ������\n"
         << "====================\n" << "����i�� �����: ";
    cin >> choice;

    if (choice == 1) {
        string filename;
        cout << "����i�� i�'� ����� ��� ������������: ";
        cin >> filename;
        loadFromCSV(filename, clients);
        printBankState(clients);
    } else if (choice == 2) {
        int numClients = 0;
        // �������� �� ������� �볺���
        while (numClients <= 0) {
            cout << "\n====================\n";
            cout << "����i�� �i���i��� ��i���i�: ";
            cin >> numClients;
            if (numClients <= 0) {
                cout << "�i���i��� ��i���i� ������� ���� �i����� �� 0.\n";
            }
        }

        // ˳������� �볺���
        int clientCount = 0;
        for (int i = 0; i < numClients; ++i) {
            string name;
            double balance;
            cout << "\n====================\n";
            cout << "��i��� �" << clientCount + 1 << "\n";
            cout << "����i�� i�'� ��i���� ��� ����i�i�: ";
            cin >> name;
            cout << "����i�� ������ ��i����: ";
            cin >> balance;
            Client client(name, balance);
            clientCount++;

            int numDeposits;
            cout << "����i�� �i���i��� �����i�: ";
            cin >> numDeposits;

            // ˳������� ������ ��� ������� �볺���
            int depositCount = 0;

            for (int j = 0; j < numDeposits; ++j) {
                Deposit deposit;
                cout << "\n====================\n";
                cout << "����� �" << depositCount + 1 << "\n";
                cout << "����i�� ��� ������: ";
                cin >> deposit.type;
                cout << "����i�� ���� ������: ";
                cin >> deposit.amount;
                cout << "����i�� ��������� ������: ";
                cin >> deposit.interest_rate;
                cout << "����i�� ����� ������ (� �����): ";
                cin >> deposit.duration;
                client.addDeposit(deposit);
                depositCount++; // �������� �������� ������
            }

            clients.push_back(client);
        }
    } else {
        cout << "\n���i���� ���i�!" << endl;
        return 1;
    }

    // ��������� ������ ������
    int numStocks;
    cout << "\n====================\n";
    cout << "����i�� �i���i��� �i���� �����i�: ";
    cin >> numStocks;

    for (int i = 0; i < numStocks; ++i) {
        string name;
        double price;
        int quantity;
        cout << "\n====================\n";
        if (numStocks > 1) {
            cout << "�i���� ���i� �" << i + 1 << ":\n";
        }
        cout << "����i�� i�'� �i����� ������: ";
        cin >> name;
        cout << "����i�� �i��: ";
        cin >> price;
        cout << "����i�� �i���i���: ";
        cin >> quantity;
        stocks.push_back(Stock(name, price, quantity));
    }

    // ³���������� ����� �����
    cout << "\n========= ���� ����� =========\n";
    printBankState(clients);

    // ��������� ��� �� ���� ������
    double percentIncrease;
    cout << "\n����i�� �i������ ��i������� �i� �� �i��i ������: ";
    cin >> percentIncrease;
    updateStockPrices(stocks, percentIncrease);

    // ��������� ��������� ���
    cout << "\n=== �������i �i�� �� �i��i ������ ===\n";
    for (const auto& stock : stocks) {
        cout << "�i���� ���i�: " << stock.name << ", �i��: " << stock.price << ", �i���i���: " << stock.quantity << endl;
    }

    // ������� ���������� �������� �� ������� �������� (���� �� ����)
    if (!clients.empty() && !clients[0].deposits.empty()) {
        cout << "\n���������� �������� �� ������� ��������:\n";
        calculateProfit(clients[0].deposits[0]);
    }

    // ���������� ����� � ����
    string filename;
    int answer;
    cout << "=============================\n";
    cout << "\n������ �������� ����i � ����?\n" << "1. ���, �������� � ����.\n" << "2. �i, �� ����i����.\n" << "����i�� �����: ";
    cin >> answer;

    if (answer == 1) {
        cout << "����i�� i�'� ����� ��� ���������� �����: ";
        cin >> filename;
        saveToCSV(filename, clients);
    } else if (answer == 2) {
        cout << "��� �� ��������.\n";
    } else {
        cout << "������� ����. �������� �����������.\n";
    }

    return 0;
}
