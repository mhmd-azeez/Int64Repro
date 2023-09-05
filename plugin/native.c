

#include <string.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/exception.h>

// https://github.com/dotnet/runtime/blob/v7.0.0/src/mono/wasi/mono-wasi-driver/driver.c
#include <string.h>

#include "driver.h"
// #include <mono/metadata/exception.h>

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define IMPORT(a, b) __attribute__((import_module(a), import_name(b)))

IMPORT("native", "do_something")
extern int64_t do_something_wrapper(int64_t v);

int64_t do_something(int64_t v) {
    return do_something_wrapper(v);
}




// void dotnet_wasi_registerbundledassemblies();




// // This symbol's implementation is generated during the build
// const char* dotnet_wasi_getentrypointassemblyname();


// #ifdef WASI_AFTER_RUNTIME_LOADED_DECLARATIONS
// // This is supplied from the MSBuild itemgroup @(WasiAfterRuntimeLoaded)
// WASI_AFTER_RUNTIME_LOADED_DECLARATIONS
// #endif

// int _initialize() {

//     dotnet_wasi_registerbundledassemblies();

//     MonoDomain *domain;

//     domain = mono_jit_init ("main");

// #ifdef WASI_AFTER_RUNTIME_LOADED_CALLS
// 	// This is supplied from the MSBuild itemgroup @(WasiAfterRuntimeLoaded)
// 	WASI_AFTER_RUNTIME_LOADED_CALLS
// #endif
// #ifndef WASM_SINGLE_FILE
// 	mono_set_assemblies_path("managed");
// #endif
// 	mono_wasm_load_runtime("", 0);

// 	int arg_ofs = 0;
// #ifdef WASM_SINGLE_FILE
// 	/*
// 	 * For single-file bundle, running with wasmtime:
// 	 *
// 	 *  $ wasmtime run --dir . MainAssembly.wasm [args]
// 	 *
// 	 * arg0: MainAssembly
// 	 * arg1-..: args
// 	 */
// 	const char* assembly_name = dotnet_wasi_getentrypointassemblyname();
// 	MonoAssembly* assembly = mono_assembly_open(assembly_name, NULL);
// #else
// 	/*
// 	 * For default case which uses dotnet.wasm, running with wasmtime:
// 	 *
// 	 *  $ wasmtime run --dir . dotnet.wasm MainAssembly [args]
// 	 *
// 	 * arg0: dotnet.wasm
// 	 * arg1: MainAssembly
// 	 * arg2-..: args
// 	 */

// 	const char *assembly_name = argv[1];
// 	arg_ofs = 1;
// 	MonoAssembly* assembly = mono_wasm_assembly_load (assembly_name);
// 	if (!assembly) {
// 		printf("Could not load assembly %s\n", assembly_name);
// 		return 1;
// 	}
// #endif

// 	MonoMethod* entry_method = mono_wasi_assembly_get_entry_point (assembly);
// 	if (!entry_method) {
// 		fprintf(stderr, "Could not find entrypoint in assembly %s\n", assembly_name);
// 		exit(1);
// 	}

// 	MonoObject* out_exc;
// 	MonoObject* out_res;
// 	// Managed app will see: arg0: MainAssembly, arg1-.. [args]
// 	int ret = mono_runtime_run_main(entry_method, argc - arg_ofs, &argv[arg_ofs], &out_exc);
// 	if (out_exc)
// 	{
// 		mono_print_unhandled_exception(out_exc);
// 		exit(1);
// 	}
// 	return ret < 0 ? -ret : ret;
// }

// Function declaration at the top of your file
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
