# Loops

Looping through data is pretty fundamental, so it shouldn't be a surprise that Rust supports loops.

## For Loops

Take the following C code:

```c
#include <stdio.h>

int main() {
    int i;
    for (i = 0; i < 10; i++) {
        printf("%d\n", i);
    }
    return 0;
}
```

Unsurprisingly: this prints `0` through `9`.

Here's a Rust equivalent:

```rust
fn main() {
    for i in 0..10 {
        println!("{i}");
    }
}
```

The output is the same, but the syntax is quite different:

* `0..10` is an *exclusive range*. It provides an *iterator* over every number in the range, exclusing the last one. We'll worry about iterators later.
* `i` only exists inside the loop scope. (In C++ and later C editions you can do `for (int i=0; i<10; i++)` for the same effect).
* You don't have any control over the operation that occurs for each iteration. Rust just ticks through each entry in the range.

If you prefer an inclusive range:

```rust
fn main() {
    for i in 0 ..= 10 {
        println!("{i}");
    }
}
```

> We'll look at `for_each` equivalency later.

## While Loops

This C should look familiar, too:

```c
#include <stdio.h>

int main() {
    int i = 0;
    while (i < 10) {
        printf("%d\n", i);
        i += 1;
    }
    return 0;
}
```

Equivalent Rust code looks like this:

```rust
fn main() {
    let mut i = 0;
    while i < 10 {
        println!("{i}");
        i += 1;
    }
}
```

> Sadly, Rust doesn't protect you from an infinite while loop either!

## `loop` loops

Rust adds one more type of loop, named `loop`. `loop` runs forever, or until a `break` statement is hit.

```rust
fn main() {
    let mut i = 0;
    loop {
        println!("{i}");
        i += 1;
        if i > 9 {
            break;
        }
    }
}
```