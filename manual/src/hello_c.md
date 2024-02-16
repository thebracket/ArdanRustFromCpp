# Hello World in C

Here's a hopefully familiar looking C version of "hello, world":

```c
#include <stdio.h>
int main() {
   printf("Hello, World!\n");
   return 0;
}
```

## Compilation

You can compile it with:

```bash
gcc -g -o hello hello_world.c
```

Or

```bash
clang -g -o hello hello_world.c
```

Or you can build a `Makefile`:

```makefile
CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: hello

hello: hello_world.c
	$(CC) $(CFLAGS) -o hello hello_world.c

clean veryclean:
	$(RM) hello
```

And type `make` to execute it.

All of these produce a binary, `hello` - which prints "Hello, World!".

## Takeaways

* The source code is short and to the point.
* You include `stdio.h` to pull in `printf`. This is a "copy paste"---the contents of `stdio.h` are included directly in your compilation.
* You either need to create a platform specific build script (specifying your compiler), or use a tool like `configure` (or `CMake`---which we'll talk about in C++).
* Compilation is *really* fast.
* It's not specified anywhere, but you are depending upon your platform's C standard library (`libc`, `glibc`, etc.). Your program is *dynamically linked* with it. You need to have `libc` installed to run your program.
