#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_DICT_SIZE 10
#define DICT_SIZE_MULTIPLIER 2

// function definitions
struct dict_d *dict_d_create();
void dict_d_destroy(struct dict_d *d);
void dict_d_add(struct dict_d *d, char *key, char *value);
void dict_d_dbl_capacity(struct dict_d *d);

// a dynamic dict with a size that can be adjusted
struct dict_d {
    struct dict_entry **entries;
    int size;
};

struct dict_entry {
    char *key;
    char *value;
    struct dict_entry *next;
};

struct dict_d *dict_d_create() {
    struct dict_d *d = malloc(sizeof(struct dict_d));
    d->size = DEFAULT_DICT_SIZE;
    d->entries = malloc(sizeof(struct dict_entry *) * d->size);
    memset(d->entries, 0, sizeof(struct dict_entry *) * d->size);
    return d;
}

void dict_d_dbl_capacity(struct dict_d *d) {
    struct dict_d *new_dict = dict_d_create();
    new_dict->size = d->size * DICT_SIZE_MULTIPLIER;
    new_dict->entries = malloc(sizeof(struct dict_entry *) * new_dict->size);
    memset(new_dict->entries, 0, sizeof(struct dict_entry *) * new_dict->size);
    for (int i = 0; i < d->size; i++) {
        struct dict_entry *e = d->entries[i];
        while (e) {
            dict_d_add(new_dict, e->key, e->value);
            e = e->next;
        }
    }
    dict_d_destroy(d);
    d = new_dict;
}

void dict_d_destroy(struct dict_d *d) {
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
unsigned int dict_d_hash(char *key, int size) {
    unsigned int hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;

    return hash % size;
}

void dict_d_add(struct dict_d *d, char *key, char *value) {
    unsigned int hash = dict_d_hash(key, d->size);
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
    e->next = d->entries[hash];
    d->entries[hash] = e;
}

char *dict_d_get(struct dict_d *d, char *key) {
    unsigned int hash = dict_d_hash(key, d->size);
    struct dict_entry *e = d->entries[hash];
    while (e) {
        if (strcmp(e->key, key) == 0) {
            return e->value;
        }
        e = e->next;
    }
    return NULL;
}

// 

int main() {
    struct dict_d *d = dict_d_create();
    dict_d_add(d, "key1", "value1");
    dict_d_add(d, "key2", "value2");
    dict_d_add(d, "key3", "value3");
    dict_d_add(d, "key4", "value4");
    dict_d_add(d, "key5", "value5");
    dict_d_add(d, "key6", "value6");
    dict_d_add(d, "key7", "value7");
    dict_d_add(d, "key8", "value8");
    dict_d_add(d, "key9", "value9");
    dict_d_add(d, "key10", "value10");
    dict_d_add(d, "key11", "value11");
    dict_d_add(d, "key12", "value12");
    dict_d_add(d, "key13", "value13");
    dict_d_add(d, "key14", "value14");
    dict_d_add(d, "key15", "value15");
    dict_d_add(d, "key16", "value16");
    dict_d_add(d, "key17", "value17");
    dict_d_add(d, "key18", "value18");
    dict_d_add(d, "key19", "value19");
    dict_d_add(d, "key20", "value20");
    dict_d_add(d, "key21", "value21");
    dict_d_add(d, "key22", "value22");
    dict_d_add(d, "key23", "value23");
    dict_d_add(d, "key24", "value24");
    dict_d_add(d, "key25", "value25");
    dict_d_add(d, "key26", "value26");
    dict_d_add(d, "key27", "value27");
    dict_d_add(d, "key28", "value28");
    dict_d_add(d, "key29", "value29");
    dict_d_add(d, "key30", "value30");

    // print all keys and values
    for (int i = 0; i < d->size; i++) {
        struct dict_entry *e = d->entries[i];
        while (e) {
            printf("%s: %s\n", e->key, e->value);
            e = e->next;
        }
    }

    dict_d_destroy(d);

    return 0;
}
