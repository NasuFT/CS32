#include <stdio.h>
#include <stdlib.h>

#define HASH_KEYS 8

typedef struct Node {
    int key;
    int x;
} Node;

Node* create_node(int key, int x) {
    Node* node = malloc(sizeof(Node));
    node->key = key;
    node->x = x;
    return node;
}

Node** create_hash_table(int size) {
    Node** table = malloc(sizeof(Node*) * size);
    for(int i = 0; i < size; i++) {
        table[i] = NULL;
    }

    return table;
}

int h1(int key, int size) {
    return key % size;
}

int h2(int key, int size) {
    return (((1731 * key + 520123) % 524287) % size) | 1;
}

int hash(int key, int i, int size) {
    return (h1(key, size) + (i * h2(key, size))) % size;
}

int is_table_full(Node** table, int size) {
    for(int i = 0; i < size; i++) {
        if(table[i] == NULL) return 0;
    }

    return 1;
}

int is_table_quarter_full(Node** table, int size) {
    int count = 0;

    for(int i = 0; i < size; i++) {
        if(table[i] != NULL) count++;
    }

    return count <= size / 4 ? 1 : 0;
}

void print_table(Node** table, int size) {
    for(int i = 0; i < size; i++) {
        int num = table[i] == NULL ? 0 : table[i]->x;
        printf("%d: %d\n", i, num);
    }
}

void print_double_table(Node** table, int size) {
    printf("DOUBLING HASH TABLE\n");
    print_table(table, size);
}

void print_half_table(Node** table, int size) {
    printf("HALVING HASH TABLE\n");
    print_table(table, size);
}

void double_table(Node*** old_table, int* size) {
    Node** table = *old_table;
    int new_size = *size * 2;
    Node** new_table = create_hash_table(new_size);

    for(int i = 0; i < *size; i++) {
        int key = table[i]->key;
        int hashkey = hash(key, 0, new_size);

        for(int j = 1; new_table[hashkey] != NULL; j++) {
            hashkey = hash(key, j, new_size);
        }

        new_table[hashkey] = table[i];
    }

    free(table);
    *old_table = new_table;
    *size = new_size;
}

void half_table(Node*** hash_table, int* size) {
    Node** table = *hash_table;
    int new_size = *size / 2;
    Node** new_table = create_hash_table(new_size);

    for(int i = 0; i < *size; i++) {
        if(table[i] == NULL) continue;
        int key = table[i]->key;
        int hashkey = hash(key, 0, new_size);

        for(int j = 1; new_table[hashkey] != NULL; j++) {
            hashkey = hash(key, j, new_size);
        }

        new_table[hashkey] = table[i];
    }

    free(table);
    *hash_table = new_table;
    *size = new_size;
}

void insert(Node*** old_table, int* size, int key, int x) {
    Node** table = *old_table;
    Node* node = create_node(key, x);
    int hashkey = hash(key, 0, *size);

    for(int i = 1; table[hashkey] != NULL; i++) {
        hashkey = hash(key, i, *size);
    }

    table[hashkey] = node;

    if(is_table_full(table, *size) == 1) {
        double_table(old_table, size);
        print_double_table(*old_table, *size);
    }
}

void delete(Node*** hash_table, int* size, int x) {
    Node** table = *hash_table;
    for(int i = 0; i < *size; i++) {
        if(table[i] != NULL && table[i]->x == x) {
            free(table[i]);
            table[i] = NULL;
            break;
        }
    }

    if(is_table_quarter_full(table, *size) == 1) {
        half_table(hash_table, size);
        print_half_table(*hash_table, *size);
    }
}

void print_final_state(Node** table, int size) {
    printf("FINAL STATE\n");
    print_table(table, size);
}

int main() {
    int size = HASH_KEYS;
    Node** table = create_hash_table(size);

    int commands;
    scanf("%d", &commands);

    for(int i = 0; i < commands; i++) {
        char c[3];
        int x;
        scanf("%s %d", c, &x);

        if(c[0] == 'i') {
            insert(&table, &size, x, x);
        } else {
            delete(&table, &size, x);
        }
    }

    print_final_state(table, size);
}