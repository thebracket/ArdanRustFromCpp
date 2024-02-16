# Numeric Overflow

Let's take a very simple C program:

```c
#include <stdio.h>

int main() {
   char a = 127;
   a = a + 1;
   printf("a = %d\n", a);
   return 0;
}
```

If you haven't been programming for a while, you may be surprised that the output is `-127`. Your 8-bit signed integer (`char`) can only hold -128 through 127, in binary two's complement. A binary addition of 1 to 127 gives `10000000`. Since the first digit in two's complemenet binary represents the sign bit---you get -127.

Rust's behavior for this program varies by how you compiled your program. In default `debug` mode:

```rust
fn main() {
    let mut a: i8 = 127;
    a += 1;
    println!("{a}");
}
```

Crashes the program with `attempt to add with overflow`. (If you compile in release mode with `cargo run --release`), it prints the wrapped number.

> Always test your builds in `debug`` mode!

## Explicitly Handling Wrapping

In C, you can detect this overflow with some additional code:

```c
#include <stdio.h>
#include <limits.h>

int main() {
   char a = 127;
   char add = 1;
   if (a > 0 && add > 0 && a > CHAR_MAX - add) {
      printf("Overflow detected\n");
      return 1;
   }
   a = a + add;
   printf("a = %d\n", a);
   return 0;
}
```

(You may also want to check for underflow)

Rust includes `checked_` arithmetic for this purpose:

```rust
fn main() {
    let a: i8 = 127;
    let a = a.checked_add(1);
    println!("{a:?}");
}
```

This prints `None`. That's odd! `checked_add` returns an `Option` type, which is fundamentally Rust's alternative to `null/nullptr`. Just like a `Result`, an `Option` is a sum type that can either be `None`, or `Some(x)`. 

> Notice that I snuck in `:?` in the print. This is "debug printing", and prints the contents of complicated types if they implement the appropriate trait.

You can also `unwrap` options:

```rust
fn main() {
    let a: i8 = 127;
    let a = a.checked_add(1).unwrap();
    println!("{a}");
}
```

## But I Want to Wrap!

Sometimes, wrapping is the desired behavior. It's used a lot in cryptographic functions, for example. Rust lets you *opt in* to the wrapping behavior:

```rust
fn main() {
    let a: i8 = 127;
    let a = a.wrapping_add(1);
    println!("{a}");
}
```

This won't crash on debug or release builds: you've explicitly told Rust (and whomever reads your code later) that wrapping was the *intended* behavior, and not a bug.

## Saturating

Maybe you'd rather saturate at the maximum possible value?

```rust
fn main() {
    let a: i8 = 127;
    let a = a.saturating_add(1);
    println!("{a}");
}
```

This prints `127`.

## Other Operations

Checked, saturating and wrapping variants of addition, subtraction, multiplication and division are all provided (division checking checks for divide by zero).

> If you are sensing a theme, it's that Rust picks *safe by default* when possible---and gives you the chance to opt out. C and C++ tend to assume you know what you're doing, and offer the option of adding safety checks.

