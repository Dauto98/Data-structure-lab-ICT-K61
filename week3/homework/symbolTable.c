#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"

#define INITIAL_SIZE 2
#define INCREMENTAL_SIZE 2

SymbolTable* createSymbolTable(Entry* (*makeNode)(void*, void*), int (*compare)(void*, void*)) {
	SymbolTable* table = malloc(sizeof(SymbolTable));
	if (table != NULL) {
		table->entries = malloc(sizeof(Entry) * INITIAL_SIZE);
		if (table->entries != NULL) {
			table->total = 0;
			table->size = INITIAL_SIZE;
			table->makeNode = makeNode;
			table->compare = compare;

			return table;
		}
	}
	return NULL;
}

void dropSymbolTable(SymbolTable* table) {
	for (int i = 0; i < table->total; i++) {
		free(table->entries[i].key);
		free(table->entries[i].value);
		free(&(table->entries[i]));
	}
	free(table);
}

void addEntry(void* key, void* value, SymbolTable* table) {
	Entry* entry = getEntry(key, table);
	if (entry == NULL) {
		if (table->total >= table->size) {
			Entry* newTableEntries = realloc(table->entries, (table->size + INCREMENTAL_SIZE) * sizeof(Entry));
			if (newTableEntries != NULL) {
				table->entries = newTableEntries;
				table->size += INCREMENTAL_SIZE;
			} else {
				return;
			}
		}
		entry = table->makeNode(key, value);
		table->entries[table->total] = *entry;
		table->total += 1;
	}
}

Entry* getEntry(void* key, SymbolTable* table) {
	for (int i = 0; i < table->total; i++) {
		if (table->compare(table->entries[i].key, key) == 0) {
			return &(table->entries[i]);
		}
	}
	return NULL;
}
