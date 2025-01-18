## How to build
mkdir build; cd build
cmake .

## Commands used
1. pkg-config --libs protobuf
   1. This command should output the necessary linker flags (e.g., -lprotobuf -lprotoc). If it doesn't find the library, pkg-config will return an error.
2. pkg-config --cflags protobuf
   1. This command should output the necessary compiler flags (e.g., -I/usr/local/include). If it doesn't find the library, pkg-config will return an error.
3. brew info protobuf
4. When files in remote docker header is not resolves, use Tools > "Resync Remote Header Cache" in CLion
