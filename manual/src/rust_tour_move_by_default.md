# Move by Default

> Newcomers to Rust are always surprised by this one!

First, a quick C++ quiz. Do you really know what `std::move` does? When I've taught in person, there's a surprising amount of confusion. Does it create a copy? Can you use the value after you've moved out of it? It's not as clear as it could be.

`std::move` converts a type to an `xvalue`---a value that used to be valid, but may now have been plundered by the moved-to function. It's guaranteed to be valid, and it's undefined behavior to rely on its content. `my_function(std::move(x));` leaves `x` in a messy state.

Rust is *move* heavy---so much so that it is the *default* for all non-primitive types (which automatically get copied, since they fit in a register). In most languages, you'd expect this to compile:

```rust
fn do_something(s: String) {
    // Something happens here
}

fn main() {
    let s = "Hello".to_string();
    do_something(s);
    println!("{s}");
}
```

Instead of compiling, you get a pretty long error message summarized as `error[E0382]: borrow of moved value: s`. The full error does a great job of explaining what happened:

```
error[E0382]: borrow of moved value: `s`
 --> src/main.rs:8:15
  |
6 |     let s = "Hello".to_string();
  |         - move occurs because `s` has type `String`, which does not implement the `Copy` trait
7 |     do_something(s);
  |                  - value moved here
8 |     println!("{s}");
  |               ^^^ value borrowed here after move
  |
note: consider changing this parameter type in function `do_something` to borrow instead if owning the value isn't necessary
 --> src/main.rs:1:20
  |
1 | fn do_something(s: String) {
  |    ------------    ^^^^^^ this parameter takes ownership of the value
  |    |
  |    in this function
  = note: this error originates in the macro `$crate::format_args_nl` which comes from the expansion of the macro `println` (in Nightly builds, run with -Z macro-backtrace for more info)
help: consider cloning the value if the performance cost is acceptable
  |
7 |     do_something(s.clone());
  |                   ++++++++

```

The parameter `s: String` doesn't borrow or copy---it *moves* ownership to the function. The String now belongs to the function. It is dropped as soon as the function ends!

You *could* simply move it back (return value optimization guarantees from C++ apply to Rust, too):

```rust
fn do_something(s: String) -> String {
    // Something happens here
    s
}

fn main() {
    let s = "Hello".to_string();
    let s = do_something(s);
    println!("{s}");
}
```

That's fine if its the coding style you want, but it's not overly ergonomic. What you want to do is to *borrow* the data---make a reference. That's up next.