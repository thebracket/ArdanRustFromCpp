# Functions and Scopes

Functions are a mainstay of structured programming. C and C++ both support them:

```c
#include <stdio.h>

void print() {
    printf("Hello, World");
}

int main() {
    print();
}
```

Does exactly what you expect: it prints "Hello, World!". The equivalent Rust is similar:

```rust
fn print() {
    println!("Hello, World!");
}

fn main() {
    print();
}
```

## Returning Data from Functions

```c
#include <stdio.h>

int add_one(int i) {
    return i+1;
}

int main() {
    int x = add_one(5);
    printf("%d", x);
}
```

Here you are declaring a function named `add_one`, with the return type `int`. You accept a parameter named `i`, and return `i+1`.

The Rust syntax is quite different:

```rust
fn add_one(i: i32) -> i32 {
    i + 1
}

fn main() {
    let x = add_one(5);
    println!("{x}");
}
```

The syntax differences are quite obvious:
* The return type goes on the *end*, prefixed with `->`.
* Parameters are declared "name: type", rather than "type name".
* There's no `return` statement! By default, Rust functions always return the result of the last expression. In idiomatic Rust, you'll usually see functions declared in this way.

If you miss `return`, it's still there:

```rust
fn add_one(i: i32) -> i32 {
    return i + 1;
}

fn main() {
    let x = add_one(5);
    println!("{x}");
}
```

Notice that to use `return` you need to add a semicolon - but the first version didn't have one! Lines with a semicolon are still expressions---but they return the "unit type" (`()`). So you can *either* omit the semicolon to have the expression "fall out" of the function, or you can use `return` and a semicolon. That's a little confusing, so let's look at some underlying Rust.

In Rust, *everything* returns.

```rust
fn foo() {}

fn main() {
    let i = foo();
    println!("{i:?}");
}
```

> Notice we've used `:?`, the debug print again.

The program prints `()`. That's because `()` is like `void` - but it has a value (admittedly not a very useful one). So if you assign the result of a statement that ends in a `;`, you are setting it to the unit type---which is probably not what you wanted.

Rust also supports expression assignment:

```rust
fn main() {
    let i = 5;
    let i = if i < 5 {
            1
        } else {
            0
        };
    println!("{i}");
}
```

> Rust doesn't have a ternary operator!

You can assign from an expression or conditional just by returning using the no-semicolon syntax. This works for scopes, too:

```rust
fn main() {
    let i = {
        let mut accumulator = 0;
        for i in 0..10 {
            accumulator += i;
        }
        accumulator
    };
    println!("{i}");
}
```

> Note that you can't use the `return` keyword when you do this---`return` explicitly returns out of the current function.

How about if I want to return multiple potential values from a function?

You can either make sure that every branch implicitly returns:

```rust
fn test(i: i32) -> i32 {
    if i < 10 {
        0
    } else {
        1
    }
}

fn main() {
    println!("{}", test(5));
}
```

Or you can use early return:

```rust
fn test(i: i32) -> i32 {
    if i < 10 {
        return;
    }
    1
}

fn main() {
    println!("{}", test(5));
}
```