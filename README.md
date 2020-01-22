# awx-inventory
Reads easydcim to build awx inventory

### Build

```
mkdir build
cd build
conan install .. -s build_type=Release --install-folder=. --build missing
cmake ..
make
```

### Usage:

```c++

./awx_inventory 'API_KEY' '/api/v2/device?filters[metadata_real_value]=internal,managed,unmanaged&filters[metadata_key]=61' '/tmp/raw_data.json' 12000

```
