#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

int** input_results(int num, int** arr);
int** random_results(int num, int** arr);
void print_results(int num, int** arr);
int** sum_valuation(int num, int** arr, int** sums);
int index_valuation(int number_of_participant);
void print_table(int** sums, int number_of_participant);
void print_to_file(int** sums, int index);

int** input_results(int num, int** arr) {
    for (int i = 0; i < num; i++) {
        printf("Введите номер участника: ");
        scanf_s("%d", &arr[i][0]);
        for (int j = 1; j < 4; j++) {
            printf("Введите результат участника #%d (попытка %d): ", i + 1, j);
            scanf_s("%d", &arr[i][j]);
        }
    }
    return arr;
}

int** random_results(int num, int** arr) {
    for (int i = 0; i < num; i++) {
        arr[i][0] = i + 1;
        for (int j = 1; j < 4; j++) {
            arr[i][j] = rand() % 100;
        }
    }
    return arr;
}

void print_results(int num, int** arr) {
    printf("\nРезультаты участников:\n");
    printf("+-------------------+-------------------+-------------------+-------------------+\n");
    printf("| Номер участника   | Первый забег      | Второй забег      | Третий забег      |\n");
    printf("+-------------------+-------------------+-------------------+-------------------+\n");
    for (int i = 0; i < num; i++) {
        printf("| %-17d | %-17d | %-17d | %-17d |\n", arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
    }
    printf("+-------------------+-------------------+-------------------+-------------------+\n");
}

int** sum_valuation(int num, int** arr, int** sums) {
    for (int i = 0; i < num; i++) {
        int sum = 0;
        for (int j = 1; j < 4; j++) {
            sum += arr[i][j];
        }
        sums[i][0] = arr[i][0];
        sums[i][1] = sum;
    }
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (sums[j][1] > sums[j + 1][1]) {
                int temp_num = sums[j][0];
                int temp_sum = sums[j][1];
                sums[j][0] = sums[j + 1][0];
                sums[j][1] = sums[j + 1][1];
                sums[j + 1][0] = temp_num;
                sums[j + 1][1] = temp_sum;
            }
        }
    }
    return sums;
}

int index_valuation(int number_of_participant) {
    int percentile;
    printf("Введите процентиль (от 0 до 100): ");
    scanf_s("%d", &percentile);


    int index = ceil((percentile / 100.0) * number_of_participant) - 1;
    if (index < 0) index = 0;
    if (index >= number_of_participant) index = number_of_participant - 1;
    return index;
}

void print_table(int** sums, int number_of_participant) {
    printf("\nРезультаты участников:\n");
    printf("+-------------------+-------------------+\n");
    printf("|  Номер участника  |    Общее время    |\n");
    printf("+-------------------+-------------------+\n");
    for (int i = 0; i < number_of_participant; i++) {
        printf("| %-17d | %-17d |\n", sums[i][0], sums[i][1]);
    }
    printf("+-------------------+-------------------+\n");
}

void print_to_file(int** sums, int index) {
    FILE* file = fopen("C:\\Users\\Admin\\Desktop\\results.txt", "w");
    fprintf(file, "\nРезультаты участников (по убыванию):\n");
    fprintf(file, "+-------------------+-------------------+\n");
    fprintf(file, "| Номер участника   | Сумма баллов      |\n");
    fprintf(file, "+-------------------+-------------------+\n");
    for (int i = 0; i < index; i++) {
        fprintf(file, "| %-17d | %-17d |\n", sums[i][0], sums[i][1]);
    }
    fprintf(file, "+-------------------+-------------------+\n");
    fclose(file);
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int percentile;

    printf("                                +-------------------------------------------------------------+\n");
    printf("                                |                      КУРСОВОЙ ПРОЕКТ                        |\n");
    printf("                                |-------------------------------------------------------------|\n");
    printf("                                |  ТЕМА: ДВУМЕРНЫЕ МАССИВЫ, ПОСТРОЕНИЕ ПРОГРАММЫ ВЫЧИСЛЕНИЯ   |\n");
    printf("                                |    (И АНАЛИЗА) РЕЗУЛЬТАТОВ СОРЕВНОВАНИЙ ПО ВИДАМ СПОРТА     |\n");
    printf("                                |                      (ЛЫЖНЫЕ ГОНКИ)                         |\n");
    printf("                                |                                                             |\n");
    printf("                                |  ВЫПОЛНИЛ:                                   БОГДАНОВ И.П   |\n");
    printf("                                |  ГРУППА:                                         БОИС-242   |\n");
    printf("                                +-------------------------------------------------------------+\n");

    int number_of_participant;
    printf("Приветствую вас в программе для расчёта результатов турнира по лыжным гонкам, введите кол-во спортсменов:\n");
    scanf_s("%d", &number_of_participant);

    int** arr = (int**)malloc(number_of_participant * sizeof(int*));
    for (int i = 0;i < number_of_participant;i++) {
        arr[i] = (int*)malloc(4 * sizeof(int));
    }

    int** sums = (int**)malloc(number_of_participant * sizeof(int*));
    for (int i = 0;i < number_of_participant;i++) {
        sums[i] = (int*)malloc(2 * sizeof(int));
    }

    arr = random_results(number_of_participant, arr);

    int choice;
    short is_running = 1;
    int index;
    int a;
    while (is_running == 1) {
        printf("Нажмите 0 чтобы вывести информацию о программе\n");
        printf("Нажмите 1 чтобы указать данные о спортсменах\n");
        printf("Нажмите 2 чтобы вывести на экран таблицу с результатами\n");
        printf("Нажмите 3 чтобы вывести на экран таблицу общего рейтинга\n");
        printf("Нажмите 4 чтобы вывести на экран участников по процентилю\n");
        printf("Нажмите 5 чтобы вывести результаты в файл\n");
        printf("Нажмите 6 чтобы выйти из программы\n");
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("+-------------------------------------------------------------+\n");
            printf("|                  ИНФОРМАЦИЯ О ПРОГРАММЕ                     |\n");
            printf("|-------------------------------------------------------------|\n");
            printf("|     РАЗРАБОТЧИК: СТУДЕНТ ГРУППЫ БОИС-242 БОГДАНОВ ИЛЬЯ      |\n");
            printf("|     ФУНКЦИОНАЛ: ПОМОЩЬ В СОСТАВЛЕНИИ ОТЧЁТОВ О ТУРНИРАХ     |\n");
            printf("|      ПО ЛЫЖНЫМ ГОНКАМ, ВЫЧИСЛЕНИЕ ЛУЧШИХ СПОРТСМЕНОВ        |\n");
            printf("|                                                             |\n");
            printf("|  ВЕРСИЯ:                                      VERSION 0.1   |\n");
            printf("+-------------------------------------------------------------+\n");
            printf("\n");
            break;
        case 1:
            printf("Введите 1, чтобы заполнить данные вручную или 2, чтобы заполнить рандомно:\n");
            scanf_s("%d", &a);
            if (a == 1) {
                arr = input_results(number_of_participant, arr);
            }
            else {
                arr = random_results(number_of_participant, arr);
            }
            break;
        case 2:
            print_results(number_of_participant, arr);
            break;
        case 3:
            sums = sum_valuation(number_of_participant, arr, sums);
            print_table(sums, number_of_participant);
            break;
        case 4:
            sums = sum_valuation(number_of_participant, arr, sums);
            index = index_valuation(number_of_participant);
            print_table(sums, index);
            break;
        case 5:
            print_to_file(sums, index);
            break;
        case 6:
            is_running = 0;
            break;
        default:
            break;
        }
    }

    for (int i = 0; i < number_of_participant; i++) {
        free(arr[i]);
    }
    free(arr);
}
