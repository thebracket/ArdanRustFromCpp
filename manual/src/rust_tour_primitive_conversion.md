# Primitive Type Conversion

Take the following C program:

```c
#include <stdio.h>

int main() {
   int i = 500;
   char c = i;
   printf("%d\n", c);
   return 0;
}
```

It compiles with no warnings, and outputs... `-12`. C lets you implicitly convert between types---even when doing so loses data.

An equivalent Rust program won't compile:

```rust
fn main() {
    let i: i32 = 500;
    let c: i8 = i;
    println!("{c}");
}
```

Just in case you thought Rust was just protecting you against an overflow, this won't compile either:

```rust
fn main() {
    let i: i32 = 500;
    let j: i64 = i;
    println!("{j}");
}
```

> Rust is *really* explicit about types and type conversion. You can almost never implicitly convert types. That's a good thing for avoiding bugs: it requires that you acknowledge that there is a type mismatch and explicitly handle it.

## Brute Force Conversion with `as`

The lowest level (and most dangerous) form of conversion in Rust is the `as` keyword. You can tell Rust that you accept that a conversion is potentially dangerous, and to do it anyway:

```rust
fn main() {
    let i: i32 = 500;
    let c: i8 = i as i8;
    println!("{c}");
}
```

This also prints out `-12`---so you have bug compatibility! You also generally don't want to do this unless you are absolutely, positively sure that doing so is safe.

It's always safe to up-convert---you can be sure that the larger type of the same size will be able to hold your data:

```rust
fn main() {
    let i: i32 = 500;
    let i: i64 = i as i64;
    println!("{i}");
}
```

Mixing signed and unsigned, or converting to a smaller type is potentially dangerous. (There's been regular discussion in the Rust world about whether `as` should sometimes be `unsafe`).

## Safe Conversion with `into`

Safe conversions between primitives are implemented with the `into()` function (itself part of the `Into` trait---traits are a much later topic). The compiler error messages earlier even suggested using it. Converting with `into` is simple:

```rust
fn main() {
    let i: i32 = 500;
    let i: i64 = i.into();
    println!("{i}");
}
```

`into` isn't implemented for the potentially unsafe conversions. This won't compile:

```rust
fn main() {
    let i: i64 = 500;
    let i: i32 = i.into();
    println!("{i}");
}
```

## Fallible Conversion with `try_into`

Some conversions are possible, but may or may not work. This will work:

```rust
use std::convert::TryInto;

fn main() {
    let i: i64 = 500;
    let i: i32 = i.try_into().unwrap();
    println!("{i}");
}
```

And this will compile but crash at runtime:

```rust
use std::convert::TryInto;

fn main() {
    let i: i64 = 2_147_483_648;
    let i: i32 = i.try_into().unwrap();
    println!("{i}");
}
```

So what's going on with the `unwrap`? `try_into` returns a `Result` type. We'll talk a lot about how they work internally later. A `Result` is a Rust enumeration (which are a lot like tagged unions in C or C++) that *either* contains `Ok(..)` or `Err(..)` - where the `..` are a generic type. `unwrap()` says "give me the value of Ok(x), or crash if it wasn't ok".

Obviously, crashing isn't a great choice---but we'll leave it there for now. Crashing *is* a better choice than corrupting your company's data because of a type conversion!