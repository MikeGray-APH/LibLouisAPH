# LibLouisAPH

****************************************

## Introduction

LibLouisAPH is a re-factorization of [LibLouis](http://liblouis.org) that implements streaming control characters for better translation control for use in applications like [BrailleBlaster](http://www.aph.org/brailleblaster/).

LibLouisAPH is licensed under the [GNU LGPLv2.1+](https://www.gnu.org/licenses/lgpl-2.1.txt) (see the file COPYING.LESSER).  The command line tools are licensed under the [GNU GPLv3+](https://www.gnu.org/licenses/gpl.txt) (see the file COPYING).

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

You can build all at once with:
```
make dists
```

## Development

All source code files pertaining to the library are in the `source/` directory.  Source code specifically used for outputting internal structures and such are in the `source/output/` directory.

Source and data files for testing are in the `test` directory, and may be started with:

```
make test
```
or to compile test optimized and start:
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
make cleanse
```

****************************************
