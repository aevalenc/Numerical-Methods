# Numerical-Methods
A simple library for common numerical methods

# Usage
The idea is to depend on this library as an external library and directly use the methods defined in the various folders within the repository. Currently the source code is maintained with the bazel build system. CMake support is still ongoing.

# Building
There are a few provided toolchains within the `bazel/toolchains` directory for various platforms for the sake of semi-hermeticity. The `.bazelrc` file defines some configurations that you can use at your leisure. The supported configurations are:
- `clang18_macos_aarch64`: For macOS on Apple Silicon using Clang 18
- `gcc12_macos_x86_64`: For macOS on Apple Intel chips using GCC 12
- `gcc12_macos_aarch64`: For macOS on Apple Silicon using GCC 12
- `gcc12`: For Linux on x86_64 platforms using GCC 12
- `gcc9`: For Linux on x86_64 platforms using GCC 9
- `clang18`: For Linux on x86_64 platforms using GCC 9

MPI support is in progess, but first bite implementations at the toolchains are located in `bazel/toolchains/openmpi`. The configurations for OpenMPI are:
- `mpi_gcc9`: For Linux on x86_64 using GCC 9 with OpenMPI
- `mpi_macos_aarch64_clang17`: For macOS on Apple Silicon using Clang 17 with OpenMPI

Additionally CUDA support is in progress and initial setup is provided in the MODULE file.

# Testing
The library is tested using the bazel build system. The tests are located in `tests` directories. As an example you can run the tests using the following command on a linux x86_64 system with GCC 12: 
```bash
bazel test --config=gcc12 //...
```
