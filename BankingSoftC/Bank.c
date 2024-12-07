#include "Bank.h"
#include <string.h>
#include <time.h>

// ����������� ����� � ���������� ����� ������
Bank init_bank(double initial_cash) {
    Bank bank;
    bank.cash = initial_cash;       // "���������� ������ �����"
    bank.client_count = 0;         // "ʳ������ �볺���"
    bank.clients = NULL;           // "����� �볺��� (���� �� �������)"
    bank.security_count = 0;       // "ʳ������ ������ ������"
    bank.securities = NULL;        // "����� ������ ������ (���� �� �������)"
    return bank;
}

// ��������� ������ �볺��� �� �����
void add_client(Bank* bank, char* name, double initial_deposit, double deposit_rate, int duration) {
    // �������� ��������� ���'�� ��� ������ �볺���

    bank->clients = realloc(bank->clients, (bank->client_count + 1) * sizeof(Client));
    // "���������� ���������� ��� �볺���"

    strcpy(bank->clients[bank->client_count].name, name);
    bank->clients[bank->client_count].balance = initial_deposit;
    bank->clients[bank->client_count].deposit_rate = deposit_rate;
    bank->clients[bank->client_count].deposit_duration = duration;
    bank->client_count++;         // "��������� ������� �볺���"
    bank->cash += initial_deposit; // "��������� ������ �����"
}

// ��������� ������ ������� ������ �� �����
void add_security(Bank* bank, char* name, double price, int quantity, char* type) {
    // "�������� ��������� ���'�� ��� ������ ������� ������"
    bank->securities = realloc(bank->securities, (bank->security_count + 1) * sizeof(Security));
    // "���������� ���������� ��� ������ ����"
    strcpy(bank->securities[bank->security_count].name, name);
    bank->securities[bank->security_count].price = price;
    bank->securities[bank->security_count].quantity = quantity;
    strcpy(bank->securities[bank->security_count].type, type);
    bank->security_count++;       // "��������� ������� ������ ������"
}

// ��������� ��� ������ ������ � �����
void update_securities(Bank* bank) {
    for (int i = 0; i < bank->security_count; i++) {
        // "��������� ���� ���� � ����� �� -10% �� +10%"
        double change = (rand() % 2001 - 1000) / 10000.0;
        bank->securities[i].price += bank->securities[i].price * change;
    }
}

// ������� ������� ������ ������
void buy_security(Bank* bank, char* name, int quantity) {
    for (int i = 0; i < bank->security_count; i++) {
        if (strcmp(bank->securities[i].name, name) == 0 && bank->securities[i].quantity >= quantity) {
            double cost = bank->securities[i].price * quantity;      // "�������� ������� �������"
            if (bank->cash >= cost) {                               // "��������, �� ������� ������"
                bank->securities[i].quantity -= quantity;            // "��������� ������� ��������� ������"
                bank->cash -= cost;                               // "��������� ������ �����"
                printf("\n���� ����� %d ������� %s.\n", quantity, name);
                return;
            }
        }
    }
    printf("\n�i���� ���i� %s ����������� ��� ���������� �i���i���.\n", name);
}

// ������ ������� ������ ������
void sell_security(Bank* bank, char* name, int quantity) {
    for (int i = 0; i < bank->security_count; i++) {
        if (strcmp(bank->securities[i].name, name) == 0) {
            bank->securities[i].quantity += quantity; // "��������� ������� ������ � �����"
            bank->cash += bank->securities[i].price * quantity; // "��������� ������ �����"
            printf("\n���� ������ %d ������� %s.\n", quantity, name);
            return;
        }
    }
    printf("\n�i���� ���i� %s �� ��������.\n", name);
}

// ��������� �������� ��� ��� �볺���
void update_client_deposits(Bank* bank) {
    for (int i = 0; i < bank->client_count; i++) {
        // "���������� ������ ��������� ������"
        double monthly_rate = bank->clients[i].deposit_rate / 12.0;
        // "��������� ������� �� ������� �볺���"
        bank->clients[i].balance += bank->clients[i].balance * monthly_rate;
    }
}

// ���������� ����� ����� � CSV-����
void save_to_csv(Bank* bank, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("\n�� ������� �i������ ���� %s ��� ������.\n", filename);
        return;
    }

    // "����� ��������� �������"
    fprintf(file, "Name | Balance | DepositRate | DepositDuration |\n");
    for (int i = 0; i < bank->client_count; i++) {
        // "����� ����� �볺���"
        fprintf(file, "%s | %.2f |%.2f | %d |\n", bank->clients[i].name, bank->clients[i].balance,
                bank->clients[i].deposit_rate, bank->clients[i].deposit_duration);
    }
    fclose(file);
}

// ������������ ����� ����� � CSV-�����
void load_from_csv(Bank* bank, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("\n�� ������� �i������ ���� %s ��� �������.\n", filename);
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strlen(buffer) < 5) continue; // "���������� ������ �����"

        char name[50];
        double balance, rate;
        int duration;

        // "���������� ����� ��� �볺���"
        if (sscanf(buffer, "%49[^,],%lf,%lf,%d", name, &balance, &rate, &duration) == 4) {
            add_client(bank, name, balance, rate, duration);
        }
    }

    fclose(file);
}

// ��������� ����� ����� � �������
void print_bank_state(Bank* bank) {
    printf("\n========= ���� ����� =========\n");
    printf("���i��� �����: %.2f\n", bank->cash);

    printf("\n========= �i��i ������ =========\n");
    if (bank->security_count == 0) {
        printf("I�������i� ��� �i��i ������ �i������.\n");
    } else {
        for (int i = 0; i < bank->security_count; i++) {
            printf("���: %s | �����: %s | �i��: %.2f | �i���i���: %d\n",
                   bank->securities[i].type, bank->securities[i].name,
                   bank->securities[i].price, bank->securities[i].quantity);
        }
    }

    printf("\n========= ��i���� =========\n");
    if (bank->client_count == 0) {
        printf("I�������i� ��� ��i���i� �i������.\n");
    } else {
        for (int i = 0; i < bank->client_count; i++) {
            printf("��i���: %s | ������: %.2f | ��������� ������: %.2f | ������i��� ��������: %d �i���i�\n",
                   bank->clients[i].name, bank->clients[i].balance,
                   bank->clients[i].deposit_rate, bank->clients[i].deposit_duration);
        }
    }
}


// ��������� ���'��, ������� ��� �����
void free_bank(Bank* bank) {
    if (bank->clients) free(bank->clients);       // "��������� ���'�� ��� �볺���"
    if (bank->securities) free(bank->securities); // "��������� ���'�� ��� ������ ������"
}
