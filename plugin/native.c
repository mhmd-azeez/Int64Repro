

#include <string.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/exception.h>

// https://github.com/dotnet/runtime/blob/v7.0.0/src/mono/wasi/mono-wasi-driver/driver.c
#include <string.h>

#include "driver.h"

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define IMPORT(a, b) __attribute__((import_module(a), import_name(b)))

IMPORT("native", "do_something")
extern int64_t do_something(int64_t v);

extern void mono_wasm_invoke_method_ref (MonoMethod *method, MonoObject **this_arg_in, void *params[], MonoObject **_out_exc, MonoObject **out_result);

void mono_wasm_load_runtime (const char *unused, int debug_level);

#ifdef WASI_AFTER_RUNTIME_LOADED_DECLARATIONS
// This is supplied from the MSBuild itemgroup @(WasiAfterRuntimeLoaded)
WASI_AFTER_RUNTIME_LOADED_DECLARATIONS
#endif

__attribute__((export_name("_initialize"))) void initialize() {
	mono_wasm_load_runtime("", 0);
}
MonoMethod* method_count_vowels;
__attribute__((export_name("hi"))) int hi()
{
    if (!method_count_vowels)
    {
        method_count_vowels = lookup_dotnet_method("Int64Repro.dll", "", "Program", "hi", -1);
        assert(method_count_vowels);
    }
    
    void* method_params[] = { };
    MonoObject* exception = NULL;
    MonoObject* result = NULL;
    mono_wasm_invoke_method_ref(method_count_vowels, NULL, method_params, &exception, &result);
    assert(!exception);
    
    int int_result = 0;  // Default value

    if (result != NULL) {
        int_result = *(int*)mono_object_unbox(result);
    }

    return int_result;
}
