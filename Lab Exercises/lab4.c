#include <stdio.h>
#include <stdlib.h>

typedef struct BigInt {
    int digit;
    struct BigInt* next;
    struct BigInt* prev;
} BigInt;

BigInt* add_digit(int x) {
    BigInt* digit = malloc(sizeof(BigInt));
    digit->digit = x;
    digit->next = NULL;
    digit->prev = NULL;
    return digit;
}

BigInt* get_tail(BigInt** num) {
    BigInt* tail_next = *num;
    BigInt* tail = NULL;
    while(tail_next != NULL) {
        tail = tail_next;
        tail_next = tail_next->next;
    }
    return tail;
}

void add_left(BigInt** num, int x) {
    BigInt* new_digit = add_digit(x);
    new_digit->next = *num;
    if(*num != NULL) (*num)->prev = new_digit;
    *num = new_digit;
}

void add_right(BigInt** num, int x) {
    BigInt* new_digit = add_digit(x);
    BigInt* tail = get_tail(num);
    new_digit->prev = tail;
    if(tail != NULL) tail->next = new_digit;
    else *num = new_digit;
}

BigInt* char_to_bigint(char *digits, int len) {
    BigInt* bigint = NULL;
    for(int i = 0; i < len; i++) {
        add_right(&bigint, digits[i] - 48);
    }
    return bigint;
}

void print_bigint(BigInt** num) {
    BigInt* next_digit = *num;
    BigInt* current_digit = NULL;
    while(next_digit != NULL) {
        current_digit = next_digit;
        next_digit = next_digit->next;
        printf("%d", current_digit->digit);
    }
    printf("\n");
}

void print_bigint_rev(BigInt** num) {
    BigInt* current_digit = get_tail(num);
    while(current_digit != NULL) {
        printf("%d", current_digit->digit);
        current_digit = current_digit->prev;
    }
    printf("\n");
}

BigInt* add(BigInt** a, BigInt** b) {
    BigInt* result_num = NULL;
    BigInt* current_a =  get_tail(a);
    BigInt* current_b = get_tail(b);

    int carry_over = 0;
    while(current_a != NULL || current_b != NULL) {
        int digit_a = current_a != NULL ? current_a->digit : 0;
        int digit_b = current_b != NULL ? current_b->digit : 0;
        int result = digit_a + digit_b + carry_over;
        int digit = result >= 10 ? result - 10 : result;
        carry_over = result >= 10 ? 1 : 0;

        add_left(&result_num, digit);
        
        if(current_a == *a || current_a == NULL) current_a = NULL;
        else current_a = current_a->prev;
        if(current_b == *b || current_b == NULL) current_b = NULL;
        else current_b = current_b->prev;
    }

    if(carry_over == 1) add_left(&result_num, 1);
    return result_num;
}

int main() {
    int len_a, len_b;

    scanf("%d", &len_a);
    scanf("%d", &len_b);

    char* array_a = malloc((len_a + 1) * sizeof(char));
    char* array_b = malloc((len_b + 1) * sizeof(char));

    scanf("%s", array_a);
    scanf("%s", array_b);

    BigInt* num_a = char_to_bigint(array_a, len_a);
    BigInt* num_b = char_to_bigint(array_b, len_b);

    print_bigint(&num_a);

    BigInt* result = add(&num_a, &num_b);

    print_bigint(&result);
    print_bigint_rev(&result);

    return 0;
}
