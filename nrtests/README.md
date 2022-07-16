# Non regressions tests

Non regression test of internal Eigen operations.

## Prerequisites

* A C++ compiller
* make

## How it works

To enable / disable some test you juste need to comments test include in `nrTestEigen.cpp`.

## Build and run

To build use / edit the Makefile.

You can build to your native platform with :

```bash
make
```

Ore you can build to a specific platform with :

```bash
make [mmx|sse|sse2|sse3|ssse3|sse4.1|sse4.2|avx|avx2|avx512]
```

To run you just need to execute the binary file.

```bash
./nrTestEigen
```
