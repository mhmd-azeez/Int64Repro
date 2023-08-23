#pragma once
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include <mono-wasi/driver.h>
#include <mono/metadata/exception.h>

#define IMPORT(a, b) __attribute__((import_module(a), import_name(b)))

typedef struct {
    const char* name;
    void* addr;
} MonoDlMapping;

int count = 1;
void do_something(void) {
    int x = 1;
    x++;
    count += x;
    // Your function implementation
}

static MonoDlMapping hardcoded_mapping = { "do_something", &do_something };

char* basic_strdup(const char* source) {
    if (!source) return NULL;
    char* dest = (char*)malloc(strlen(source) + 1);
    if (dest) {
        strcpy(dest, source);
    }
    return dest;
}

static void*
dl_mapping_open(const char* file, int flags, char** err, void* user_data) {
   
    if (strcmp(file, "mylib") == 0) {
        *err = basic_strdup("");
        return &hardcoded_mapping;
    }
    else {
        *err = basic_strdup("File not registered");
        return NULL;
    }
}

static void*
dl_mapping_symbol(void* handle, const char* symbol, char** err, void* user_data) {
    return hardcoded_mapping.addr;
    if (strcmp(symbol, hardcoded_mapping.name) == 0) {
        *err = basic_strdup("");
        return hardcoded_mapping.addr;
    }
    else {
        *err = basic_strdup("Symbol not found");
        return NULL;
    }
}



void mono_dl_register_library() {
    mono_dl_fallback_register(dl_mapping_open, dl_mapping_symbol, NULL, NULL);
    //hardcoded_mapping.addr = do_something;
}

void repro_attach_internal_calls() {
    mono_dl_register_library();
    // mono_add_internal_call("Program::do_something", do_something_wrapper); // Assuming this exists somewhere
}
