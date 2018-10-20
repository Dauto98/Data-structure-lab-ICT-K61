#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

typedef struct {
	void* key;
	void* value;
} Entry;

typedef struct {
	Entry* entries;
	int size;
	int total;
	Entry* (*makeNode)(void*, void*);
	int (*compare)(void*, void*);
} SymbolTable;

SymbolTable* createSymbolTable(Entry* (*makeNode)(void*, void*), int (*compare)(void*, void*));

void dropSymbolTable(SymbolTable* table);

void addEntry(void* key, void* value, SymbolTable* table);

Entry* getEntry(void* key, SymbolTable* table);

#endif
