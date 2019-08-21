#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int sizeInputs[] = {10, 20, 50, 100, 200, 1000, 5000, 10000};
    int sizeInputsArrSize = sizeof(sizeInputs)/sizeof(sizeInputs[0]);

    // Randomizer Setup
    srand(time(NULL));
    rand();

    printf("Starting Time Tests...");

    // Time Tests
    double *averageTimeBubble = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageTimeInsertion = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageTimeSelection = (double*) malloc(sizeInputsArrSize * sizeof(double));

    for(int i = 0; i < sizeInputsArrSize; i++) {
        int N = sizeInputs[i];
        int *arr = malloc(N * sizeof(int));
        
        //Bubble Sort
        double timeBubbleSort = 0.0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            clock_t start = clock();
            for(int i = N - 1; i > 0; i--) {
                for(int j = 0; j < i; j++) {
                    if(arr[j] > arr[j + 1]) {
                        int tmp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = tmp;
                    }
                }
            }
            clock_t end = clock();
            double duration = (double) (end - start) / CLOCKS_PER_SEC;
            timeBubbleSort += duration;
        }
        averageTimeBubble[i] = timeBubbleSort / 30.0;

        //Insertion Sort
        double timeInsertionSort = 0.0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            clock_t start = clock();
            for(int i = 1; i < N; i++) {
                int tmp = arr[i], j = i - 1;
                while(j >= 0 && arr[j] > tmp) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = tmp;
            }
            clock_t end = clock();
            double duration = (double) (end - start) / CLOCKS_PER_SEC;
            timeInsertionSort += duration;
        }
        averageTimeInsertion[i] = timeInsertionSort / 30.0;

        //Selection Sort
        double timeSelectionSort = 0.0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            clock_t start = clock();
            for(int i = 0; i < N; i++) {
                int smallestIndex = i;
                for(int j = i + 1; j < N; j++) {
                    if(arr[j] < arr[smallestIndex]) smallestIndex = j;
                }

                int tmp = arr[i];
                arr[i] = arr[smallestIndex];
                arr[smallestIndex] = tmp;
            }
            clock_t end = clock();
            double duration = (double) (end - start) / CLOCKS_PER_SEC;
            timeSelectionSort += duration;
        }
        averageTimeSelection[i] = timeSelectionSort / 30.0;
        free(arr);
    }

    printf("Completed\n");
    printf("Starting Comparison Tests...");

    // Comparison Tests
    double *averageComparisonsBubble = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageComparisonsInsertion = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageComparisonsSelection = (double*) malloc(sizeInputsArrSize * sizeof(double));

    for(int i = 0; i < sizeInputsArrSize; i++) {
        int N = sizeInputs[i];
        int *arr = malloc(N * sizeof(int));
        
        //Bubble Sort
        int comparisonsBubbleSort = 0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            int comparisons = 0;
            for(int i = N - 1; i > 0; i--) {
                for(int j = 0; j < i; j++) {
                    comparisons++;
                    if(arr[j] > arr[j + 1]) {
                        int tmp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = tmp;
                    }
                }
            }
            comparisonsBubbleSort += comparisons;
        }
        averageComparisonsBubble[i] = (double) comparisonsBubbleSort / 30.0;

        //Insertion Sort
        int comparisonsInsertionSort = 0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            int comparisons = 0;
            for(int i = 1; i < N; i++) {
                int tmp = arr[i], j = i - 1;
                comparisons++;
                while(j >= 0) {
                    comparisons++;
                    if(arr[j] > tmp) {
                        arr[j + 1] = arr[j];
                    } else {
                        break;
                    }
                    comparisons++;
                    j--;
                }
                arr[j + 1] = tmp;
            }
            comparisonsInsertionSort += comparisons;
        }
        averageComparisonsInsertion[i] = (double) comparisonsInsertionSort / 30.0;

        //Selection Sort
        int comparisonsSelectionSort = 0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            int comparisons = 0;
            for(int i = 0; i < N; i++) {
                int smallestIndex = i;
                for(int j = i + 1; j < N; j++) {
                    comparisons++;
                    if(arr[j] < arr[smallestIndex]) {
                        smallestIndex = j;
                    }
                }

                int tmp = arr[i];
                arr[i] = arr[smallestIndex];
                arr[smallestIndex] = tmp;
            }
            comparisonsSelectionSort += comparisons;
        }
        averageComparisonsSelection[i] = (double) comparisonsSelectionSort / 30.0;
        free(arr);
    }

    printf("Completed\n");
    printf("Starting Swap Tests...");

    // Swap Tests
    double *averageSwapsBubble = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageSwapsInsertion = (double*) malloc(sizeInputsArrSize * sizeof(double));
    double *averageSwapsSelection = (double*) malloc(sizeInputsArrSize * sizeof(double));

    for(int i = 0; i < sizeInputsArrSize; i++) {
        int N = sizeInputs[i];
        int *arr = malloc(N * sizeof(int));
        
        //Bubble Sort
        int swapsBubbleSort = 0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            int swaps = 0;
            for(int i = N - 1; i > 0; i--) {
                for(int j = 0; j < i; j++) {
                    if(arr[j] > arr[j + 1]) {
                        swaps += 2;
                        int tmp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = tmp;
                    }
                }
            }
            swapsBubbleSort += swaps;
        }
        averageSwapsBubble[i] = (double) swapsBubbleSort / 30.0;

        //Insertion Sort
        int swapsInsertionSort = 0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            int swaps = 0;
            for(int i = 1; i < N; i++) {
                int tmp = arr[i], j = i - 1;
                while(j >= 0 && arr[j] > tmp) {
                    swaps++;
                    arr[j + 1] = arr[j];
                    j--;
                }
                swaps++;
                arr[j + 1] = tmp;
            }
            swapsInsertionSort += swaps;
        }
        averageSwapsInsertion[i] = (double) swapsInsertionSort / 30.0;

        //Selection Sort
        int swapsSelectionSort = 0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            int swaps = 0;
            for(int i = 0; i < N; i++) {
                int smallestIndex = i;
                for(int j = i + 1; j < N; j++) {
                    if(arr[j] < arr[smallestIndex]) {
                        smallestIndex = j;
                    }
                }

                if(smallestIndex != i) swaps += 2;
                int tmp = arr[i];
                arr[i] = arr[smallestIndex];
                arr[smallestIndex] = tmp;
            }
            swapsSelectionSort += swaps;
        }
        averageSwapsSelection[i] = (double) swapsSelectionSort / 30.0;
        free(arr);
    }
    printf("Completed\n");

    //Output
    for(int i = 0; i < sizeInputsArrSize; i++) {
        printf("Time Taken (N = %d) (Bubble Sort): %f s\n", sizeInputs[i], averageTimeBubble[i]);
        printf("Time Taken (N = %d) (Insertion Sort): %f s\n", sizeInputs[i], averageTimeInsertion[i]);
        printf("Time Taken (N = %d) (Selection Sort): %f s\n", sizeInputs[i], averageTimeSelection[i]);
        printf("Comparisons Taken (N = %d) (Bubble Sort): %.2f\n", sizeInputs[i], averageComparisonsBubble[i]);
        printf("Comparisons Taken (N = %d) (Insertion Sort): %.2f\n", sizeInputs[i], averageComparisonsInsertion[i]);
        printf("Comparisons Taken (N = %d) (Selection Sort): %.2f\n", sizeInputs[i], averageComparisonsSelection[i]);
        printf("Swaps Taken (N = %d) (Bubble Sort): %.2f\n", sizeInputs[i], averageSwapsBubble[i]);
        printf("Swaps Taken (N = %d) (Insertion Sort): %.2f\n", sizeInputs[i], averageSwapsInsertion[i]);
        printf("Swaps Taken (N = %d) (Selection Sort): %.2f\n", sizeInputs[i], averageSwapsSelection[i]);
    }

    //Save all averages into CSV???
    FILE *fp = fopen("hopesanddreams.csv", "w+");
    fprintf(fp, "Table, Time, Comparisons, Swaps");
    for(int i = 0; i < sizeInputsArrSize; i++) {
        fprintf(fp, "\nN = %d", sizeInputs[i]);
        fprintf(fp, "\nBubble Sort, %f, %.2f, %.2f", averageTimeBubble[i], averageComparisonsBubble[i], averageSwapsBubble[i]);
        fprintf(fp, "\nInsertion Sort, %f, %.2f, %.2f", averageTimeInsertion[i], averageComparisonsInsertion[i], averageSwapsInsertion[i]);
        fprintf(fp, "\nSelection Sort, %f, %.2f, %.2f", averageTimeSelection[i], averageComparisonsSelection[i], averageSwapsSelection[i]);
    }
    fclose(fp);

    free(averageTimeBubble);
    free(averageTimeInsertion);
    free(averageTimeSelection);
    free(averageComparisonsBubble);
    free(averageComparisonsInsertion);
    free(averageComparisonsSelection);
    free(averageSwapsBubble);
    free(averageTimeInsertion);
    free(averageTimeSelection);

    return 0;
}