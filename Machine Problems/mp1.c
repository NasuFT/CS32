#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    int x;
    struct Node* llink;
    struct Node* rlink;
} Node;

int max_int(int a, int b) {
    return a < b ? b : a;
}

Node* create_node(int x) {
    Node* node = malloc(sizeof(Node));
    node->x = x;
    node->llink = NULL;
    node->rlink = NULL;

    return node;
}

void insert_left(Node** bigint, int x) {
    Node* head = *bigint; 
    Node* new_node = create_node(x);

    new_node->rlink = head;
    new_node->llink = head->llink;
    head->llink->rlink = new_node;
    head->llink = new_node;
    *bigint = new_node;
}

void insert_right(Node** bigint, int x) {
    insert_left(bigint, x);
    *bigint = (*bigint)->rlink;
}

Node* create_zero_bigint() {
    Node* new_node = create_node(0);
    new_node->llink = new_node;
    new_node->rlink = new_node;
    return new_node;
}

void insert_digit(Node** bigint, int x) {
    Node* head = *bigint;
    Node* new_node = create_node(abs(x));
    int sign_digit = x < 0 ? -1 : 1;
    
    new_node->rlink = head->rlink;
    new_node->llink = head;
    new_node->rlink->llink = new_node;
    head->rlink = new_node;

    head->x = sign_digit * (abs(head->x) + 1);
}

void insert_digit_right(Node** bigint, int x) {
    Node* head = *bigint;
    int sign_digit = head->x < 0 ? -1 : 1;

    insert_right(bigint, abs(x));

    head->x = sign_digit * (abs(head->x) + 1);
}

void remove_digit(Node** bigint) {
    Node* head = *bigint;
    Node* node = head->rlink;

    head->rlink = node->rlink;
    node->rlink->llink = head;

    head->x = head->x > 0 ? head->x - 1 : head->x + 1;

    free(node);
}

int get_digit(Node** bigint, int pos) {
    Node* head = *bigint;
    Node* current_node = head->llink;
    if(pos < abs(head->x)) {
        for(int i = 0; i < pos; i++) current_node = current_node->llink;
    }

    return current_node->x;
}

void change_digit(Node** bigint, int pos, int digit) {
    Node* head = *bigint;
    Node* current_node = head->llink;
    if(pos < abs(head->x)) {
        for(int i = 0; i < pos; i++) current_node = current_node->llink;

        current_node->x = digit;
    }
}

void remove_all_digits(Node** bigint) {
    Node* head = *bigint;

    while(head->x != 0) {
        remove_digit(bigint);
    }
}

void remove_leading_zeroes(Node** bigint) {
    Node* head = *bigint;
    Node* current_node = head->rlink;

    while(current_node != head && current_node->x == 0) {
        remove_digit(bigint);
        current_node = head->rlink;
    }
}

void negate_bigint(Node** bigint) {
    Node* head = *bigint;
    head->x = -1 * head->x;
}

void copy_bigint(Node** dest, Node** src) {
    Node* head_src = *src;
    Node* head_dest = *dest;

    int sign = head_src->x < 0 ? -1 : 1;

    remove_all_digits(dest);
    Node* current_node = head_src->rlink;
    while(current_node != head_src) {
        insert_digit_right(dest, current_node->x);
        current_node = current_node->rlink;
    }
    head_dest->x = sign * head_dest->x;
}

void print_bigint(Node** bigint) {
    Node* head = *bigint;

    if(head->x == 0) {
        printf("0\n");
        return;
    }

    if(head->x < 0) printf("-");

    Node* current_node = head->rlink;

    for(int i = 0; i < abs(head->x); i++) {
        if(i == 0) printf("%d", current_node->x);
        else {
            if(current_node->x == 0) printf("0000");
            else if(current_node->x < 10) printf("000%d", current_node->x);
            else if(current_node->x < 100) printf("00%d", current_node->x);
            else if(current_node->x < 1000) printf("0%d", current_node->x);
            else if(current_node->x < 10000) printf("%d", current_node->x);
        }
        current_node = current_node->rlink;
    }
    printf("\n");
}

void char_to_bigint(char* str, Node** bigint) {
    if(str[0] == 0) return;
    Node* head = *bigint;

    int sign = str[0] == '-' ? -1 : 1;
    int len = strlen(str);
    int move_factor = sign == -1 ? 1 : 0;

    for(int i = strlen(str) - 1; i >= 0 + move_factor; i -= 4) {
        int digit_1 = str[i] - 48;
        int digit_2 = i - 1 >= 0 + move_factor ? str[i - 1] - 48 : 0;
        int digit_3 = i - 2 >= 0 + move_factor ? str[i - 2] - 48 : 0;
        int digit_4 = i - 3 >= 0 + move_factor ? str[i - 3] - 48 : 0;

        int digit = digit_4 * 1000 + digit_3 * 100 + digit_2 * 10 + digit_1; 
        insert_digit(bigint, digit);
    }

    head->x = sign * head->x;
}

int is_valid_bigint(char* str) {
    if(str[0] != '-' && (str[0] < '0' || str[0] > '9')) return 0;
    int move_factor = str[0] == '-' ? 1 : 0;

    for(int i = 0 + move_factor; i < strlen(str); i++) {
        if(str[i] < '0' || str[i] > '9') return 0;
    } 

    return 1;
}

void deallocate_bigint(Node** bigint) {
    Node* head = *bigint;
    remove_all_digits(bigint);
    free(head);
    *bigint = NULL;
}

//Returns |BigInt a| > |BigInt b|
int is_abs_greater_than(Node** a, Node**b) {
    Node* head_a = *a;
    Node* head_b = *b;

    if(abs(head_a->x) < abs(head_b->x)) return 0;
    else if(abs(head_a->x) > abs(head_b->x)) return 1;

    Node* current_a = head_a->rlink;
    Node* current_b = head_b->rlink;

    while(current_a != head_a) {
        if(current_a->x > current_b->x) return 1;
        else if(current_a->x < current_b->x) return 0;

        current_a = current_a->rlink;
        current_b = current_b->rlink;
    }

    return 0;
}

Node* bigint_add(Node** a, Node** b) {
    Node* head_a = *a;
    Node* head_b = *b;
    int k = max_int(abs(head_a->x), abs(head_b->x)) + 1;

    int sign_a = 1, sign_b = 1, sign = -1;

    if(is_abs_greater_than(a, b)) {
        if(head_a->x * head_b->x <= 0) sign_b = -1;
    } else {
        if(head_b->x * head_a->x <= 0) sign_a = -1;
    }

    Node* current_a = head_a->llink;
    Node* current_b = head_b->llink;
    Node* result = create_zero_bigint();
    int carry_over = 0;
    
    for(int i = 0; i < k - 1; i++) {
        int digit_a = current_a != head_a ? current_a->x : 0;
        int digit_b = current_b != head_b ? current_b->x : 0;
        int result_digit = sign_a * digit_a + sign_b * digit_b + carry_over;
        int digit = result_digit % 10000;
        digit = digit < 0 ? digit + 10000 : digit;
        double carry_over_double = (double) result_digit / (double) 10000;
        carry_over = floor(carry_over_double);

        insert_digit(&result, digit);

        if(current_a != head_a) current_a = current_a->llink;
        if(current_b != head_b) current_b = current_b->llink;
    }

    if(carry_over != 0) insert_digit(&result, carry_over);
    remove_leading_zeroes(&result);

    if((head_a->x > 0 && head_b->x > 0) || 
        (is_abs_greater_than(a, b) == 1 && head_a->x > 0) ||
        (is_abs_greater_than(a, b) == 0 && head_b->x > 0)) sign = 1;

    result->x = sign * result->x;

    return result;
}

Node* bigint_multiply(Node** a, Node** b) {
    Node* head_a = *a;
    Node* head_b = *b;
    Node* result = create_zero_bigint();

    if(head_a->x == 0 || head_b->x == 0) return result;

    int m = abs(head_a->x);
    int n = abs(head_b->x);
    int k = m + n;
    int sign = -1;

    Node* current_a = head_a->llink;
    Node* current_b = head_b->llink;

    for(int i = 0; i < k; i++) {
        insert_digit(&result, 0);
    }

    for(int i = 0; i < m; i++) {
        int carry_over = 0;
        for(int j = 0; j < n; j++) {
            int result_digit = current_a->x * current_b->x + get_digit(&result, i + j) + carry_over;
            int digit = result_digit % 10000;
            digit = digit < 0 ? digit + 10000 : digit;
            carry_over = result_digit / 10000;

            change_digit(&result, i + j, digit);

            current_b = current_b->llink;
        }
        change_digit(&result, i + n, carry_over);

        current_a = current_a->llink;
        current_b = head_b->llink;
    }

    remove_leading_zeroes(&result);

    if((head_a->x > 0 && head_b->x > 0) ||
        (head_a->x < 0 && head_b->x < 0)) sign = 1;
    
    result->x = sign * result->x;

    return result;
}

Node* bigint_square(Node** bigint) {
    Node* result = bigint_multiply(bigint, bigint);
    return result;
}

Node* bigint_cube(Node** bigint) {
    Node* square_result = bigint_square(bigint);
    Node* result = bigint_multiply(&square_result, bigint);
    deallocate_bigint(&square_result);
    return result;
}

int main() {
    char string[1024];
    Node* a = create_zero_bigint();
    Node* b = create_zero_bigint();
    Node* c = create_zero_bigint();
    Node* d = create_zero_bigint();
    Node* e = create_zero_bigint();
    Node* active = create_zero_bigint();
    Node* prompt = create_zero_bigint();
    int state = 0;

    while(scanf("%s", string) != -1) {
        if(strcmp(string, "clear") == 0) {
            remove_all_digits(&active);
            print_bigint(&active);
            state = 0;
        } else if(strcmp(string, "store") == 0) {
            char second_arg[5];
            scanf("%s", second_arg);

            if(strcmp(second_arg, "A") == 0) {
                copy_bigint(&a, &active);
            } else if(strcmp(second_arg, "B") == 0) {
                copy_bigint(&b, &active);
            } else if(strcmp(second_arg, "C") == 0) {
                copy_bigint(&c, &active);
            } else if(strcmp(second_arg, "D") == 0) {
                copy_bigint(&d, &active);
            } else if(strcmp(second_arg, "E") == 0) {
                copy_bigint(&e, &active);
            }

            state = 0;
        } else if(strcmp(string, "load") == 0) {
            char second_arg[5];
            scanf("%s", second_arg);

            if(strcmp(second_arg, "A") == 0) {
                copy_bigint(&active, &a);
            } else if(strcmp(second_arg, "B") == 0) {
                copy_bigint(&active, &b);
            } else if(strcmp(second_arg, "C") == 0) {
                copy_bigint(&active, &c);
            } else if(strcmp(second_arg, "D") == 0) {
                copy_bigint(&active, &d);
            } else if(strcmp(second_arg, "E") == 0) {
                copy_bigint(&active, &e);
            }

            print_bigint(&active);

            state = 0;
        } else if(strcmp(string, "+/-") == 0) {
            negate_bigint(&active);
            print_bigint(&active);
        } else if(strcmp(string, "^2") == 0) {
            Node* result = bigint_square(&active);
            copy_bigint(&active, &result);
            deallocate_bigint(&result);
            print_bigint(&active);
            state = 0;
        } else if(strcmp(string, "^3") == 0) {
            Node* result = bigint_cube(&active);
            copy_bigint(&active, &result);
            deallocate_bigint(&result);
            print_bigint(&active);
            state = 0;
        } else if(strcmp(string, "+") == 0) {
            state = 1;
        } else if(strcmp(string, "-") == 0) {
            state = 2;
        } else if(strcmp(string, "*") == 0) {
            state = 3;
        } else {
            if(state == 0) {
                remove_all_digits(&active);
                char_to_bigint(string, &active);
            } else if(state == 1) {
                if(is_valid_bigint(string) == 1) {
                    char_to_bigint(string, &prompt);
                    Node* result = bigint_add(&active, &prompt);
                    remove_all_digits(&prompt);
                    remove_all_digits(&active);
                    copy_bigint(&active, &result);
                    deallocate_bigint(&result);
                    print_bigint(&active);
                }

                state = 0;
            } else if(state == 2) {
                if(is_valid_bigint(string) == 1) {
                    char_to_bigint(string, &prompt);
                    negate_bigint(&prompt);
                    Node* result = bigint_add(&active, &prompt);
                    remove_all_digits(&prompt);
                    remove_all_digits(&active);
                    copy_bigint(&active, &result);
                    deallocate_bigint(&result);
                    print_bigint(&active);
                }

                state = 0;
            } else if(state == 3) {
                if(is_valid_bigint(string) == 1) {
                    char_to_bigint(string, &prompt);
                    Node* result = bigint_multiply(&active, &prompt);
                    remove_all_digits(&prompt);
                    remove_all_digits(&active);
                    copy_bigint(&active, &result);
                    deallocate_bigint(&result);
                    remove_all_digits(&prompt);
                    print_bigint(&active);
                }

                state = 0;
            }
        }
    }
}
