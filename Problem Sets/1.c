#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int sizeInputs[] = {10, 20, 50, 100, 200, 1000, 5000, 10000};
    int sizeInputsArrSize = sizeof(sizeInputs)/sizeof(sizeInputs[0]);

    // Randomizer Setup
    srand(time(NULL));
    rand();

    // Time Comparisons
    float *averageTimeBubble = (float*) malloc(sizeInputsArrSize * sizeof(float));
    float *averageTimeInsertion = (float*) malloc(sizeInputsArrSize * sizeof(float));
    float *averageTimeSelection = (float*) malloc(sizeInputsArrSize * sizeof(float));

    for(int i = 0; i < sizeInputsArrSize; i++) {
        int N = sizeInputs[i];
        int *arr = malloc(N * sizeof(int));
        
        //Bubble Sort
        float timeBubbleSort = 0.0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            int start = time(NULL);
            for(int i = N - 1; i > 0; i--) {
                for(int j = 0; j < i; j++) {
                    if(arr[j] > arr[j + 1]) {
                        int tmp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = tmp;
                    }
                }
            }
            int end = time(NULL);
            int duration = end - start;
            timeBubbleSort += duration;
        }
        averageTimeBubble[i] = timeBubbleSort / 30.0;

        //Insertion Sort
        float timeInsertionSort = 0.0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            int start = time(NULL);
            for(int i = 1; i < N; i++) {
                int tmp = arr[i], j = i - 1;
                while(j >= 0 && arr[j] > tmp) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = tmp;
            }
            int end = time(NULL);
            int duration = end - start;
            timeInsertionSort += duration;
        }
        averageTimeInsertion[i] = timeInsertionSort / 30.0;

        //Selection Sort
        float timeSelectionSort = 0.0;
        for(int i = 0; i < 30; i++) {
            //Randomizer
            for(int i = 0; i < N; i++) {
                arr[i] = rand();
            }

            int start = time(NULL);
            for(int i = 0; i < N; i++) {
                int smallestIndex = i;
                for(int j = i + 1; j < N; j++) {
                    if(arr[j] < arr[smallestIndex]) smallestIndex = j;
                }

                int tmp = arr[i];
                arr[i] = arr[smallestIndex];
                arr[smallestIndex] = tmp;
            }
            int end = time(NULL);
            int duration = end - start;
            timeSelectionSort += duration;
        }
        averageTimeSelection[i] = timeSelectionSort / 30.0;
    }

    for(int i = 0; i < sizeInputsArrSize; i++) {
        printf("Time Taken (%d) (Bubble Sort): %f s\n", sizeInputs[i], averageTimeBubble[i]);
        printf("Time Taken (%d) (Insertion Sort): %f s\n", sizeInputs[i], averageTimeInsertion[i]);
        printf("Time Taken (%d) (Selection Sort): %f s\n", sizeInputs[i], averageTimeSelection[i]);
    }
}