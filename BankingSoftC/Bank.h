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

extern Bank init_bank(double initial_cash);

extern void add_client(Bank* bank, char* name, double initial_deposit, double deposit_rate, int duration);

extern void add_security(Bank* bank, char* name, double price, int quantity, char* type);

extern void update_securities(Bank* bank);

extern void buy_security(Bank* bank, char* name, int quantity);

extern void sell_security(Bank* bank, char* name, int quantity);

extern void update_client_deposits(Bank* bank);

extern void save_to_csv(Bank* bank, const char* filename);

extern void load_from_csv(Bank* bank, const char* filename);

extern void print_bank_state(Bank* bank);

extern void free_bank(Bank* bank);

#endif
