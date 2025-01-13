#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

int** input_results(int num, int** arr) {
    for (int i = 0; i < num; i++) {
        printf("Ââåäèòå íîìåğ ó÷àñòíèêà: ");
        scanf_s("%d", &arr[i][0]);
        for (int j = 1; j < 4; j++) {
            printf("Ââåäèòå ğåçóëüòàò ó÷àñòíèêà #%d (ïîïûòêà %d): ", i + 1, j);
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
    printf("\nĞåçóëüòàòû ó÷àñòíèêîâ:\n");
    printf("+-------------------+-------------------+-------------------+-------------------+\n");
    printf("| Íîìåğ ó÷àñòíèêà   | Ïåğâûé çàáåã      | Âòîğîé çàáåã      | Òğåòèé çàáåã      |\n");
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
    printf("Ââåäèòå ïğîöåíòèëü (îò 0 äî 100): ");
    scanf_s("%d", &percentile);


    int index = ceil((percentile / 100.0) * number_of_participant) - 1;
    if (index < 0) index = 0;
    if (index >= number_of_participant) index = number_of_participant - 1;
    return index;
}

void print_table(int** sums, int number_of_participant) {
    printf("\nĞåçóëüòàòû ó÷àñòíèêîâ:\n");
    printf("+-------------------+-------------------+\n");
    printf("|  Íîìåğ ó÷àñòíèêà  |    Îáùåå âğåìÿ    |\n");
    printf("+-------------------+-------------------+\n");
    for (int i = 0; i < number_of_participant; i++) {
        printf("| %-17d | %-17d |\n", sums[i][0], sums[i][1]);
    }
    printf("+-------------------+-------------------+\n");
}

void print_to_file(int** sums, int index) {
    FILE* file = fopen("C:\\Users\\Admin\\Desktop\\results.txt", "w");
    fprintf(file, "\nĞåçóëüòàòû ó÷àñòíèêîâ (ïî óáûâàíèş):\n");
    fprintf(file, "+-------------------+-------------------+\n");
    fprintf(file, "| Íîìåğ ó÷àñòíèêà   | Ñóììà áàëëîâ      |\n");
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
    printf("                                |                      ÊÓĞÑÎÂÎÉ ÏĞÎÅÊÒ                        |\n");
    printf("                                |-------------------------------------------------------------|\n");
    printf("                                |  ÒÅÌÀ: ÄÂÓÌÅĞÍÛÅ ÌÀÑÑÈÂÛ, ÏÎÑÒĞÎÅÍÈÅ ÏĞÎÃĞÀÌÌÛ ÂÛ×ÈÑËÅÍÈß   |\n");
    printf("                                |  (È ÀÍÀËÈÇÀ) ĞÅÇÓËÜÒÀÒÎÂ ÑÎĞÅÂÍÎÂÀÍÈÉ ÏÎ ÂÈÄÀÌ ÑÏÎĞÒÀ       |\n");
    printf("                                |                      (ËÛÆÍÛÅ ÃÎÍÊÈ)                         |\n");
    printf("                                |                                                             |\n");
    printf("                                |  ÂÛÏÎËÍÈË:                                   ÁÎÃÄÀÍÎÂ È.Ï   |\n");
    printf("                                |  ÃĞÓÏÏÀ:                                         ÁÎÈÑ-242   |\n");
    printf("                                +-------------------------------------------------------------+\n");

    int number_of_participant;
    printf("Ïğèâåòñòâóş âàñ â ïğîãğàììå äëÿ ğàñ÷¸òà ğåçóëüòàòîâ òóğíèğà ïî ëûæíûì ãîíêàì, ââåäèòå êîë-âî ñïîğòñìåíîâ:\n");
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
        printf("Íàæìèòå 0 ÷òîáû âûâåñòè èíôîğìàöèş î ïğîãğàììå\n");
        printf("Íàæìèòå 1 ÷òîáû óêàçàòü äàííûå î ñïîğòñìåíàõ\n");
        printf("Íàæìèòå 2 ÷òîáû âûâåñòè íà ıêğàí òàáëèöó ñ ğåçóëüòàòàìè\n");
        printf("Íàæìèòå 3 ÷òîáû âûâåñòè íà ıêğàí òàáëèöó îáùåãî ğåéòèíãà\n");
        printf("Íàæìèòå 4 ÷òîáû âûâåñòè íà ıêğàí ó÷àñòíèêîâ ïî ïğîöåíòèëş\n");
        printf("Íàæìèòå 5 ÷òîáû âûâåñòè ğåçóëüòàòû â ôàéë\n");
        printf("Íàæìèòå 6 ÷òîáû âûéòè èç ïğîãğàììû\n");
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("+-------------------------------------------------------------+\n");
            printf("|                  ÈÍÔÎĞÌÀÖÈß Î ÏĞÎÃĞÀÌÌÅ                     |\n");
            printf("|-------------------------------------------------------------|\n");
            printf("|     ĞÀÇĞÀÁÎÒ×ÈÊ: ÑÒÓÄÅÍÒ ÃĞÓÏÏÛ ÁÎÈÑ-242 ÁÎÃÄÀÍÎÂ ÈËÜß      |\n");
            printf("|     ÔÓÍÊÖÈÎÍÀË: ÏÎÌÎÙÜ Â ÑÎÑÒÀÂËÅÍÈÈ ÎÒ×¨ÒÎÂ Î ÒÓĞÍÈĞÀÕ     |\n");
            printf("|      ÏÎ ËÛÆÍÛÌ ÃÎÍÊÀÌ, ÂÛ×ÈÑËÅÍÈÅ ËÓ×ØÈÕ ÑÏÎĞÒÑÌÅÍÎÂ        |\n");
            printf("|                                                             |\n");
            printf("|  ÂÅĞÑÈß:                                      VERSION 0.1   |\n");
            printf("+-------------------------------------------------------------+\n");
            printf("\n");
            break;
        case 1:
            printf("Ââåäèòå 1, ÷òîáû çàïîëíèòü äàííûå âğó÷íóş èëè 2, ÷òîáû çàïîëíèòü ğàíäîìíî:\n");
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