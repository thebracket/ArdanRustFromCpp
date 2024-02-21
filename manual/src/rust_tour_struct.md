# Structures

In regular C, you are used to grouping data with `struct`s:

```c
#include <stdio.h>

struct mystruct_t {
    int a;
    int b;
};

int main() {
    struct mystruct_t value = {
        .a=1,
        .b=2
    };
    printf("%d, %d", value.a, value.b);
    return 0;
}
```

C++ is very similar, albeit with more assignment options:

```cpp
#include <iostream>

struct mystruct_t {
    int a;
    int b;
};

int main() {
    mystruct_t value = { 1, 2 };
    std::cout << value.a << ", " << value.b << std::endl;
    return 0;
}
```

Rust is similar, too:

```rust
struct MyStruct {
    a: i32,
    b: i32,
}

fn main() {
    let value = MyStruct {
        a: 1,
        b: 2,
    };
    println!("{}, {}", value.a, value.b);
}
```

Rust will let you use a shortcut to debug print, too:

```rust
#[derive(Debug)]
struct MyStruct {
    a: i32,
    b: i32,
}

fn main() {
    let value = MyStruct {
        a: 1,
        b: 2,
    };
    println!("{value:?}");
}
```

You can even "pretty print":

```rust
#[derive(Debug)]
struct MyStruct {
    a: i32,
    b: i32,
}

fn main() {
    let value = MyStruct {
        a: 1,
        b: 2,
    };
    println!("{value:#?}");
}
```

`#derive` is another type of macro. The compiler will iterate through the structure at compile time, generating a trait implementation of `fmt::Debug` for you (once again, we'll talk about traits later). It's not quite reflection, but it does a great job of faking it!

## Structure Privacy

In C++, `struct` defaults to all-public, while `class` defaults to all private. You can control individual members' privacy with `public` and `private` sections:

```cpp
struct MyStruct {
    uint32_t my_public;
private:
    uint32_t my_private;
}
```

Rust doesn't have classes, but all members default to being private unless you mark them as public with the `pub` or `pub(crate)` markers:

```rust
struct MyPrivateStruct {} // Structure is private to the module
pub struct MyPublicStruct {
    my_private: u32,
    pub my_public: u32,
    pub(crate) my_public_but_not_exported_from_the_crate: u32,
}
```

## Types of Structure

A "Marker Struct" (one you use to mark a type but that doesn't contain data) may be declared as:

```rust
struct MyMarker;

let s = MyMarker;
```

A regular structure with named fields:

```rust
struct Named {
    my_field: i32,
}

let s = Named { my_field: 3 };
println!("{}", s.my_field);
```

And a tuple-structure:

```rust
struct TupleStruct(i32);

let s = TupleStruct(3);
println!("{}", s.0)
```


