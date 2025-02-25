#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>

/* Base structure of Client */
typedef struct Client {
    char name[50];          ///< Ім'я клієнта
    double balance;         ///< Баланс клієнта
    double deposit_rate;    ///< Процентна ставка депозиту
    int deposit_duration;   ///< Термін депозиту (місяців)
} Client;

/* Base structure of Security */
typedef struct Security {
    char name[50];          ///< Назва цінного паперу
    double price;           ///< Ціна цінного паперу
    int quantity;           ///< Кількість цінного паперу
    char type[20];          ///< Тип цінного паперу (наприклад, акція, облігація)
} Security;

/* Base structure of Bank */
typedef struct Bank {
    double cash;            ///< Готівка банку
    Client* clients;        ///< Масив клієнтів
    int client_count;       ///< Кількість клієнтів
    Security* securities;   ///< Масив цінних паперів
    int security_count;     ///< Кількість цінних паперів
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
