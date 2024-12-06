#include <stdio.h>
#include "Bank.h"
#include <locale.h>
int main() {
    setlocale(LC_CTYPE,"rus");
    // Ініціалізація банку
    double initial_cash = 1000000; //початкова сума готiвки для банку

    Bank bank = init_bank(initial_cash);

    // Меню
    int choice;
    do {
        printf("\n====================\n");
        printf("       МЕНЮ\n");
        printf("====================\n");
        printf("\n1. Додати клiєнта\n");
        printf("\n2. Додати цiнний папiр\n");
        printf("3. Оновити цiни цiнних паперiв\n");
        printf("4. Купити цiнний папiр\n");
        printf("5. Продати цiнний папiр\n");
        printf("\n6. Оновити депозити клiєнтiв\n");
        printf("7. Вивести стан банку\n");
        printf("\n8. Зберегти данi банку у файл\n");
        printf("9. Завантажити данi банку з файлу\n");
        printf("\n0. Вихiд\n");
        printf("\n====================\n");
        printf("Ваш вибiр: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[50];
                double deposit, rate;
                int duration;
                printf("\n====================\n");
                printf("\nВведiть iм'я клiєнта: ");
                scanf("%s", name);
                printf("\nВведiть початковий депозит: ");
                scanf("%lf", &deposit);
                printf("\nВведiть рiчну вiдсоткову ставку: ");
                scanf("%lf", &rate);
                printf("\nВведiть строк депозиту (мiсяцiв): ");
                scanf("%d", &duration);
                add_client(&bank, name, deposit, rate, duration);
                break;
            }
            case 2: {
                char name[50], type[20];
                double price;
                int quantity;
                printf("\n====================\n");
                printf("\nВведiть назву цiнного паперу: ");
                scanf("%s", name);
                printf("\nВведiть цiну: ");
                scanf("%lf", &price);
                printf("\nВведiть кiлькiсть: ");
                scanf("%d", &quantity);
                printf("\nВведiть тип (акцiя(Stock)/облiгацiя(Bond)): ");
                scanf("%s", type);
                add_security(&bank, name, price, quantity, type);
                break;
            }
            case 3:
                update_securities(&bank);
                printf("Цiни цiнних паперiв оновлено.\n");
                break;
            case 4: {
                char name[50];
                int quantity;
                printf("\n====================\n");
                printf("Введiть назву цiнного паперу для покупки: ");
                scanf("%s", name);
                printf("Введiть кiлькiсть для покупки: ");
                scanf("%d", &quantity);
                buy_security(&bank, name, quantity);
                break;
            }
            case 5: {
                char name[50];
                int quantity;
                printf("\n====================\n");
                printf("Введiть назву цiнного паперу для продажу: ");
                scanf("%s", name);
                printf("Введiть кiлькiсть для продажу: ");
                scanf("%d", &quantity);
                sell_security(&bank, name, quantity);
                break;
            }
            case 6:
                update_client_deposits(&bank);
                printf("Депозити клiєнтiв оновлено.\n");
                break;
            case 7:
                print_bank_state(&bank);
                break;
            case 8: {
                char filename[50];
                printf("\n====================\n");
                printf("Введiть назву файлу для збереження: ");
                scanf("%s", filename);
                save_to_csv(&bank, filename);
                break;
            }
            case 9: {
                char filename[50];
                printf("\n====================\n");
                printf("Введiть назву файлу: ");
                scanf("%s", filename);
                load_from_csv(&bank, filename);
                print_bank_state(&bank);
                break;

            }
            case 0:
                printf("Завершення програми.\n");
                break;
            default:
                printf("\n===============================\n");
                printf("Невiрний вибiр, спробуйте ще раз.\n");
                printf("\n===============================\n");
        }
    } while (choice != 0);

    // Звільнення пам'яті
    free_bank(&bank);
    return 0;
}
