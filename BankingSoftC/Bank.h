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

/* Function to initialize the bank with initial cash
 * @param[in] initial_cash Початкова сума готівки для банку
 * @result Bank структура, ініціалізована з готівкою
 */
extern Bank init_bank(double initial_cash);

/* Function to add a client to the bank
 * @param[in,out] bank Вказівник на структуру Bank
 * @param[in] name Ім'я клієнта
 * @param[in] initial_deposit Початковий депозит
 * @param[in] deposit_rate Процентна ставка депозиту
 * @param[in] duration Термін депозиту в місяцях
 * @result void
 */
extern void add_client(Bank* bank, char* name, double initial_deposit, double deposit_rate, int duration);

/* Function to add a security to the bank
 * @param[in,out] bank Вказівник на структуру Bank
 * @param[in] name Назва цінного паперу
 * @param[in] price Ціна цінного паперу
 * @param[in] quantity Кількість цінного паперу
 * @param[in] type Тип цінного паперу (наприклад, акція, облігація)
 * @result void
 */
extern void add_security(Bank* bank, char* name, double price, int quantity, char* type);

/* Function to update the prices of securities in the bank
 * Ціни змінюються випадковим чином у діапазоні від -10% до +10%
 * @param[in,out] bank Вказівник на структуру Bank
 * @result void
 */
extern void update_securities(Bank* bank);

/* Function to buy a security from the bank
 * @param[in,out] bank Вказівник на структуру Bank
 * @param[in] name Назва цінного паперу для покупки
 * @param[in] quantity Кількість для покупки
 * @result void
 */
extern void buy_security(Bank* bank, char* name, int quantity);

/* Function to sell a security from the bank
 * @param[in,out] bank Вказівник на структуру Bank
 * @param[in] name Назва цінного паперу для продажу
 * @param[in] quantity Кількість для продажу
 * @result void
 */
extern void sell_security(Bank* bank, char* name, int quantity);

/* Function to update deposits of all clients
 * @param[in,out] bank Вказівник на структуру Bank
 * @result void
 */
extern void update_client_deposits(Bank* bank);

/* Function to save bank data to a CSV file
 * @param[in] bank Вказівник на структуру Bank
 * @param[in] filename Назва CSV файлу
 * @result void
 */
extern void save_to_csv(Bank* bank, const char* filename);

/* Function to load bank data from a CSV file
 * @param[in,out] bank Вказівник на структуру Bank
 * @param[in] filename Назва CSV файлу
 * @result void
 */
extern void load_from_csv(Bank* bank, const char* filename);

/* Function to print the current state of the bank to the console
 * @param[in] bank Вказівник на структуру Bank
 * @result void
 */
extern void print_bank_state(Bank* bank);

/* Function to free allocated memory for the bank
 * @param[in,out] bank Вказівник на структуру Bank
 * @result void
 */
extern void free_bank(Bank* bank);

#endif
