#pragma once
#define NDEBUG
// https://github.com/dotnet/runtime/blob/v7.0.0/src/mono/wasi/mono-wasi-driver/driver.c
#include <string.h>

#include <mono-wasi/driver.h>
#include <mono/metadata/exception.h>

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define IMPORT(a, b) __attribute__((import_module(a), import_name(b)))

// This doesn't work
IMPORT("env", "do_something") extern int64_t do_something(int64_t);

// This works
// IMPORT("env", "do_something") extern int64_t do_something(int32_t);

// This doesn't work
// IMPORT("env", "do_something") extern int64_t do_something(int32_t, int32_t);

// This works
// IMPORT("env", "do_something") extern int32_t do_something(int32_t, int32_t);

// This doesn't work
// IMPORT("env", "do_something") extern int32_t do_something(int32_t, int32_t, int32_t, int32_t, int32_t);


void repro_attach_internal_calls()
{
    mono_add_internal_call("Program::do_something", do_something);
}