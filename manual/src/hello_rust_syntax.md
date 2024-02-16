# Rust Syntax

```rust
fn main() {
    println!("Hello, World!");
}
```

I often argue that "Hello, World" is the worst Rust program to start with. `println!` is a *macro*, and doesn't look much like normal Rust code. (In fairness, `std::cout << "Hello, World!" << std::endl;` isn't very normal, either).

`println!` is a *macro*. Macros in Rust have a `!` at the end because they might be surprising: they are extensions to Rust's normal syntax.

So bear that in mind as we move forward.