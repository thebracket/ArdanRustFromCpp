# Type Conversions

> If you see a lot of these error messages, it's a code smell. That is code that may not be such a great idea! Try to settle on types that are appropriate for what you are doing.

You actually have a few options for type conversion. 

#### Converting with `as`

The first is `as`:

```rust
fn double_it(n: i64) -> i32 {
    n as i32 * 2
}

fn main() {
    let i: i32 = 5;
    let j: i32 = double_it(i as i64);
    println!("i = {i}, j = {j}");
}
```

`as` works, but it is the *least safe* option. `as` does a direct conversion, ignoring any overflow, data-loss, or precision loss. It's always safe to go from `i32` to `i64`---you can't lose any data. Going from `i64` to `i32` may not be what you intended:

```rust
fn main() {
    let i: i64 = 2_147_483_648; // One more than i32 can hold
    let j = i as i32;
    println!("{j}");
}
```

You probably guessed that the result is `-2147483648`...

Takeaway: you can use `as` for safe conversions, it's not always the best idea.

#### Using `into`

The compiler error messages suggest using `into`. `into` is *only* provided for conversions where the type-conversion is safe and won't lose your data. We could use it like this:

```rust
fn double_it(n: i64) -> i32 {
    n as i32 * 2
}

fn main() {
    let i: i32 = 5;
    let j: i32 = double_it(i.into());
    println!("i = {i}, j = {j}");
}
```

This works, but we're still using `n as i32`. Why? `i64` to `i32` conversion can lose data---so Rust doesn't implement `into()`. Still, we're half way there.

#### Using `try_into`

For fallible conversions, Rust provides the `try_into` operation:

```rust
use std::convert::TryInto;

fn double_it(n: i64) -> i32 {
    let n: i32 = n.try_into().expect("{n} could not be converted safely into an i32");
    n * 2
}

fn main() {
    let i: i32 = 5;
    let j: i32 = double_it(i.into());
    println!("i = {i}, j = {j}");
}
```

`try_into` returns a `Result` type. We're going to go into those in detail later. For now, just think of it as equivalent to `std::expected`---it's either the expected result, or an error. You can use `unwrap()` to crash immediately on an error, or `expect` to crash with a nicer error message. There's lots of *good* ways to handle errors, too---but we'll get to that later.

Yes, that's a lot more pedantic. On the other hand, Rust makes you jump through a few hoops before you are confused by:

```c++
std::cout << double_it(2147483648) << std::endl;
```

> It outputs 0
