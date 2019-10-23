#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int reallocations = 0;

int is_stack_full(int* base, int* top, int stack_number) {
    if(top[stack_number] == base[stack_number + 1]) return 1;
    else return 0;
}

int get_free_cells(int* base, int* top) {
    int free_cells = 0;
    for(int i = 0; i < 10; i++) {
        free_cells += base[i + 1] - top[i];
    }
    return free_cells;
}

void shift_cells(int* array, int* base, int* top, int* new_base, int* new_top, int stack_number) {
    int new_array[1000];
    for(int i = 0; i < 10; i++) {
        new_top[i] = new_base[i] + (top[i] - base[i]);
        for(int j = 0; j <= top[i] - base[i]; j++) {
            new_array[new_base[i] + j + 1] = array[base[i] + j + 1];
        }
    }
    for(int i = 0; i < 1000; i++) {
        array[i] = new_array[i];
    }
    for(int i = 0; i < 10; i++) {
        base[i] = new_base[i];
        top[i] = new_top[i];
    }
    base[10] = new_base[10];
}
	
void reallocate(int* array, int* base, int* top, int stack_number, int reallocation_ratio) {
    float equal_partition_total_percentage = reallocation_ratio * 0.01;
    float unequal_partition_total_percentage = 1.0f - equal_partition_total_percentage;
    static int oldT[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int usedSpace[10];
    for(int i = 0; i < 10; i++) {
        usedSpace[i] = top[i] - base[i];
    }
    int increment[10], total_increment = 0;
    for(int i = 0; i < 10; i++) {
        increment[i] = usedSpace[i] - oldT[i];
        if(increment[i] < 0) increment[i] = 0;
        total_increment += increment[i];
    }
    increment[stack_number]++;
    total_increment++;

    int free_cells = get_free_cells(base, top) - 1;
    float equal_partition_per_stack = (free_cells * equal_partition_total_percentage) / 10.0f;
    float cells_per_increment = (free_cells * unequal_partition_total_percentage) / (float) total_increment;

    float theoretical_added_cells[10];
    for(int i = 0; i < 10; i++) {
        theoretical_added_cells[i] = equal_partition_per_stack + (cells_per_increment * increment[i]);
    }

    float theoretical_added_cells_incremental[10];
    theoretical_added_cells_incremental[0] = theoretical_added_cells[0];
    for(int i = 1; i < 10; i++) {
        theoretical_added_cells_incremental[i] = theoretical_added_cells_incremental[i - 1] + theoretical_added_cells[i];
    }

    int actual_cells_added[10];
    actual_cells_added[0] = floor(theoretical_added_cells_incremental[0]);
    for(int i = 1; i < 10; i++) {
        actual_cells_added[i] = floor(theoretical_added_cells_incremental[i]) - floor(theoretical_added_cells_incremental[i - 1]);
    }

    int new_base[11];
    new_base[0] = -1;
    for(int i = 1; i < 10; i++) {
        new_base[i] = new_base[i - 1] + usedSpace[i - 1] + actual_cells_added[i - 1];
        if(i - 1 == stack_number) new_base[i]++;
    }
    new_base[10] = base[10];

    int new_top[10];
    shift_cells(array, base, top, new_base, new_top, stack_number);

    for(int i = 0; i < 10; i++) {
        oldT[i] = top[i] - base[i];
    }
}

void push_to_stack(int* array, int* base, int* top, int reallocation_ratio, int stack_number, int element) {
    if(is_stack_full(base, top, stack_number) != 0) { 
        reallocate(array, base, top, stack_number, reallocation_ratio);
        reallocations++;
    }

    array[++top[stack_number]] = element;
}

int main() {
    int array[1000];
    int base[11] = {-1, 99, 199, 299, 399, 499, 599, 699, 799, 899, 999};
    int top[10] = {-1, 99, 199, 299, 399, 499, 599, 699, 799, 899};
    int equal_partition_percentages[8] = {10, 5, 20, 30, 40, 50, 60, 70};

    srand(19802);
    //for(int j = 0; j < 8; j++) {
        //for(int k = 0; k < 50; k++) {
            for(int i = 0; i < 1000; i++) {
	            push_to_stack(array, base, top, equal_partition_percentages[j], rand() % 10, rand());
            }
        //}

    //    printf("Ratio [%d - %d]: Avg. Allocations: %.2f", 100 - equal_partition_percentages[j], equal_partition_percentages[j], (float) reallocations / 50.0f);

    //    reallocations = 0;
    //}

    printf("Reallocations: %d", reallocations);
}
