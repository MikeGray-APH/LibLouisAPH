# LibLouisAPH

****************************************

## Introduction

LibLouisAPH is a re-factorization of [LibLouis](http://liblouis.org) that implements streaming control characters for better translation control for use in applications like [BrailleBlaster](http://www.aph.org/brailleblaster/).

LibLouisAPH is licensed under the [Apache License, Version 2.0](http://www.apache.org/licenses/LICENSE-2.0) (see the file LICENSE-2.0.txt).

## Building

To build the libraries and tools for linux systems:
```
make dist-linux64
```
will place the libraries, executables, and tables in the `dists/x86_64-linux` directory.

To build the libraries and tools for linux 32-bit systems:
```
make dist-linux32
```
will place the libraries, executables, and tables in the `dists/i686-linux` directory.

To build the libraries and tools for windows systems using `MinGW`:
```
make dist-win64
```
```
make dist-win32
```
will place the libraries, executables, and tables in the `dists/x86_64-win` and `dists/i686-win` directories respectively.

To build the libraries and tools for apple systems using `osxcross`:
```
make dist-mac64
```
```
make dist-mac32
```
will place the libraries, executables, and tables in the `dists/x86_64-mac` and `dists/i386-mac` directories respectively.

## Development

All source code files pertaining to the library are in the `source/` directory.  Source code specifically used for outputting internal structures and such are in the `source/output/` directory.

Source and data files for testing are in the `test` directory, and may be started with:

```
make test
```
Additional tests may be run with:
```
make test-all
```
To compile and start certian tests optimized for benchmarking:
```
make test-opt
```
Addition code and data files used for development and debugging are in the `debug/` directory.  The file `debug/main-debug.c` contains a `main()` and utility functions and can be started with:

```
make db
```
See `debug/main.gdb` files for details.

To start testing through the debugger:
```
make test-db
```

Development version of the tools can be built with:

```
make tools
```
which will place the executables in the `build/tools/` directory.

To clean just the build:
```
make clean
```
or to clean the build and more:
```
make distclean
```

****************************************
