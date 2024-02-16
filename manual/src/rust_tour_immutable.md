# Mutability

Coming from C and C++, the following is quite normal:

```c
#include <stdio.h>
int main() {
   int i = 5;
   i += 1;
   printf("%d\n", i);
   return 0;
}
```

However, this doesn't work in Rust (there is no `++` operator):

```rust
fn main() {
    let i = 5;
    i += 1;
    println!("{i}");
}
```

You get the compiler error `cannot assign twice to immutable variable i`. That's because `let` creates an *immutable* variable. It's the same as typing `const int i = 5;` in C or C++.

## Making a Mutable Variable

To mark a variable as mutable, you have to explicitly declare it as such:

```rust
fn main() {
    let mut i = 5;
    i += 1;
    println!("{i}");
}
```

So why wouldn't you define *everything* as mutable?
* Your program gains some clarity from the knowledge that a variable won't change.
* Functional-style programming tends to prefer not reusing variables.
* If you accidentally mutate a variable later, the compiler will stop you.

You *can* make everything `let mut`, and then use the linter (`cargo clippy` or your IDE) to highlight the variables that don't need it---but that's a crutch and should be avoided as you gain experience.

## Shadowing

You can also make use of *shadowing*. This is popular in many functional styles. It can also be confusing. I recommend adopting a style that suits you.

Take the following immutable code:

```rust
fn main() {
    let i = 5;
    let i_plus_one = i + 1;
    println!("{i}");
}
```

Your variables are immutable, and you are making it clear what's going on in your algorithm by naming each subsequent step. That's great until you get to a *big* algorithm and start running into `i_log10_times_3`... so you'll often find that "shadowing" is used to remove previous editions of a variable name from circulation as the calculation progresses:

```rust
fn main() {
    let i = 5;
    let i = i + 1;
    println!("{i}");
}
```

Shadowing is useful with scope (which we'll talk about in a moment). Within a scope, you can shadow a parent-scope's variable names---and get them back at the end of the scope. For example:

```rust
fn main() {
    let i = 5;
    {
        let i = i + 1;
        println!("{i}");
    }
    println!("{i}");
}
```