using Extism.Sdk;
using Extism.Sdk.Native;

using System.Text;

var path = "../plugin/bin/Debug/net7.0/Int64Repro.wasm";

Console.WriteLine(path);
var bytes = File.ReadAllBytes(path);
var context = new Context();

// This doesn't work
var hf = new HostFunction("do_something", "env",  new ExtismValType[] { ExtismValType.I64 }, new ExtismValType[] { ExtismValType.I64 }, 0, DoSomething);

// This works
// var hf = new HostFunction("do_something", "env",  new ExtismValType[] { ExtismValType.I32 }, new ExtismValType[] { ExtismValType.I64 }, 0, DoSomething);

// This doesn't works
// var hf = new HostFunction("do_something", "env",  new ExtismValType[] { ExtismValType.I32, ExtismValType.I32 }, new ExtismValType[] { ExtismValType.I64 }, 0, DoSomething);

// This works
// var hf = new HostFunction("do_something", "env",  new ExtismValType[] { ExtismValType.I32, ExtismValType.I32 }, new ExtismValType[] { ExtismValType.I32 }, 0, DoSomething);

void DoSomething(CurrentPlugin plugin, Span<ExtismVal> inputs, Span<ExtismVal> outputs, nint userData)
{
   Console.WriteLine($"Input: {inputs[0].v.i32}");
   outputs[0].v.i64 = 1;
}

var plugin = context.CreatePlugin(bytes, new[] { hf }, withWasi: true);

_ = plugin.CallFunction("_start", Encoding.UTF8.GetBytes("Hello World!"));
