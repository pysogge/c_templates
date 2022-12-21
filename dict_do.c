// not working

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_DICT_SIZE 10
#define DICT_SIZE_MULTIPLIER 2
#define DICT_LOAD_FACTOR 0.75

// function prototypes
struct dict_do *dict_do_create();
void dict_do_destroy(struct dict_do *d);
void dict_do_add(struct dict_do *d, char *key, char *value);
void dict_do_dbl_capacity(struct dict_do *d);
unsigned int dict_do_hash(char *key, int size);

// a dynamic and ordered dict with a size that can be adjusted
struct dict_do {
    struct dict_entry **entries;
    int size;
    int count;
};

struct dict_entry {
    char *key;
    char *value;
    int index;
    struct dict_entry *next;
};

struct dict_do *dict_do_create() {
    struct dict_do *d = malloc(sizeof(struct dict_do));
    d->size = DEFAULT_DICT_SIZE;
    d->entries = malloc(sizeof(struct dict_entry *) * d->size);
    d->count = 0;
    memset(d->entries, 0, sizeof(struct dict_entry *) * d->size);
    return d;
}

// double capacity and maintain index order
void dict_do_dbl_capacity(struct dict_do *d) {
    struct dict_do *new_dict = dict_do_create();
    new_dict->size = d->size * DICT_SIZE_MULTIPLIER;
    new_dict->entries = malloc(sizeof(struct dict_entry *) * new_dict->size);
    memset(new_dict->entries, 0, sizeof(struct dict_entry *) * new_dict->size);
    for (int i = 0; i < d->size; i++) {
        struct dict_entry *e = d->entries[i];
        while (e) {
            dict_do_add(new_dict, e->key, e->value);
            e = e->next;
        }
    }
    dict_do_destroy(d);
    d = new_dict;
}


void dict_do_destroy(struct dict_do *d) {
    for (int i = 0; i < d->size; i++) {
        struct dict_entry *e = d->entries[i];
        while (e) {
            struct dict_entry *next = e->next;
            free(e->key);
            free(e->value);
            free(e);
            e = next;
        }
    }
    free(d->entries);
    free(d);
}

// hash function
unsigned int dict_do_hash(char *key, int size) {
    unsigned int hash = 0;
    for (int i = 0; i < strlen(key); i++) {
        hash = (hash << 2) ^ key[i];
    }
    return hash % size;
}

void dict_do_add(struct dict_do *d, char *key, char *value) {
    if (d->count >= d->size * DICT_LOAD_FACTOR) {
        dict_do_dbl_capacity(d);
    }
    unsigned int hash = dict_do_hash(key, d->size);
    struct dict_entry *e = d->entries[hash];
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
    e->index = d->count;
    e->next = d->entries[hash];
    d->entries[hash] = e;
    d->count++;

    printf("Added (%s: %s) to index %d, count is now %d\n", key, value, e->index, d->count);
}

char *dict_do_get(struct dict_do *d, char *key) {
    unsigned int hash = dict_do_hash(key, d->size);
    struct dict_entry *e = d->entries[hash];
    while (e) {
        if (strcmp(e->key, key) == 0) {
            return e->value;
        }
        e = e->next;
    }
    return NULL;
}

// print the dict in index order
void dict_do_print(struct dict_do *d) {
    struct dict_entry **entries = malloc(sizeof(struct dict_entry *) * d->count);
    for (int i = 0; i < d->size; i++) {
        struct dict_entry *e = d->entries[i];
        while (e) {
            entries[e->index] = e;
            e = e->next;
        }
    }
    for (int i = 0; i < d->count; i++) {
        printf("[%d] - (%s: %s)\n", entries[i]->index, entries[i]->key, entries[i]->value);
    }
    free(entries);
}

int main() {
    struct dict_do *d = dict_do_create();
    dict_do_add(d, "a", "1");
    dict_do_add(d, "b", "2");
    dict_do_add(d, "c", "3");
    dict_do_add(d, "d", "4");
    dict_do_add(d, "e", "5");
    dict_do_add(d, "f", "6");
    dict_do_add(d, "g", "7");
    dict_do_add(d, "h", "8");
    dict_do_add(d, "i", "9");
    // dict_do_add(d, "j", "10");
    // dict_do_add(d, "k", "11");
    // dict_do_add(d, "l", "12");
    // dict_do_add(d, "m", "13");
    // dict_do_add(d, "n", "14");
    // dict_do_add(d, "o", "15");
    // dict_do_add(d, "p", "16");
    // dict_do_add(d, "q", "17");
    // dict_do_add(d, "r", "18");
    // dict_do_add(d, "s", "19");
    // dict_do_add(d, "t", "20");
    // dict_do_add(d, "u", "21");
    // dict_do_add(d, "v", "22");
    // dict_do_add(d, "w", "23");
    // dict_do_add(d, "x", "24");
    // dict_do_add(d, "y", "25");
    // dict_do_add(d, "z", "26");
    dict_do_print(d);
    // dict_do_destroy(d);
    return 0;
}