## .NET Function Import Repro

When trying to import C functions, it seems like there is a certain threshold that causes problems when it's hit. The size depends both on parameter types and return type. For example, this works:

```
IMPORT("env", "do_something") extern int64_t do_something(int32_t);
```

Output:
```
Mo in D:\dylibso\Int64Repro\host on main ● ~4 λ dotnet run
Input: 5
```

But this doesn't work (notice the parameter is also 64 bit now):
```
IMPORT("env", "do_something") extern int64_t do_something(int64_t);
```

Output:
```
Mo in D:\dylibso\Int64Repro\host on main ● ~3 λ dotnet run
../plugin/bin/Debug/net7.0/Int64Repro.wasm
Unhandled exception. Extism.Sdk.Native.ExtismException: error while executing at wasm backtrace:
    0: 0x405605 - <unknown>!<wasm function 7673>
    1: 0x403143 - <unknown>!<wasm function 7586>
    2: 0x405ad0 - <unknown>!<wasm function 7682>
    3: 0xe1c36 - <unknown>!<wasm function 699>
    4: 0x2d0b5a - <unknown>!<wasm function 4847>
    5: 0x3f5839 - <unknown>!<wasm function 7289>
    6: 0x3f56e5 - <unknown>!<wasm function 7287>
    7: 0x3f55ae - <unknown>!<wasm function 7286>
    8: 0x3f58b8 - <unknown>!<wasm function 7290>
    9: 0x3a26ad - <unknown>!<wasm function 6652>
   10: 0xbc1fa - <unknown>!<wasm function 397>
   11: 0x660dd - <unknown>!<wasm function 323>
   12: 0x61af2 - <unknown>!<wasm function 322>
   13: 0x365523 - <unknown>!<wasm function 6277>
   14: 0x20f187 - <unknown>!<wasm function 3058>
   15: 0x210e70 - <unknown>!<wasm function 3074>
   16: 0x21a4d8 - <unknown>!<wasm function 3160>
   17: 0xe1e05 - <unknown>!<wasm function 701>
   18: 0xe202a - <unknown>!<wasm function 702>
   19: 0x3408 - <unknown>!<wasm function 39>
   20: 0x32e7 - <unknown>!<wasm function 36>
   21: 0x417269 - <unknown>!<wasm function 7885>

Caused by:
    Exited with i32 exit status 1
   at Extism.Sdk.Native.Plugin.CallFunction(String functionName, ReadOnlySpan`1 data)
   at Program.<Main>$(String[] args) in D:\dylibso\Int64Repro\host\Program.cs:line 35
```

This doesn't work, but it's even more starnge:
```
IMPORT("env", "do_something") extern int32_t do_something(int32_t, int32_t, int32_t, int32_t, int32_t);
```

Output:
```
Mo in D:\dylibso\Int64Repro\host on main ● ~3 λ dotnet run
../plugin/bin/Debug/net7.0/Int64Repro.wasm
Fatal error. System.AccessViolationException: Attempted to read or write protected memory. This is often an indication that other memory is corrupt.
Repeat 2 times:
--------------------------------
   at Extism.Sdk.Native.LibExtism.extism_function_new(System.String, Extism.Sdk.Native.ExtismValType*, Int64, Extism.Sdk.Native.ExtismValType*, Int64, InternalExtismFunction, IntPtr, IntPtr)
--------------------------------
   at Extism.Sdk.HostFunction..ctor(System.String, System.String, System.Span`1<Extism.Sdk.Native.ExtismValType>, System.Span`1<Extism.Sdk.Native.ExtismValType>, IntPtr, Extism.Sdk.ExtismFunction)
   at Program.<Main>$(System.String[])
```

Interesting files:
 - Plugin:
   - native.c
   - Program.c

 - Host:
   - Program.c