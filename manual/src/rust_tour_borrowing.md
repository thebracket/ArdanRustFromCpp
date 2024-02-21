# Borrowing

References in Rust are explicit at both the caller and the callee. Our simple "do something" example with a reference works:

```rust
fn do_something(s: &String) {
    // Something happens here
}

fn main() {
    let s = "Hello".to_string();
    do_something(&s);
    println!("{s}");
}
```

> Contrast this with C++ in which you don't specify the `&` on the caller. It's more typing, but you can't accidentally copy your data when the function signature changes.

If you want to allow the function to *change*/*mutate* the data, you need to *mutably borrow* it:

```rust
fn do_something(s: &mut String) {
    // Something happens here
    *s += " World";
}

fn main() {
    let mut s = "Hello".to_string();
    do_something(&mut s);
    println!("{s}");
}
```

Notice that this is even more pedantic: you have to make `s` mutable before it can be borrowed mutably. And then you have to *explicitly* mark the borrow `&mut`. There's no escaping it---Rust makes you specify your intent when you lend the data to another funciton.

## Borrowing Strings

Strings have a special case. A string contains a buffer of characters, and you can immutably refer to the characters as `&str`---a static string. So this also works:

```rust
fn do_something(s: &str) {
    // Something happens here
}

fn main() {
    let s = "Hello".to_string();
    do_something(&s);
    println!("{s}");
}
```

As we saw in the strings section, you can't modify an `str` buffer---but if all you need to do is print or use the string in a formatting expression (etc.), it can be quicker to just pass the reference.