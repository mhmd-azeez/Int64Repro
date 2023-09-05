package main

import (
	"context"
	"fmt"
	"os"

	extism "github.com/extism/go-sdk"
	"github.com/tetratelabs/wazero"
	"github.com/tetratelabs/wazero/api"
)

func main() {
	// set some input data to provide to the plugin module
	manifest := extism.Manifest{
		Wasm: []extism.Wasm{
			extism.WasmFile{
				Path: "../plugin/bin/Debug/net8.0/wasi-wasm/AppBundle/Int64Repro.wasm",
			},
		},
	}

	ctx := context.Background()
	config := extism.PluginConfig{
		EnableWasi:   true,
		ModuleConfig: wazero.NewModuleConfig().WithArgs("app.wasm").WithStdout(os.Stdout),
	}

	hf := extism.HostFunction{
		Name:      "do_something",
		Namespace: "native",
		Callback: func(ctx context.Context, p *extism.CurrentPlugin, userData interface{}, stack []uint64) {
			fmt.Printf("Hello from Go: %v\n", api.DecodeI32(stack[0]))
			stack[0] = stack[0] * 2
		},
		Params:   []byte{api.ValueTypeI64},
		Results:  []byte{api.ValueTypeI64},
		UserData: "user data",
	}

	plugin, err := extism.NewPlugin(ctx, manifest, config, []extism.HostFunction{hf})

	if err != nil {
		fmt.Printf("Failed to initialize plugin: %v\n", err)
		os.Exit(1)
	}

	exit, _, err := plugin.Call("_start", []byte{})
	if err != nil {
		fmt.Println(err)
		os.Exit(int(exit))
	}

	fmt.Println("Success!")
}
