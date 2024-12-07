#include "Bank.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
using namespace std;

// ������� ��� ���������� �������� �� ������
void calculateProfit(const Deposit& deposit) {
    double profit = deposit.amount * deposit.interest_rate * deposit.duration / 100;
    cout << "�������� �� ������: " << profit << endl;
}

// ������� ��� ���������� ����� � CSV
void saveToCSV(const string& filename, const vector<Client>& clients) {
    ofstream file(filename);
    for (const auto& client : clients) {
        file << "Client name: " << quoted(client.name) << ","
             << client.balance << "\n";
        for (const auto& deposit : client.deposits) {
            file << quoted(deposit.type) << ","
                 << deposit.amount << ","
                 << deposit.interest_rate << ","
                 << deposit.duration << "\n";
        }
    }
}

// ������� ��� ������������ ����� � CSV
void loadFromCSV(const string& filename, vector<Client>& clients) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Client client;
        getline(ss, client.name, ',');
        ss >> client.balance;
        clients.push_back(client);
        while (getline(file, line)) {
            stringstream depositStream(line);
            Deposit deposit;
            getline(depositStream, deposit.type, ',');
            depositStream >> deposit.amount >> deposit.interest_rate >> deposit.duration;
            client.addDeposit(deposit);
        }
    }
}

// ������� ��� ��������� ����� �����
void printBankState(const vector<Client>& clients) {
    for (const auto& client : clients) {
        client.displayClientInfo();
        cout << "=============================\n";
    }
}

// ������� ��� ���� ���� ������ ������
void updateStockPrices(vector<Stock>& stocks, double percentIncrease) {
    for (auto& stock : stocks) {
        stock.price += stock.price * percentIncrease / 100;
    }
}

// ������� ��� ������� ������ ������
void buyStock(vector<Stock>& stocks, const string& stockName, double price, int quantity) {
    stocks.push_back(Stock(stockName, price, quantity));
}

// ������� ��� ������� ������ ������
void sellStock(vector<Stock>& stocks, const string& stockName, int quantity) {
    for (auto& stock : stocks) {
        if (stock.name == stockName && stock.quantity >= quantity) {
            stock.quantity -= quantity;
            break;
        }
    }
}
