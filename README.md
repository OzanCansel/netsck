<p align="center">
  <a href="https://github.com/OzanCansel/netsck/actions/workflows/cmake-gcc-ubuntu-1804.yml">
    <img src="https://github.com/OzanCansel/netsck/actions/workflows/cmake-gcc-ubuntu-1804.yml/badge.svg" alt="codacy"/>
  </a>
  
  <a href="https://github.com/OzanCansel/netsck/actions/workflows/cmake-gcc-ubuntu-2004.yml">
    <img src="https://github.com/OzanCansel/netsck/actions/workflows/cmake-gcc-ubuntu-2004.yml/badge.svg" alt="codacy"/>
  </a>
</p>

# netsck
`netsck` is a network utility tool which is developed to prototype or test network things. It provides a shell inside which runs javascript engine. Makes posible to create, bind, send data through or receive data from a socket. Current only `udp_socket` is implemented.

- It is a terminal application.

- Depends on `QtQml`, `QtNetwork` and `QtCore`.

- Qt 5.9.3 and greater

- GCC 7.3.1 and greater

- Currently tested only on Linux but should work for Windows too.

## How to build ?
### On Ubuntu 18.04 or 20.04

```bash
git clone https://github.com/OzanCansel/netsck.git
cd netsck
git submodule update --init
mkdir build && cd build
cmake ..
sudo cmake --build . --target install -- -j$(nproc)
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://raw.githubusercontent.com/OzanCansel/netsck/master/LICENSE)
