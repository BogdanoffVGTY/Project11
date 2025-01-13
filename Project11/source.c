#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

int** input_results(int num, int** arr) {
    for (int i = 0; i < num; i++) {
        printf("Введите номер участника: ");
        scanf_s("%d", &arr[i][0]);
        for (int j = 1; j < 4; j++) {
            printf("Ââåäèòå ðåçóëüòàò ó÷àñòíèêà #%d (ïîïûòêà %d): ", i + 1, j);
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
    printf("\nÐåçóëüòàòû ó÷àñòíèêîâ:\n");
    printf("+-------------------+-------------------+-------------------+-------------------+\n");
    printf("| Íîìåð ó÷àñòíèêà   | Ïåðâûé çàáåã      | Âòîðîé çàáåã      | Òðåòèé çàáåã      |\n");
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
    printf("Ââåäèòå ïðîöåíòèëü (îò 0 äî 100): ");
    scanf_s("%d", &percentile);


    int index = ceil((percentile / 100.0) * number_of_participant) - 1;
    if (index < 0) index = 0;
    if (index >= number_of_participant) index = number_of_participant - 1;
    return index;
}

void print_table(int** sums, int number_of_participant) {
    printf("\nÐåçóëüòàòû ó÷àñòíèêîâ:\n");
    printf("+-------------------+-------------------+\n");
    printf("|  Íîìåð ó÷àñòíèêà  |    Îáùåå âðåìÿ    |\n");
    printf("+-------------------+-------------------+\n");
    for (int i = 0; i < number_of_participant; i++) {
        printf("| %-17d | %-17d |\n", sums[i][0], sums[i][1]);
    }
    printf("+-------------------+-------------------+\n");
}

void print_to_file(int** sums, int index) {
    FILE* file = fopen("C:\\Users\\Admin\\Desktop\\results.txt", "w");
    fprintf(file, "\nÐåçóëüòàòû ó÷àñòíèêîâ (ïî óáûâàíèþ):\n");
    fprintf(file, "+-------------------+-------------------+\n");
    fprintf(file, "| Íîìåð ó÷àñòíèêà   | Ñóììà áàëëîâ      |\n");
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
    printf("                                |                      ÊÓÐÑÎÂÎÉ ÏÐÎÅÊÒ                        |\n");
    printf("                                |-------------------------------------------------------------|\n");
    printf("                                |  ÒÅÌÀ: ÄÂÓÌÅÐÍÛÅ ÌÀÑÑÈÂÛ, ÏÎÑÒÐÎÅÍÈÅ ÏÐÎÃÐÀÌÌÛ ÂÛ×ÈÑËÅÍÈß   |\n");
    printf("                                |  (È ÀÍÀËÈÇÀ) ÐÅÇÓËÜÒÀÒÎÂ ÑÎÐÅÂÍÎÂÀÍÈÉ ÏÎ ÂÈÄÀÌ ÑÏÎÐÒÀ       |\n");
    printf("                                |                      (ËÛÆÍÛÅ ÃÎÍÊÈ)                         |\n");
    printf("                                |                                                             |\n");
    printf("                                |  ÂÛÏÎËÍÈË:                                   ÁÎÃÄÀÍÎÂ È.Ï   |\n");
    printf("                                |  ÃÐÓÏÏÀ:                                         ÁÎÈÑ-242   |\n");
    printf("                                +-------------------------------------------------------------+\n");

    int number_of_participant;
    printf("Ïðèâåòñòâóþ âàñ â ïðîãðàììå äëÿ ðàñ÷¸òà ðåçóëüòàòîâ òóðíèðà ïî ëûæíûì ãîíêàì, ââåäèòå êîë-âî ñïîðòñìåíîâ:\n");
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
        printf("Íàæìèòå 0 ÷òîáû âûâåñòè èíôîðìàöèþ î ïðîãðàììå\n");
        printf("Íàæìèòå 1 ÷òîáû óêàçàòü äàííûå î ñïîðòñìåíàõ\n");
        printf("Íàæìèòå 2 ÷òîáû âûâåñòè íà ýêðàí òàáëèöó ñ ðåçóëüòàòàìè\n");
        printf("Íàæìèòå 3 ÷òîáû âûâåñòè íà ýêðàí òàáëèöó îáùåãî ðåéòèíãà\n");
        printf("Íàæìèòå 4 ÷òîáû âûâåñòè íà ýêðàí ó÷àñòíèêîâ ïî ïðîöåíòèëþ\n");
        printf("Íàæìèòå 5 ÷òîáû âûâåñòè ðåçóëüòàòû â ôàéë\n");
        printf("Íàæìèòå 6 ÷òîáû âûéòè èç ïðîãðàììû\n");
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("+-------------------------------------------------------------+\n");
            printf("|                  ÈÍÔÎÐÌÀÖÈß Î ÏÐÎÃÐÀÌÌÅ                     |\n");
            printf("|-------------------------------------------------------------|\n");
            printf("|     ÐÀÇÐÀÁÎÒ×ÈÊ: ÑÒÓÄÅÍÒ ÃÐÓÏÏÛ ÁÎÈÑ-242 ÁÎÃÄÀÍÎÂ ÈËÜß      |\n");
            printf("|     ÔÓÍÊÖÈÎÍÀË: ÏÎÌÎÙÜ Â ÑÎÑÒÀÂËÅÍÈÈ ÎÒ×¨ÒÎÂ Î ÒÓÐÍÈÐÀÕ     |\n");
            printf("|      ÏÎ ËÛÆÍÛÌ ÃÎÍÊÀÌ, ÂÛ×ÈÑËÅÍÈÅ ËÓ×ØÈÕ ÑÏÎÐÒÑÌÅÍÎÂ        |\n");
            printf("|                                                             |\n");
            printf("|  ÂÅÐÑÈß:                                      VERSION 0.1   |\n");
            printf("+-------------------------------------------------------------+\n");
            printf("\n");
            break;
        case 1:
            printf("Ââåäèòå 1, ÷òîáû çàïîëíèòü äàííûå âðó÷íóþ èëè 2, ÷òîáû çàïîëíèòü ðàíäîìíî:\n");
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
