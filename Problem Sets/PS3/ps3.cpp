#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;

#define HASH_KEYS 100

typedef struct Node {
    int key;
    int data;
    struct Node* next;
} Node;

Node* create_node(int key, int x) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->data = x;
    node->next = NULL;
    return node;
}

int hash_key(int key) {
    return key % 100;
}

Node* get_tail(Node* list) {
    Node* current_node = list;
    Node* previous_node = NULL;
    while(current_node != NULL) {
        previous_node = current_node;
        current_node = current_node->next;
    }
    return previous_node;
}

void insert_right(Node** a, Node** b) {
    if(*a == NULL) *a = *b;
    else (*a)->next = *b;
}

void insert_chain(Node* list, int key, int x) {
    Node* node = create_node(key, x);
    Node* tail = get_tail(list);
    insert_right(&tail, &node);
}

void reset_table(Node* table[], int size) {
    for(int i = 0; i < size; i++) {
        Node* current_node = table[i];
        while(current_node != NULL) {
            Node* node = current_node;
            current_node = current_node->next;
            free(node);
        }

    }
}

int is_hkey_occupied(Node* table[], int hash_key) {
    return table[hash_key] != NULL;
}

int probe_func_1(Node* table[], int hashkey) {
    int x = hashkey;
    int i = 1;

    while(is_hkey_occupied(table, x) == 1) {
        x = (hash_key(hashkey) - (i)) % 100;
        if(x < 0) x += 100;
        i++;
    }

    return x;
}

int probe_func_2(Node* table[], int hashkey) {
    int x = hashkey;

    for(int i = 1; is_hkey_occupied(table, x) == 1; i++) {
        x = (hash_key(hashkey) - (5 * i * i) - (6 * i));
        if(x < 0) x += 100;
    }

    return x;
}

int occupy_hkey(Node* table[], int hashkey, int key, int x) {
    Node* node = create_node(key, x);
    insert_right(&table[hashkey], &node);
}

int main() {
    Node* table[HASH_KEYS];
    
    srand(time(NULL));

    for(int i = 0; i < HASH_KEYS; i++) table[i] = NULL;

    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 30; i++) {
        for(int i = 0; i < 50; i++) {
            int key = rand();
            int hashkey = hash_key(key);
            insert_chain(table[hashkey], key, rand());
        }

        reset_table(table, HASH_KEYS);
        for(int i = 0; i < HASH_KEYS; i++) table[i] = NULL;
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    cout << "Chaining (50 insertion - Total): " << duration << " ns\n";
    duration /= 30.0f * (float) 50;
    cout << "Chaining (50 insertion - Average): " << duration << " ns\n";

    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 30; i++) {
        for(int i = 0; i < 100; i++) {
            int key = rand();
            int hashkey = hash_key(key);
            insert_chain(table[hashkey], key, rand());
        }

        reset_table(table, HASH_KEYS);
        for(int i = 0; i < HASH_KEYS; i++) table[i] = NULL;
    }
    end = chrono::high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    cout << "Chaining (100 insertions - Total): " << duration << " ns\n";
    duration /= 30.0f * (float) 100;
    cout << "Chaining (100 insertions - Average: " << duration << " ns\n";

    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 30; i++) {
        for(int i = 0; i < 200; i++) {
            int key = rand();
            int hashkey = hash_key(key);
            insert_chain(table[hashkey], key, rand());
        }

        reset_table(table, HASH_KEYS);
        for(int i = 0; i < HASH_KEYS; i++) table[i] = NULL;
    }
    end = chrono::high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    cout << "Chaining (200 insertions - Total): " << duration << " ns\n";
    duration /= 30.0f * (float) 200;
    cout << "Chaining (200 insertions - Average: " << duration << " ns\n";

    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 30; i++) {
        for(int i = 0; i < 500; i++) {
            int key = rand();
            int hashkey = hash_key(key);
            insert_chain(table[hashkey], key, rand());
        }

        reset_table(table, HASH_KEYS);
        for(int i = 0; i < HASH_KEYS; i++) table[i] = NULL;
    }
    end = chrono::high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    cout << "Chaining (500 insertions - Total): " << duration << " ns\n";
    duration /= 30.0f * (float) 500;
    cout << "Chaining (500 insertions - Average: " << duration << " ns\n";

    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 30; i++) {
        for(int i = 0; i < 100; i++) {
            int key = rand();
            int hashkey = hash_key(key);
            if(is_hkey_occupied(table, hashkey) == 1) hashkey = probe_func_1(table, hashkey);
            occupy_hkey(table, hashkey, key, rand());
        }

        reset_table(table, HASH_KEYS);
        for(int i = 0; i < HASH_KEYS; i++) table[i] = NULL;
    }
    end = chrono::high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    cout << "Probing function 1 (100 insertions - Total): " << duration << " ns\n";
    duration /= 30.0f * (float) 100;
    cout << "Probing function 1 (100 insertions - Average): " << duration << " ns\n";

    start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 30; i++) {
        for(int i = 0; i < 100; i++) {
            int key = rand();
            int hashkey = hash_key(key);
            if(is_hkey_occupied(table, hashkey) == 1) hashkey = probe_func_2(table, hashkey);
            occupy_hkey(table, hashkey, key, rand());
        }

        reset_table(table, HASH_KEYS);
        for(int i = 0; i < HASH_KEYS; i++) table[i] = NULL;
    }
    end = chrono::high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    cout << "Probing function 2 (100 insertions - Total): " << duration << " ns\n";
    duration /= 30.0f * (float) 100;
    cout << "Probing function 2 (100 insertions - Average): " << duration << " ns\n";
}