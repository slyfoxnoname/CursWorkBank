#include "Bank.h"
#include <iostream>
using namespace std;

int main() {
    // ��������� �볺���
    Client client1("���������", 10000);
    Client client2("���i�", 15000);

    // ��������� ������ �볺����
    Deposit deposit("����i�����", 5000, 5.0, 2); // 5% �� 2 ����
    Deposit deposit("����i�����", 3000, 4.0, 3);   // 4% �� 3 ����

    client1.addDeposit(deposit1);
    client2.addDeposit(deposit2);

    // ��������� ���������� ��� �볺���
    cout << "=== ���������� ���� ����� ===" << endl;
    vector<Client> clients = {client1, client2};
    printBankState(clients);

    // ���������� �������� �� ������
    cout << "=== ���������� �������� ===" << endl;
    calculateProfit(deposit1);
    calculateProfit(deposit2);

    // ������ � ������� ��������
    vector<Stock> stocks;
    buyStock(stocks, "���i� Apple", 150.0, 10);
    buyStock(stocks, "���i� Tesla", 250.0, 5);

    cout << "\n=== ��������� �i� �i���� �����i� ===" << endl;
    updateStockPrices(stocks, 10.0); // ϳ�������� ���� �� 10%
    for (const auto& stock : stocks) {
        cout << "�����: " << stock.name << ", �i��: " << stock.price
             << ", �i���i���: " << stock.quantity << endl;
    }

    // ���������� ����� � CSV
    cout << "\n=== ���������� � CSV ===" << endl;
    saveToCSV("clients.csv", clients);

    // ������������ ����� �� CSV
    cout << "\n=== ������������ � CSV ===" << endl;
    vector<Client> loadedClients;
    loadFromCSV("clients.csv", loadedClients);
    printBankState(loadedClients);

    return 0;
}
