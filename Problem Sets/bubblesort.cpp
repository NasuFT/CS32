#include <iostream>
#include <ctime>

struct ArrayInt {
    int* array;
    int size;

    ~ArrayInt();

    void generateRandomNumbers(int N);
    void bubbleSort();
    void insertionSort();
    void selectionSort();
    void show();
};

ArrayInt::~ArrayInt() {
    delete array;
}

void ArrayInt::generateRandomNumbers(int N) {
    size = N;
    int *arr = new int[N];
    for(int i = 0; i < N; i++) {
        arr[i] = rand();
    }
}

void ArrayInt::bubbleSort() {
    for(int i = size; i > 1; i--) {
        for(int j = 1; j < i; j++) {
            if(array[j - 1] > array[j]) {
                int tmp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = tmp;
            }
        }
    }
}

void ArrayInt::insertionSort() {
    
}

void ArrayInt::selectionSort() {
    
}

void ArrayInt::show() {
    std::cout << "[";
    for(int i = 0; i < size; i++) {
        std::cout << array[i];
        if(i != size - 1) std::cout << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    int N = 0;
    ArrayInt array;
    array.generateRandomNumbers(N);
    array.show();
    array.bubbleSort();
    array.show();
}