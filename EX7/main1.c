#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩:");
    scanf("%d", &n);

    // 確保輸入在 1~5 之間
    if (n < 1) n = 1;
    if (n > 5) n = 5;

    FILE *fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        printf("無法開啟檔案!\n");
        return 1;
    }

    time_t curtime;
    time(&curtime);
    char *time_str = ctime(&curtime);
    for (int i = 0; time_str[i] != '\0'; i++) {
        if (time_str[i] == '\n') {
            time_str[i] = '\0';
            break;
        }
    }

    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "= %s =\n", time_str);

    srand((unsigned)time(NULL));

    for (int i = 1; i <= 5; i++) {
        fprintf(fp, "[%d]: ", i);
        if (i <= n) {
            int lotto[7];
            int used[70] = {0}; 

            for (int j = 0; j < 7; j++) {
                int num;
                do {
                    num = rand() % 69 + 1;
                } while (used[num]);
                used[num] = 1;
                lotto[j] = num;
            }

            for (int a = 0; a < 5; a++) {
                for (int b = 0; b < 5 - a; b++) {
                    if (lotto[b] > lotto[b + 1]) {
                        int temp = lotto[b];
                        lotto[b] = lotto[b + 1];
                        lotto[b + 1] = temp;
                    }
                }
            }

            for (int j = 0; j < 7; j++) {
                fprintf(fp, "%02d ", lotto[j]);
            }
            fprintf(fp, "\n");
        } else {

            fprintf(fp, "-- -- -- -- -- -- -- \n");
        }
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

    printf("以為您購買的%d組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}

