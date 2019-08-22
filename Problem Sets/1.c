#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAMPLE_SIZE 30

int main() {
    int sizeInputs[] = {10, 20, 50, 100, 200, 1000, 5000, 10000};
    int sizeInputsArrSize = sizeof(sizeInputs)/sizeof(sizeInputs[0]);
    FILE *fp;

    // Randomizer Setup
    srand(time(NULL));
    rand();

    printf("Starting Time Tests...");

    // Time Tests
    double *averageTimeBubble = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageTimeInsertion = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageTimeSelection = (double*) malloc(sizeInputsArrSize * sizeof(double));
    fp = fopen("1time.csv", "w+");

    for(int i = 0; i < sizeInputsArrSize; i++) {
        int N = sizeInputs[i];
        int *arrBubble = malloc(N * sizeof(int));
        int *arrInsertion = malloc(N * sizeof(int));
        int *arrSelection = malloc(N * sizeof(int));
        double totalTimeBubble = 0.0;
        double totalTimeInsertion = 0.0;
        double totalTimeSelection = 0.0;

        fprintf(fp, "N = %d\n", N);
        fprintf(fp, "Test Case, Bubble Sort, Insertion Sort, Selection Sort\n");

        for(int i = 0; i < SAMPLE_SIZE; i++) {
            for(int i = 0; i < N; i++) {
                int x = rand();
                arrBubble[i] = x;
                arrInsertion[i] = x;
                arrSelection[i] = x;
            }

            //Bubble Sort
            clock_t startBubble = clock();
            for(int i = N - 1; i > 0; i--) {
                for(int j = 0; j < i; j++) {
                    if(arrBubble[j] > arrBubble[j + 1]) {
                        int tmp = arrBubble[j];
                        arrBubble[j] = arrBubble[j + 1];
                        arrBubble[j + 1] = tmp;
                    }
                }
            }
            clock_t endBubble = clock();
            double durationBubble = (double) (endBubble - startBubble) / CLOCKS_PER_SEC;
            totalTimeBubble += durationBubble;

            //Insertion Sort
            clock_t startInsertion = clock();
            for(int i = 1; i < N; i++) {
                int tmp = arrInsertion[i], j = i - 1;
                while(j >= 0 && arrInsertion[j] > tmp) {
                    arrInsertion[j + 1] = arrInsertion[j];
                    j--;
                }
                arrInsertion[j + 1] = tmp;
            }
            clock_t endInsertion = clock();
            double durationInsertion = (double) (endInsertion - startInsertion) / CLOCKS_PER_SEC;
            totalTimeInsertion += durationInsertion;

            //Selection Sort
            clock_t startSelection = clock();
            for(int i = 0; i < N; i++) {
                int smallestIndex = i;
                for(int j = i + 1; j < N; j++) {
                    if(arrSelection[j] < arrSelection[smallestIndex]) smallestIndex = j;
                }

                int tmp = arrSelection[i];
                arrSelection[i] = arrSelection[smallestIndex];
                arrSelection[smallestIndex] = tmp;
            }
            clock_t endSelection = clock();
            double durationSelection = (double) (endSelection - startSelection) / CLOCKS_PER_SEC;
            totalTimeSelection += durationSelection;

            fprintf(fp, "%d, %f, %f, %f\n", i + 1, durationBubble, durationInsertion, durationSelection);
        }

        averageTimeBubble[i] = totalTimeBubble / 30.0;
        averageTimeInsertion[i] = totalTimeInsertion / 30.0;
        averageTimeSelection[i] = totalTimeSelection / 30.0;

        fprintf(fp, "Average, %f, %f, %f\n", averageTimeBubble[i], averageTimeInsertion[i], averageTimeSelection[i]);

        free(arrBubble);
        free(arrInsertion);
        free(arrSelection);
    }

    fprintf(fp, "Summary\n");
    fprintf(fp, "N, Bubble Sort, Insertion Sort, Selection Sort\n");
    for(int i = 0; i < sizeInputsArrSize; i++) {
        fprintf(fp, "%d, %f, %f, %f\n", sizeInputs[i], averageTimeBubble[i], averageTimeInsertion[i], averageTimeSelection[i]);
    }

    fclose(fp);

    printf("Completed\n");
    printf("Starting Comparison Tests...");

    // Comparison Tests
    double *averageComparisonsBubble = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageComparisonsInsertion = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageComparisonsSelection = (double*) malloc(sizeInputsArrSize * sizeof(double));
    fp = fopen("1comparison.csv", "w+");

    for(int i = 0; i < sizeInputsArrSize; i++) {
        int N = sizeInputs[i];
        int *arrBubble = malloc(N * sizeof(int));
        int *arrInsertion = malloc(N * sizeof(int));
        int *arrSelection = malloc(N * sizeof(int));
        int totalComparisonsBubble = 0;
        int totalComparisonsInsertion = 0;
        int totalComparisonsSelection = 0;

        fprintf(fp, "N = %d\n", N);
        fprintf(fp, "Test Case, Bubble Sort, Insertion Sort, Selection Sort\n");

        for(int i = 0; i < SAMPLE_SIZE; i++) {
            for(int i = 0; i < N; i++) {
                int x = rand();
                arrBubble[i] = x;
                arrInsertion[i] = x;
                arrSelection[i] = x;
            }

            //Bubble Sort
            int comparisonsBubble = 0;
            for(int i = N - 1; i > 0; i--) {
                for(int j = 0; j < i; j++) {
                    comparisonsBubble++;
                    if(arrBubble[j] > arrBubble[j + 1]) {
                        int tmp = arrBubble[j];
                        arrBubble[j] = arrBubble[j + 1];
                        arrBubble[j + 1] = tmp;
                    }
                }
            }
            totalComparisonsBubble += comparisonsBubble;

            //Insertion Sort
            int comparisonsInsertion = 0;
            for(int i = 1; i < N; i++) {
                int tmp = arrInsertion[i], j = i - 1;
                while(j >= 0) {
                    comparisonsInsertion++;
                    if(arrInsertion[j] > tmp) {
                        arrInsertion[j + 1] = arrInsertion[j];
                    } else {
                        break;
                    }
                    j--;
                }
                arrInsertion[j + 1] = tmp;
            }
            totalComparisonsInsertion += comparisonsInsertion;

            //Selection Sort
            int comparisonsSelection = 0;
            for(int i = 0; i < N; i++) {
                int smallestIndex = i;
                for(int j = i + 1; j < N; j++) {
                    comparisonsSelection++;
                    if(arrSelection[j] < arrSelection[smallestIndex]) smallestIndex = j;
                }

                int tmp = arrSelection[i];
                arrSelection[i] = arrSelection[smallestIndex];
                arrSelection[smallestIndex] = tmp;
            }
            totalComparisonsSelection += comparisonsSelection;

            fprintf(fp, "%d, %d, %d, %d\n", i + 1, comparisonsBubble, comparisonsInsertion, comparisonsSelection);
        }

        averageComparisonsBubble[i] = (double) totalComparisonsBubble / 30.0;
        averageComparisonsInsertion[i] = (double) totalComparisonsInsertion / 30.0;
        averageComparisonsSelection[i] = (double) totalComparisonsSelection / 30.0;

        fprintf(fp, "Average, %f, %f, %f\n", averageComparisonsBubble[i], averageComparisonsInsertion[i], averageComparisonsSelection[i]);

        free(arrBubble);
        free(arrInsertion);
        free(arrSelection);
    }

    fprintf(fp, "Summary\n");
    fprintf(fp, "N, Bubble Sort, Insertion Sort, Selection Sort\n");
    for(int i = 0; i < sizeInputsArrSize; i++) {
        fprintf(fp, "%d, %f, %f, %f\n", sizeInputs[i], averageComparisonsBubble[i], averageComparisonsInsertion[i], averageComparisonsSelection[i]);
    }

    fclose(fp);

    printf("Completed\n");
    printf("Starting Swap Tests...");

    // Swap Tests
    double *averageSwapsBubble = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageSwapsInsertion = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageSwapsSelection = (double*) malloc(sizeInputsArrSize * sizeof(double));
    fp = fopen("1swap.csv", "w+");

    for(int i = 0; i < sizeInputsArrSize; i++) {
        int N = sizeInputs[i];
        int *arrBubble = malloc(N * sizeof(int));
        int *arrInsertion = malloc(N * sizeof(int));
        int *arrSelection = malloc(N * sizeof(int));
        int totalSwapsBubble = 0;
        int totalSwapsInsertion = 0;
        int totalSwapsSelection = 0;

        fprintf(fp, "N = %d\n", N);
        fprintf(fp, "Test Case, Bubble Sort, Insertion Sort, Selection Sort\n");

        for(int i = 0; i < SAMPLE_SIZE; i++) {
            for(int i = 0; i < N; i++) {
                int x = rand();
                arrBubble[i] = x;
                arrInsertion[i] = x;
                arrSelection[i] = x;
            }

            //Bubble Sort
            int swapsBubble = 0;
            for(int i = N - 1; i > 0; i--) {
                for(int j = 0; j < i; j++) {
                    if(arrBubble[j] > arrBubble[j + 1]) {
                        swapsBubble++;
                        int tmp = arrBubble[j];
                        arrBubble[j] = arrBubble[j + 1];
                        arrBubble[j + 1] = tmp;
                    }
                }
            }
            totalSwapsBubble += swapsBubble;

            //Insertion Sort
            int swapsInsertion = 0;
            for(int i = 1; i < N; i++) {
                int tmp = arrInsertion[i], j = i - 1;
                while(j >= 0 && arrInsertion[j] > tmp) {
                    swapsInsertion++;
                    arrSelection[j + 1] = arrSelection[j];
                    j--;
                }
                arrInsertion[j + 1] = tmp;
            }
            totalSwapsInsertion += swapsInsertion;

            //Selection Sort
            int swapsSelection = 0;
            for(int i = 0; i < N; i++) {
                int smallestIndex = i;
                for(int j = i + 1; j < N; j++) {
                    if(arrSelection[j] < arrSelection[smallestIndex]) smallestIndex = j;
                }

                swapsSelection++;
                int tmp = arrSelection[i];
                arrSelection[i] = arrSelection[smallestIndex];
                arrSelection[smallestIndex] = tmp;
            }
            totalSwapsSelection += swapsSelection;

            fprintf(fp, "%d, %d, %d, %d\n", i + 1, swapsBubble, swapsInsertion, swapsSelection);
        }
        averageSwapsBubble[i] = (double) totalSwapsBubble / 30.0;
        averageSwapsInsertion[i] = (double) totalSwapsInsertion / 30.0;
        averageSwapsSelection[i] = (double) totalSwapsSelection / 30.0;

        fprintf(fp, "Average, %f, %f, %f\n", (double) totalSwapsBubble / 30.0, (double) totalSwapsInsertion / 30.0, (double) totalSwapsSelection / 30.0);

        free(arrBubble);
        free(arrInsertion);
        free(arrSelection);
    }

    fprintf(fp, "Summary\n");
    fprintf(fp, "N, Bubble Sort, Insertion Sort, Selection Sort\n");
    for(int i = 0; i < sizeInputsArrSize; i++) {
        fprintf(fp, "%d, %f, %f, %f\n", sizeInputs[i], averageSwapsBubble[i], averageSwapsInsertion[i], averageSwapsSelection[i]);
    }

    fclose(fp);
    printf("Completed\n");

    free(averageTimeBubble);
    free(averageTimeInsertion);
    free(averageTimeSelection);
    free(averageComparisonsBubble);
    free(averageComparisonsInsertion);
    free(averageComparisonsSelection);
    free(averageSwapsBubble);
    free(averageSwapsInsertion);
    free(averageSwapsSelection);
    return 0;
}