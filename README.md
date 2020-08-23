# minacalc-standalone
Standalone version of MinaCalc along with a C API for easy access and bindings

# How to build
MinaCalc requires C++17.

The following commands assume GCC and Linux. Adjust the commands to your platform of choice

1. Compile the source files:
    - `g++ -std=c++17 -O2 -static -c MinaCalc.cpp API.cpp`
    - If the C API is not needed, omit API.cpp: <br/>
      `g++ -std=c++17 -O2 -static -c MinaCalc.cpp`
2. Link the object files together into a library: `ar rcs libminacalc.a *.o`
