#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_KEYS 256

typedef struct Node {
    char* key;
    char* data;
    struct Node* next;
} Node;

Node* create_node(char key[], int key_size, char data[], int data_size) {
    Node* node = malloc(sizeof(Node));
    node->key = malloc(sizeof(char) * (key_size + 1));
    node->data = malloc(sizeof(char) * (data_size + 1));
    strcpy(node->key, key);
    strcpy(node->data, data);
    node->next = NULL;
    return node;
}

Node** create_hash_table(int size) {
    Node** table = malloc(sizeof(Node*) * size);
    for(int i = 0; i < size; ++i) table[i] = NULL;
    return table;
}

int str_to_key(char key[]) {
    int i = 0;
    int intkey = 0;

    while(key[i] != 0) {
        intkey += (key[i] + i * 63);
        ++i;
    }

    return intkey >> 1;
}

int hash(char key[], int size) {
    int hashkey = str_to_key(key);
    return hashkey % size;
}

Node* get_tail(Node* list) {
    Node* current_node = list;
    while(current_node != NULL && current_node->next != NULL) {
        current_node = current_node->next;
    }

    return current_node;
}

Node* search(Node** table, int size, char key[]) {
    int hashkey = hash(key, size);
    Node* current_node = table[hashkey];
    while(current_node != NULL) {
        if(strcmp(current_node->key, key) == 0) return current_node;
        current_node = current_node->next;
    }

    return NULL;
}

void insert(Node*** hash_table, int* key_size, char key[], char data[]) {
    Node** table = *hash_table;
    int size = *key_size;

    int hashkey = hash(key, size);
    Node* node = get_tail(table[hashkey]);
    if(node == NULL) table[hashkey] = create_node(key, strlen(key), data, strlen(data));
    else node->next = create_node(key, strlen(key), data, strlen(data));
}

void delete(Node*** hash_table, int* key_size, char key[], char** value) {
    Node** table = *hash_table;
    int size = *key_size;
    *value = malloc(sizeof(char) * 102);

    int hashkey = hash(key, size);
    Node* previous_node = NULL;
    Node* current_node = table[hashkey];
    while(current_node != NULL) {
        if(strcmp(current_node->key, key) == 0) {
            strcpy(*value, current_node->data);
            if(previous_node != NULL) previous_node->next = current_node->next;
            else table[hashkey] = current_node->next;
            free(current_node->key);
            free(current_node->data);
            free(current_node);
            return;
        };
        previous_node = current_node;
        current_node = current_node->next;
    }

    strcpy(*value, "");
}

void print_search(Node* node) {
    if(node != NULL) {
        printf("%s : %s\n", node->key, node->data);
    } else {
        printf("KEY-VALUE DOES NOT EXIST\n");
    }
}

void print_insert(char key[]) {
    printf("INSERT %s\n", key);
}

void print_delete(char key[], char* data) {
    if(strcmp(data, "") != 0) {
        printf("DELETE %s\n", key);
    } else {
        printf("KEY-VALUE DOES NOT EXIST\n");
    }
}

int main() {
    int size = HASH_KEYS;
    Node** table = create_hash_table(size);
    
    int operations;
    scanf("%d", &operations);

    for(int i = 0; i < operations; ++i) {
        char str[4];
        scanf("%s", str);

        if(str[0] == 'i') {
            char key[102];
            char data[102];
            scanf("%s : %s", key, data);

            insert(&table, &size, key, data);
            print_insert(key);
        } else if(str[0] == 'd') {
            char key[102];
            char* data = NULL;
            scanf("%s", key);

            delete(&table, &size, key, &data);
            print_delete(key, data);
            free(data);
        } else if(str[0] == 's') {
            char key[102];
            scanf("%s", key);

            Node* node = search(table, size, key);
            print_search(node);
        }
    }
}