#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ��������� ��� ������
struct Deposit {
    string type;         // ��� ������
    double amount;       // ����
    double interest_rate; // ��������� ������
    int duration;         // ����� (� �����)

    Deposit() : type("����i�����"), amount(0), interest_rate(0), duration(0) {}
};

// ���� ��� �볺���
class Client {
public:
    string name;                 // ��'� �볺���
    double balance;              // ������ �볺���
    vector<Deposit> deposits;   // ������ ������

    Client(string n = "", double b = 0) : name(n), balance(b) {}

    void addDeposit(const Deposit& deposit) {
        deposits.push_back(deposit);
    }

    void displayClientInfo() const {
        cout << "��i���: " << name << "\n������: " << balance << "\n������:\n";
        for (const auto& deposit : deposits) {
            cout << "���: " << deposit.type << ", ����: " << deposit.amount
                 << ", ��������� ������: " << deposit.interest_rate
                 << "%, �����: " << deposit.duration << " ���i�\n";
        }
    }
};

// ��������� ��� ������� ������
struct Stock {
    string name;     // ��'� ������� ������
    double price;    // ������� ����
    int quantity;    // ʳ������

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
