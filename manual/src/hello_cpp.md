# Hello World in C++

A "pure" C++ version (C++20; C++23 is adding `std::print()`) looks like this:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

> It's worth noting that a *lot* of C++ projects use `printf` anyway.

## Compilation

You can also build this from the command-line:

```bash
g++ -g -o hello hello.cpp
```

Or with Clang:

```bash
clang++ -g -o hello hello.cpp
```

## With CMake

You can build a Makefile, but a lot of modern C++ projects now use CMake. Here's the `CMakeLists.txt` file:

```cmake
cmake_minimum_required(VERSION 3.5)
project(HelloWorld)

add_executable(hello hello.cpp)
```

Your build process then becomes:

```bash
mkdir build
cd build
cmake ..
make
```

As long as you have `CMake` and a build system it recognizes (`Make`, `Ninja`, etc.) it will build your project.

## Takeaways

All of these produce a binary, hello - which prints "Hello, World!".

* You are including `<iostream>`. No `.h` required. It's still a copy/paste into your compiled source. (If you are lucky enough to have modules, that's not quite as true now).
* You are using C++'s "streams" `cout` to stream data to the console.
* You are dynamically linking to the C++ standard library, it just isn't stated.
* `CMake` has made it easier to determine what compilers and build systems to use---but it's still not automatic.
* Compilation is still pretty fast.