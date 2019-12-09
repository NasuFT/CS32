#include <stdio.h>
#include <stdlib.h>

int quick_select(int arr[], int p, int r, int rank);

void insertion_sort(int A[], int from, int to) {
    for(int i = from; i < to; i++) {
        for(int j = i + 1; j > from && A[j] < A[j - 1]; j--) {
            int temp = A[j - 1];
            A[j - 1] = A[j];
            A[j] = temp;
        }
    }
}

int median_of_medians(int arr[], int p, int r) {
    int N = r - p + 1;
    int median_sz = N % 5 == 0 ? N / 5 : N / 5 + 1;
    int* median_arr = malloc(sizeof(int) * median_sz);
    int j = 0;

    for(int i = p; i <= r; i += 5) {
        int q = i + 4 < r ? i + 4 : r;
        insertion_sort(arr, i, q);
        int median_ind = i + (q - i) / 2;
        median_arr[j++] = arr[median_ind];
    }

    int median = quick_select(median_arr, 0, median_sz - 1, median_sz % 2 == 0 ? median_sz / 2 : median_sz / 2 + 1);
    free(median_arr);
    return median;
}

int random_partition(int arr[], int p, int r) {
    int median = median_of_medians(arr, p, r);
    int median_ind = -1;

    for(int i = p; i <= r; ++i) {
        if(arr[i] == median) {
            median_ind = i;
            break;
        }
    }

    int tmp = arr[r];
    arr[r] = arr[median_ind];
    arr[median_ind] = tmp;

    int x = arr[r];
    int i = p - 1;
    for(int j = p; j < r; ++j) {
        if(arr[j] <= x) {
            tmp = arr[++i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    tmp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = tmp;

    return i + 1;
}

int quick_select(int arr[], int p, int r, int rank) {
    if(p == r) return arr[p];
    int q = random_partition(arr, p, r);
    int k = q - p + 1;
    if(rank == k) return arr[q];
    else if(k < rank) return quick_select(arr, q + 1, r, rank - k);
    else return quick_select(arr, p, q - 1, rank);
}

int main() {
    int t;
    scanf("%d", &t);

    for(int i = 0; i < t; ++i) {
        int N;
        scanf("%d", &N);
        int* arr = malloc(sizeof(int) * N);

        for(int i = 0; i < N; ++i) scanf("%d", &arr[i]);

        printf("Median : %d\n", quick_select(arr, 0, N - 1, N % 2 == 0 ? N / 2 : N / 2 + 1));
        free(arr);
    }
}