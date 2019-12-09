#include <stdio.h>
#include <stdlib.h>

void dual_quicksort(int arr[], int p, int r);

void print_arr(int arr[], int p, int r) {
    for(int i = p; i <= r; ++i) printf(i == r ? "%d" : "%d ", arr[i]);
    printf("\n");
}

void insertion_sort(int A[], int from, int to) {
    for(int i = from; i < to; i++) {
        for(int j = i + 1; j > from && A[j] < A[j - 1]; j--) {
            int temp = A[j - 1];
            A[j - 1] = A[j];
            A[j] = temp;
        }
    }
}

void dual_quicksort(int arr[], int p, int r) {
    if(r - p + 1 <= 17) {
        if(r - p + 1 >= 1) {
            insertion_sort(arr, p, r);
            printf("Insertion sort: ");
            print_arr(arr, p, r);
        }
        return;
    }

    int tmp;

    if(arr[p] > arr[r]) {
        tmp = arr[r];
        arr[r] = arr[p];
        arr[p] = tmp;
    }

    int lpivot = arr[p];
    int rpivot = arr[r];
    int a = p;

    for(int i = a + 1; i < r; ++i) {
        if(arr[i] < lpivot) {
            tmp = arr[a + 1];
            arr[++a] = arr[i];
            arr[i] = tmp;
        }
    }

    printf("After moving elements less than left pivot:\n");
    print_arr(arr, p, r);
    
    int b = a;
    for(int i = b + 1; i < r; ++i) {
        if(arr[i] >= lpivot && arr[i] <= rpivot) {
            tmp = arr[b + 1];
            arr[++b] = arr[i];
            arr[i] = tmp;
        }
    }

    printf("After moving elements that lie between left pivot and right pivot:\n");
    print_arr(arr, p, r);

    tmp = arr[a];
    arr[a] = arr[p];
    arr[p] = tmp;
    tmp = arr[b + 1];
    arr[b + 1] = arr[r];
    arr[r] = tmp;

    printf("After final pivot swap:\n");
    print_arr(arr, p, r);

    dual_quicksort(arr, p, a - 1);
    dual_quicksort(arr, a + 1, b);
    dual_quicksort(arr, b + 2, r);
}

int main() {
    int t;
    scanf("%d", &t);

    for(int i = 0; i < t; ++i) {
        int n;
        scanf("%d", &n);

        int* arr = malloc(sizeof(int) * n);
        for(int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        dual_quicksort(arr, 0, n - 1);
        print_arr(arr, 0, n - 1);

        free(arr);
    }
}