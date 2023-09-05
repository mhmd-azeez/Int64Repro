#pragma once
#define NDEBUG
// https://github.com/dotnet/runtime/blob/v7.0.0/src/mono/wasi/mono-wasi-driver/driver.c
#include <string.h>

// #include <mono-wasi/driver.h>
// #include <mono/metadata/exception.h>

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define IMPORT(a, b) __attribute__((import_module(a), import_name(b)))

IMPORT("native", "do_something")
extern int64_t do_something_wrapper(int64_t v);

int64_t do_something(int64_t v) {
    return do_something_wrapper(v);
}