#include <iostream>
#include <ctime>

struct ArrayInt {
    int* array = nullptr;
    unsigned int size;
    unsigned int lastSortDuration = 0;

    ~ArrayInt();

    void generateRandomNumbers(int N);
    void bubbleSort();
    void insertionSort();
    void selectionSort();
    void show();
    auto getLastSortTime();
};

ArrayInt::~ArrayInt() {
    delete array;
}

void ArrayInt::generateRandomNumbers(int N) {
    size = N;
    array = new int[N];

    srand(time(NULL));
    rand();
    
    for(int i = 0; i < N; i++) {
        array[i] = rand();
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
    for(int i = 1; i < size; i++) {
        int tmp = array[i], j = i - 1;
        while(j >= 0 && array[j] > tmp) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = tmp;
    }
}

void ArrayInt::selectionSort() {
    for(int i = 0; i < size; i++) {
        int smallestIndex = i;
        for(int j = i + 1; j < size; j++) {
            if(array[j] < array[smallestIndex]) smallestIndex = j;
        }

        int tmp = array[i];
        array[i] = array[smallestIndex];
        array[smallestIndex] = tmp;
    }
}

void ArrayInt::show() {
    std::cout << "[";
    for(int i = 0; i < size; i++) {
        std::cout << array[i];
        if(i != size - 1) std::cout << " ";
    }
    std::cout << "]" << std::endl;
}

auto ArrayInt::getLastSortTime() {
    return lastSortDuration;
}

int main() {
    int N = 10;
    ArrayInt array;
    array.generateRandomNumbers(N);
    array.show();
    {
        array.selectionSort();
    }
    
    array.show();
}