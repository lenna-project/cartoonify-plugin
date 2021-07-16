# cartoonify-plugin
Plugin to create a cartoon style.

## rust version

The plugin is nativaly developed in rust programming language.

### build

Build the plugin.

```bash
cargo build --release
```

The file target/release/liblenna_cartoonify_plugin.so can be copied to the plugins folder of

[lenna-cli](https://github.com/lenna-project/lenna-cli) and used in the pipeline.

## wasm and javascript version

The plugin can be compiled to wasm and used on [lenna.app](https://lenna.app).

### build

Build the wasm package.

```bash
wasm-pack build
```

The node module can be build then.

```bash
npm run build
```

### serve

The plugin can be hosted using

```bash

```

A server runs on localhost:3002 now.

On [lenna.app](https://lenna.app) on the left side the url http://localhost:3002 can be loaded to use the plugin.

## C++ version

The rust version can be linked into a c++ wrapper which can then be used as plugin for the desktop app [lenna](https://github.com/lenna-project/lenna)

### build

Create the folder build and change into it.
Run cmake and configure the path to [lenna](https://github.com/lenna-project/lenna).

```bash
mkdir build
cd build
cmake -Dlenna_DIR=../lenna ..
make
```

The file build/plugins/libcartoonify.so can be copied to the lenna plugins folder.
