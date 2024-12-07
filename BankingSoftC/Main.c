#include <stdio.h>
#include "Bank.h"
#include <locale.h>
int main() {
    setlocale(LC_CTYPE,"rus");
    // ����������� �����
    double initial_cash = 1000000; //��������� ���� ���i��� ��� �����

    Bank bank = init_bank(initial_cash);

    // ����
    int choice;
    do {
        printf("\n====================\n");
        printf("       ����\n");
        printf("====================\n");
        printf("\n1. ������ ��i����\n");
        printf("\n2. ������ �i���� ���i�\n");
        printf("3. ������� �i�� �i���� �����i�\n");
        printf("4. ������ �i���� ���i�\n");
        printf("5. ������� �i���� ���i�\n");
        printf("\n6. ������� �������� ��i���i�\n");
        printf("7. ������� ���� �����\n");
        printf("\n8. �������� ���i ����� � ����\n");
        printf("9. ����������� ���i ����� � �����\n");
        printf("\n0. ���i�\n");
        printf("\n====================\n");
        printf("��� ���i�: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[50];
                double deposit, rate;
                int duration;
                printf("\n====================\n");
                printf("\n����i�� i�'� ��i����: ");
                scanf("%s", name);
                printf("\n����i�� ���������� �������: ");
                scanf("%lf", &deposit);
                printf("\n����i�� �i��� �i�������� ������: ");
                scanf("%lf", &rate);
                printf("\n����i�� ����� �������� (�i���i�): ");
                scanf("%d", &duration);
                add_client(&bank, name, deposit, rate, duration);
                break;
            }
            case 2: {
                char name[50], type[20];
                double price;
                int quantity;
                printf("\n====================\n");
                printf("\n����i�� ����� �i����� ������: ");
                scanf("%s", name);
                printf("\n����i�� �i��: ");
                scanf("%lf", &price);
                printf("\n����i�� �i���i���: ");
                scanf("%d", &quantity);
                printf("\n����i�� ��� (���i�(Stock)/���i���i�(Bond)): ");
                scanf("%s", type);
                add_security(&bank, name, price, quantity, type);
                break;
            }
            case 3:
                update_securities(&bank);
                printf("�i�� �i���� �����i� ��������.\n");
                break;
            case 4: {
                char name[50];
                int quantity;
                printf("\n====================\n");
                printf("����i�� ����� �i����� ������ ��� �������: ");
                scanf("%s", name);
                printf("����i�� �i���i��� ��� �������: ");
                scanf("%d", &quantity);
                buy_security(&bank, name, quantity);
                break;
            }
            case 5: {
                char name[50];
                int quantity;
                printf("\n====================\n");
                printf("����i�� ����� �i����� ������ ��� �������: ");
                scanf("%s", name);
                printf("����i�� �i���i��� ��� �������: ");
                scanf("%d", &quantity);
                sell_security(&bank, name, quantity);
                break;
            }
            case 6:
                update_client_deposits(&bank);
                printf("�������� ��i���i� ��������.\n");
                break;
            case 7:
                print_bank_state(&bank);
                break;
            case 8: {
                char filename[50];
                printf("\n====================\n");
                printf("����i�� ����� ����� ��� ����������: ");
                scanf("%s", filename);
                save_to_csv(&bank, filename);
                break;
            }
            case 9: {
                char filename[50];
                printf("\n====================\n");
                printf("����i�� ����� �����: ");
                scanf("%s", filename);
                load_from_csv(&bank, filename);
                print_bank_state(&bank);
                break;

            }
            case 0:
                printf("���������� ��������.\n");
                break;
            default:
                printf("\n===============================\n");
                printf("���i���� ���i�, ��������� �� ���.\n");
                printf("\n===============================\n");
        }
    } while (choice != 0);

    // ��������� ���'��
    free_bank(&bank);
    return 0;
}
