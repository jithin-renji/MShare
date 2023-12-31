# MShare
MShare aims to be a secure peer-to-peer messenger for macOS and Linux. It is currently a **WORK IN PROGRESS**.

## Build Instructions
You need the following to build and run MShare:
- C++ compiler with C++20 support (tested using clang++)
- CMake
- GNU Make/Ninja/any build system supported by CMake
- Crypto++

Make sure you have a suitable C++ compiler and CMake installed before you continue.

Clone the source code and change to the source directory:
```
$ git clone git@github.com:jithin-renji/MShare.git
$ cd MShare/
```

Download the latest version of [Crypto++](https://www.cryptopp.com/#download) and extract it to a folder called `cryptopp`.
```
$ unzip cryptoppVERSION.zip -d cryptopp
$ cd cryptopp/
```

Run `make` to build Crypto++. Optionally, add option `-jn` to speed up execution. For example, `-j8` would use 8 threads/cores.
```
$ make      # -j8
$ cd ..
```

Run `cmake` to generate build files for your platform.
```
$ cmake .
```

To build and run:
```
$ make      # -j8
$ ./mshared
```

See `./mshared --help` for more information.

## License
MShare is free software licensed under [GPLv3](https://www.gnu.org/licenses/gpl-3.0.html).

Copyright (C) 2023 Jithin Renji.
