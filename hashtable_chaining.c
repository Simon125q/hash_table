#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 30

typedef struct 
{
    char name[MAX_NAME];
    int age;
    struct person * next;
} person;

person * hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i ++) {
        hash_value += name[i];
        hash_value *= name[i];
        hash_value %= TABLE_SIZE;
    }
   
    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
}

void print_table() {
    for (int i = 0; i < TABLE_SIZE; i++){
        if (hash_table[i] == NULL){
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t", i);
            person *tmp = hash_table[i];
            while (tmp != NULL) {
                printf("%s - ", tmp->name);
                tmp = tmp -> next;
            }
            printf("\n");
        }
    }
}

bool hash_table_insert(person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    p -> next = hash_table[index];
    hash_table[index] = p;
    return true;
}

person *hash_table_lookup(char *name){
    int index = hash(name);
    person *tmp = hash_table[index];
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0){
        tmp = tmp->next;
    }
    return tmp;
}

person *hash_table_delete(char *name){
    int index = hash(name);
    person *tmp = hash_table[index];
    person *prev = NULL;
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0){
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    if (prev == NULL) hash_table[index] = tmp -> next;
    else prev -> next = tmp -> next;
    return tmp;
}

int main(){

    person harry = {.name = "Harry", .age = 20};
    person ron = {.name = "Ron", .age = 19};
    person hermione = {.name = "Hermione", .age = 21};
    person hagrid = {.name = "Hagrid", .age = 62};
    person syrius = {.name = "Syrius", .age = 45};
    person neville = {.name = "Neville", .age = 18};
    person dumbledor = {.name = "Dumbledor", .age = 94};
    person snape = {.name = "Snape", .age = 50};

    hash_table_insert(&harry);
    hash_table_insert(&ron);
    hash_table_insert(&hermione);
    hash_table_insert(&hagrid);
    hash_table_insert(&syrius);
    hash_table_insert(&neville);
    hash_table_insert(&dumbledor);
    hash_table_insert(&snape);

    print_table();

    person *tmp = hash_table_lookup("Harry");
    if (tmp == NULL) {
        printf("Not found! \n");
    } else {
        printf("Found %s \n", tmp->name);
    }

    tmp = hash_table_lookup("Ron");
    if (tmp == NULL) {
        printf("Not found! \n");
    } else {
        printf("Found %s \n", tmp->name);
    }

    hash_table_delete("Ron");
    tmp = hash_table_lookup("Ron");
    if (tmp == NULL) {
        printf("Not found! \n");
    } else {
        printf("Found %s \n", tmp->name);
    }

    tmp = hash_table_lookup("Draco");
    if (tmp == NULL) {
        printf("Not found! \n");
    } else {
        printf("Found %s \n", tmp->name);
    }
    // printf("Harry => %u\n", hash("Harry"));
    // printf("Ron => %u\n", hash("Ron"));
    // printf("Hermione => %u\n", hash("Hermione"));
    // printf("Hagrid => %u\n", hash("Hagrid"));
    // printf("Draco => %u\n", hash("Draco"));
    // printf("Neville => %u\n", hash("Neville"));

    return 0;
}