#include "Bank.h"
#include <string.h>
#include <time.h>

// Ініціалізація банку з початковою сумою готівки
Bank init_bank(double initial_cash) {
    Bank bank;
    bank.cash = initial_cash;       // "Початковий баланс банку"
    bank.client_count = 0;         // "Кількість клієнтів"
    bank.clients = NULL;           // "Масив клієнтів (поки що порожній)"
    bank.security_count = 0;       // "Кількість цінних паперів"
    bank.securities = NULL;        // "Масив цінних паперів (поки що порожній)"
    return bank;
}

// Додавання нового клієнта до банку
void add_client(Bank* bank, char* name, double initial_deposit, double deposit_rate, int duration) {
    // Виділення додаткової пам'яті для нового клієнта

    bank->clients = realloc(bank->clients, (bank->client_count + 1) * sizeof(Client));
    // "Збереження інформації про клієнта"

    strcpy(bank->clients[bank->client_count].name, name);
    bank->clients[bank->client_count].balance = initial_deposit;
    bank->clients[bank->client_count].deposit_rate = deposit_rate;
    bank->clients[bank->client_count].deposit_duration = duration;
    bank->client_count++;         // "Збільшення кількості клієнтів"
    bank->cash += initial_deposit; // "Збільшення готівки банку"
}

// Додавання нового цінного паперу до банку
void add_security(Bank* bank, char* name, double price, int quantity, char* type) {
    // "Виділення додаткової пам'яті для нового цінного паперу"
    bank->securities = realloc(bank->securities, (bank->security_count + 1) * sizeof(Security));
    // "Збереження інформації про цінний папір"
    strcpy(bank->securities[bank->security_count].name, name);
    bank->securities[bank->security_count].price = price;
    bank->securities[bank->security_count].quantity = quantity;
    strcpy(bank->securities[bank->security_count].type, type);
    bank->security_count++;       // "Збільшення кількості цінних паперів"
}

// Оновлення цін цінних паперів у банку
void update_securities(Bank* bank) {
    for (int i = 0; i < bank->security_count; i++) {
        // "Випадкова зміна ціни в межах від -10% до +10%"
        double change = (rand() % 2001 - 1000) / 10000.0;
        bank->securities[i].price += bank->securities[i].price * change;
    }
}

// Покупка цінного паперу банком
void buy_security(Bank* bank, char* name, int quantity) {
    for (int i = 0; i < bank->security_count; i++) {
        if (strcmp(bank->securities[i].name, name) == 0 && bank->securities[i].quantity >= quantity) {
            double cost = bank->securities[i].price * quantity;      // "Загальна вартість покупки"
            if (bank->cash >= cost) {                               // "Перевірка, чи вистачає готівки"
                bank->securities[i].quantity -= quantity;            // "Зменшення кількості доступних паперів"
                bank->cash -= cost;                               // "Зменшення готівки банку"
                printf("\nБанк купив %d одиниць %s.\n", quantity, name);
                return;
            }
        }
    }
    printf("\nЦiнний папiр %s недоступний або недостатня кiлькiсть.\n", name);
}

// Продаж цінного паперу банком
void sell_security(Bank* bank, char* name, int quantity) {
    for (int i = 0; i < bank->security_count; i++) {
        if (strcmp(bank->securities[i].name, name) == 0) {
            bank->securities[i].quantity += quantity; // "Збільшення кількості паперів у банку"
            bank->cash += bank->securities[i].price * quantity; // "Збільшення готівки банку"
            printf("\nБанк продав %d одиниць %s.\n", quantity, name);
            return;
        }
    }
    printf("\nЦiнний папiр %s не знайдено.\n", name);
}

// Оновлення депозитів для всіх клієнтів
void update_client_deposits(Bank* bank) {
    for (int i = 0; i < bank->client_count; i++) {
        // "Розрахунок місячної процентної ставки"
        double monthly_rate = bank->clients[i].deposit_rate / 12.0;
        // "Додавання відсотків до балансу клієнта"
        bank->clients[i].balance += bank->clients[i].balance * monthly_rate;
    }
}

// Збереження даних банку у CSV-файл
void save_to_csv(Bank* bank, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("\nНе вдалося вiдкрити файл %s для запису.\n", filename);
        return;
    }

    // "Запис заголовків таблиці"
    fprintf(file, "Name | Balance | DepositRate | DepositDuration |\n");
    for (int i = 0; i < bank->client_count; i++) {
        // "Запис даних клієнтів"
        fprintf(file, "%s | %.2f |%.2f | %d |\n", bank->clients[i].name, bank->clients[i].balance,
                bank->clients[i].deposit_rate, bank->clients[i].deposit_duration);
    }
    fclose(file);
}

// Завантаження даних банку з CSV-файлу
void load_from_csv(Bank* bank, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nНе вдалося вiдкрити файл %s для читання.\n", filename);
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strlen(buffer) < 5) continue; // "Пропустити порожні рядки"

        char name[50];
        double balance, rate;
        int duration;

        // "Зчитування даних про клієнта"
        if (sscanf(buffer, "%49[^,],%lf,%lf,%d", name, &balance, &rate, &duration) == 4) {
            add_client(bank, name, balance, rate, duration);
        }
    }

    fclose(file);
}

// Виведення стану банку в консоль
void print_bank_state(Bank* bank) {
    printf("\n========= Стан банку =========\n");
    printf("Готiвка банку: %.2f\n", bank->cash);

    printf("\n========= Цiннi папери =========\n");
    if (bank->security_count == 0) {
        printf("Iнформацiя про цiннi папери вiдсутня.\n");
    } else {
        for (int i = 0; i < bank->security_count; i++) {
            printf("Тип: %s | Назва: %s | Цiна: %.2f | Кiлькiсть: %d\n",
                   bank->securities[i].type, bank->securities[i].name,
                   bank->securities[i].price, bank->securities[i].quantity);
        }
    }

    printf("\n========= Клiєнти =========\n");
    if (bank->client_count == 0) {
        printf("Iнформацiя про клiєнтiв вiдсутня.\n");
    } else {
        for (int i = 0; i < bank->client_count; i++) {
            printf("Клiєнт: %s | Баланс: %.2f | Процентна ставка: %.2f | Тривалiсть депозиту: %d мiсяцiв\n",
                   bank->clients[i].name, bank->clients[i].balance,
                   bank->clients[i].deposit_rate, bank->clients[i].deposit_duration);
        }
    }
}


// Звільнення пам'яті, виділеної для банку
void free_bank(Bank* bank) {
    if (bank->clients) free(bank->clients);       // "Звільнення пам'яті для клієнтів"
    if (bank->securities) free(bank->securities); // "Звільнення пам'яті для цінних паперів"
}
