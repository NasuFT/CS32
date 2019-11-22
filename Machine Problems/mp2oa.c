#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_KEYS 128
#define NOTFOUND_ERR_MSG "KEY-VALUE DOES NOT EXIST"
#define INSERT_MSG "INSERT "
#define DELETE_MSG "DELETE "

typedef struct Node {
    char key[128];
    char data[128];
    int deleted;
} Node;

Node* create_node(char key[], char data[]) {
    Node* node = malloc(sizeof(Node));
    strcpy(node->key, key);
    strcpy(node->data, data);
    node->deleted = 0;
    return node;
}

Node** create_hash_table(int size) {
    Node** table = malloc(sizeof(Node*) * size);
    for(int i = 0; i < size; ++i) table[i] = NULL;
    return table;
}

void free_hash_table(Node** table) {
    free(table);
}

double get_load_factor(Node** table, int size) {
    int count = 0;
    
    for(int i = 0; i < size; ++i) {
        if(table[i] != NULL && table[i]->deleted != 1) {
            ++count;
        }
    }

    return (double) count / (double) size;
}

void print_table(Node** table, int size) {
    printf("------|---------------|---------------|---\n");
    for(int i = 0; i < size; i++) {
        printf("|%5d|%15s|%15s|%2d|\n", i, table[i] == NULL ? "" : table[i]->key, table[i] == NULL ? "" : table[i]->data, table[i] == NULL ? -1 : table[i]->deleted);
    }
    printf("------|---------------|---------------|---\n");
}

int str_to_key(char key[]) {
    char i = 0;
    int intkey = 0;

    while(key[i] != 0) {
        intkey += key[i] << 1;
        intkey << 1;
        ++i;
    }

    return intkey >> 1;
}

int h1(int hashkey, int size) {
    return hashkey % size;
}

int h2(int hashkey, int size) {
    return (((1731 * hashkey + 520123) % 524287) % size) | 1;
}

int hash(char key[], int size, int i) {
    int hashkey = str_to_key(key);
    return (h1(hashkey, size) + i * h2(hashkey, size)) % size;
}

void resize_table(Node*** hash_table, int* key_size, int new_size) {
    Node** table = *hash_table;
    int size = *key_size;
    Node** new_table = create_hash_table(new_size);

    for(int i = 0; i < size; ++i) {
        if(table[i] != NULL) {
            if(table[i]->deleted == 1) {
                free(table[i]);
                table[i] = NULL;
                continue;
            }

            int hashkey = hash(table[i]->key, new_size, 0);

            for(int j = 1; new_table[hashkey] != NULL; ++j) {
                hashkey = hash(table[i]->key, new_size, j);
            }

            new_table[hashkey] = table[i];
        }
    }

    free_hash_table(table);
    *hash_table = new_table;
    *key_size = new_size;
}

void double_table(Node*** hash_table, int* key_size) {
    resize_table(hash_table, key_size, *key_size * 2);
}

void half_table(Node*** hash_table, int* key_size) {
    resize_table(hash_table, key_size, *key_size / 2);
}

Node* search(Node** table, int size, char key[]) {
    int hashkey = hash(key, size, 0);

    for(int i = 1; table[hashkey] != NULL && (table[hashkey]->deleted == 1 || strcmp(table[hashkey]->key, key) != 0); ++i) 
        hashkey = hash(key, size, i);

    return table[hashkey];
}

void insert(Node*** hash_table, int* key_size, char key[], char data[]) {
    Node** table = *hash_table;
    int size = *key_size;

    int hashkey = hash(key, size, 0);
    for(int i = 1; table[hashkey] != NULL && table[hashkey]->deleted != 1; ++i) {
        hashkey = hash(key, size, i);
    }

    Node* node = NULL;
    if(table[hashkey] == NULL) {
        node = create_node(key, data);
        table[hashkey] = node;
    } else {
        node = table[hashkey];
        strcpy(node->key, key);
        strcpy(node->data, data);
        node->deleted = 0;
    }

    if(get_load_factor(table, size) >= 0.7) {
        double_table(hash_table, key_size);
    }
}

char* delete(Node*** hash_table, int* key_size, char key[]) {
    Node** table = *hash_table;
    int size = *key_size;

    Node* node = search(table, size, key);
    if(node != NULL)
        node->deleted = 1;

    return node == NULL ? "" : node->data;
}

void print_search(Node* node) {
    if(node != NULL) {
        printf("%s : %s\n", node->key, node->data);
    } else {
        printf("%s\n", NOTFOUND_ERR_MSG);
    }
}

void print_insert(char key[]) {
    char str[128];
    strcpy(str, INSERT_MSG);
    strcat(str, key);
    printf("%s\n", str);
}

void print_delete(char key[], char data[]) {
    if(strcmp("", data) != 0) {
        char str[128];
        strcpy(str, DELETE_MSG);
        strcat(str, key);
        printf("%s\n", str);
    } else {
        printf("%s\n", NOTFOUND_ERR_MSG);
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
            char key[128];
            char data[128];
            scanf("%s : %s", key, data);

            insert(&table, &size, key, data);
            print_insert(key);
        } else if(str[0] == 'd') {
            char key[128];
            scanf("%s", key);

            char* data = delete(&table, &size, key);
            print_delete(key, data);
        } else if(str[0] == 's') {
            char key[128];
            scanf("%s", key);

            Node* node = search(table, size, key);
            print_search(node);
        }
    }
}