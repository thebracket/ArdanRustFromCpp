# Strings

Strings are an area of significant difference between C, C+ and Rust. None of them really agree on how strings really work.

## The Basic In-Memory String

Let's start with some C (that also works in C++):

```c
#include <stdio.h>

int main() {
    const char * my_string = "Hello, World";
    printf("%s\n", my_string);
    return 0;
}
```

* This prints "Hello, World!". 
* You are storing `my_string` as a `const char *`. It's set aside as an area of memory, containing 8-bit ASCII for each character---and a zero at the end.

Here's a Rust equivalent:

```rust
fn main() {
    let my_string = "Hello, World";
    println!("{my_string}");
}
```

Or if you want to use a constant, which always explicitly states the type:

```rust
fn main() {
    const MY_STRING: &str = "Hello, World";
    println!("{MY_STRING}");
}
```

What's up with `&str`? `str` is a type that means "a string of characters in memory". Unlike C, it isn't suffixed with a zero. It is *prefixed* with the string length.

## Let's Throw in Some Unicode!

```c
#include <stdio.h>

int main() {
    const char * my_string = "Hello, 🌎";
    printf("%s\n", my_string);
    return 0;
}
```

On reasonably recent GCC, this works. The compiler converts 🌎 to the appropriate UTF-8 - a series of bytes.

Rust works the same way:

```rust
fn main() {
    const MY_STRING: &str = "Hello, 🌎";
    println!("{MY_STRING}");
}
```

The only difference being that Rust's `char` type is *explicitly* UTF-8, not ASCII. When you operate on a collection of `char` types, they may range from 1 to 8 bytes! That makes handling control-points easier, but also means that strings aren't plain old 8-bit integers anymore.

## How about `std::string` in C++?

Many C++ programmers have moved towards using `std::string`---it's generally easier to work with, and less prone to foot-guns.

```cpp
#include <string>
#include <iostream>

int main() {
    std::string my_string = std::string("Hello, World!");
    std::cout << my_string << std::endl;
    return 0;
}
```

This also prints `Hello, World!`. Nothing too revolutionary there.

## String Concatenation

In C, you might combine two strings into a new string as follows:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[64] = "Hello ";
    const char * string2 = "World";

    strcat(buffer, string2);
    printf("%s", buffer);
    return 0;
}
```

> Make `buffer` too small and you are looking at a segmentation fault - or worse!

In C++, you can add some safety and do this:

```cpp
#include <string>
#include <iostream>

int main() {
    std::string my_string = std::string("Hello ");
    std::string buffer = my_string + std::string("World");
    std::cout << buffer << std::endl;
    return 0;
}
```

No segmentation faults here!

Here's a Rust equivalent:

```rust
fn main() {
    let mut buffer = String::from("Hello ");
    buffer += "World";
    println!("{buffer}");
}
```

## Two Types of String

Just like C++, Rust has two string types (and a few more we won't talk about until we cover FFI):
* `&str` - a reference to a collection of characters in memory. `&str` is immutable.
* `String` - a type holding a collection of characters. `String` can be mutated.

You can coerce a `String` into an `&str` by referencing it: `&my_string`.