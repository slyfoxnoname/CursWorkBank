#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>

/* Base structure of Client */
typedef struct Client {
    char name[50];          ///< ��'� �볺���
    double balance;         ///< ������ �볺���
    double deposit_rate;    ///< ��������� ������ ��������
    int deposit_duration;   ///< ����� �������� (������)
} Client;

/* Base structure of Security */
typedef struct Security {
    char name[50];          ///< ����� ������� ������
    double price;           ///< ֳ�� ������� ������
    int quantity;           ///< ʳ������ ������� ������
    char type[20];          ///< ��� ������� ������ (���������, �����, ��������)
} Security;

/* Base structure of Bank */
typedef struct Bank {
    double cash;            ///< ������ �����
    Client* clients;        ///< ����� �볺���
    int client_count;       ///< ʳ������ �볺���
    Security* securities;   ///< ����� ������ ������
    int security_count;     ///< ʳ������ ������ ������
} Bank;

/*============ Functions for working with Bank ============*/

/* Function to initialize the bank with initial cash
 * @param[in] initial_cash ��������� ���� ������ ��� �����
 * @result Bank ���������, ������������ � �������
 */
extern Bank init_bank(double initial_cash);

/* Function to add a client to the bank
 * @param[in,out] bank �������� �� ��������� Bank
 * @param[in] name ��'� �볺���
 * @param[in] initial_deposit ���������� �������
 * @param[in] deposit_rate ��������� ������ ��������
 * @param[in] duration ����� �������� � ������
 * @result void
 */
extern void add_client(Bank* bank, char* name, double initial_deposit, double deposit_rate, int duration);

/* Function to add a security to the bank
 * @param[in,out] bank �������� �� ��������� Bank
 * @param[in] name ����� ������� ������
 * @param[in] price ֳ�� ������� ������
 * @param[in] quantity ʳ������ ������� ������
 * @param[in] type ��� ������� ������ (���������, �����, ��������)
 * @result void
 */
extern void add_security(Bank* bank, char* name, double price, int quantity, char* type);

/* Function to update the prices of securities in the bank
 * ֳ�� ��������� ���������� ����� � ������� �� -10% �� +10%
 * @param[in,out] bank �������� �� ��������� Bank
 * @result void
 */
extern void update_securities(Bank* bank);

/* Function to buy a security from the bank
 * @param[in,out] bank �������� �� ��������� Bank
 * @param[in] name ����� ������� ������ ��� �������
 * @param[in] quantity ʳ������ ��� �������
 * @result void
 */
extern void buy_security(Bank* bank, char* name, int quantity);

/* Function to sell a security from the bank
 * @param[in,out] bank �������� �� ��������� Bank
 * @param[in] name ����� ������� ������ ��� �������
 * @param[in] quantity ʳ������ ��� �������
 * @result void
 */
extern void sell_security(Bank* bank, char* name, int quantity);

/* Function to update deposits of all clients
 * @param[in,out] bank �������� �� ��������� Bank
 * @result void
 */
extern void update_client_deposits(Bank* bank);

/* Function to save bank data to a CSV file
 * @param[in] bank �������� �� ��������� Bank
 * @param[in] filename ����� CSV �����
 * @result void
 */
extern void save_to_csv(Bank* bank, const char* filename);

/* Function to load bank data from a CSV file
 * @param[in,out] bank �������� �� ��������� Bank
 * @param[in] filename ����� CSV �����
 * @result void
 */
extern void load_from_csv(Bank* bank, const char* filename);

/* Function to print the current state of the bank to the console
 * @param[in] bank �������� �� ��������� Bank
 * @result void
 */
extern void print_bank_state(Bank* bank);

/* Function to free allocated memory for the bank
 * @param[in,out] bank �������� �� ��������� Bank
 * @result void
 */
extern void free_bank(Bank* bank);

#endif
