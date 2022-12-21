#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICT_SIZE 100

struct dict_entry {
    char *key;
    char *value;
    struct dict_entry *next;
};

// a dict with a fixed size
struct dict {
    struct dict_entry *entries[DICT_SIZE];
};

struct dict *dict_create() {
    struct dict *d = malloc(sizeof(struct dict));
    memset(d->entries, 0, sizeof(d->entries));
    return d;
}

void dict_destroy(struct dict *d) {
    for (int i = 0; i < DICT_SIZE; i++) {
        struct dict_entry *e = d->entries[i];
        while (e) {
            struct dict_entry *next = e->next;
            free(e->key);
            free(e->value);
            free(e);
            e = next;
        }
    }
    free(d);
}

//
unsigned int dict_hash(char *key) {
    unsigned int hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;

    return hash % DICT_SIZE;
}

void dict_add(struct dict *d, char *key, char *value) {
    unsigned int index = dict_hash(key);
    struct dict_entry *e = d->entries[index];
    while (e) {
        if (strcmp(e->key, key) == 0) {
            free(e->value);
            e->value = strdup(value);
            return;
        }
        e = e->next;
    }

    e = malloc(sizeof(struct dict_entry));
    e->key = strdup(key);
    e->value = strdup(value);
    e->next = d->entries[index];
    d->entries[index] = e;
}

char *dict_get(struct dict *d, char *key) {
    unsigned int index = dict_hash(key);
    struct dict_entry *e = d->entries[index];
    while (e) {
        if (strcmp(e->key, key) == 0)
            return e->value;
        e = e->next;
    }
    return NULL;
}

int main() {
    struct dict *d = dict_create();

    dict_add(d, "apple", "red");
    dict_add(d, "banana", "yellow");
    dict_add(d, "orange", "orange");

    printf("Apple is %s.\n", dict_get(d, "apple"));
    printf("Banana is %s.\n", dict_get(d, "banana"));
    printf("Orange is %s.\n", dict_get(d, "orange"));

    dict_destroy(d);
}
