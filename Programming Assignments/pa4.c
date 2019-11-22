#include <stdio.h>

void shuffle(int arr[]) {
    int new_arr[1000];

    int p = 524287;
    int x = p % 1000;
    for(int i = 0; i < 1000; ++i) {
        new_arr[i] = arr[x];
        x = (x + p) % 1000;
    }
    for(int i = 0; i < 1000; ++i) {
        arr[i] = new_arr[i];
    }
}

int partition(int arr[], int p, int r) {
    int x = arr[r];
    int i = p - 1;
    for(int j = p; j < r; ++j) {
        if(arr[j] <= x) {
            ++i;
            int tmp = arr[j];
            arr[j] = arr[i];
            arr[i] = tmp;
        }
    }
    int tmp = arr[r];
    arr[r] = arr[i + 1];
    arr[i + 1] = tmp;
    return i + 1;
}

void quicksort(int arr[], int p, int r) {
    if(p < r) {
        int q = partition(arr, p, r);
        for(int i = p; i <= r; ++i) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        quicksort(arr, p, q - 1);
        quicksort(arr, q + 1, r);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    int arr[1000];

    for(int j = 0; j < t; ++j) {
        for(int i = 0; i < 1000; ++i) {
            scanf("%d", &arr[i]);
        }

        shuffle(arr);
        for(int i = 0; i < 1000; ++i) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        quicksort(arr, 0, 999);
        for(int i = 0; i < 1000; ++i) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}