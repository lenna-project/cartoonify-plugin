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
npm run start
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

## python version

The plugin can build python bindings.

### build

Create a virtual environment for python.

```bash
virtualenv -p python3 .venv
source .venv/bin/activate
pip install .
```

### usage

Import lenna_cartoonify_plugin in a python environment.

```python
from PIL import Image
from numpy import asarray
import lenna_cartoonify_plugin
print(lenna_cartoonify_plugin.description())

image = Image.open('assets/cartoonify.png')
data = asarray(image)
print(data.shape)

config = lenna_cartoonify_plugin.default_config()
print(config)
processed = lenna_cartoonify_plugin.process(config, data)
print(processed.shape)
Image.fromarray(processed).save('lenna_test_out.png')
```

### test

Run the python [test file](src/test.py) which loads the [cartoonify.png](assets/cartoonify.png) and converts it.

```bash
pip install pillow
python src/test.py
```
