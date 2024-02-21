# Enumerations

In C and C++, enums are tied to a value:

```c
enum Level {
    Low, Medium, High
}
Level n = Low;
```

You can do the same thing in Rust:

```rust
enum Level {
    Low, Medium, High
}
let n = Level::Low;
```

C and C++ let you assign specific values to enumerations and cast them into numeric types:

```c
enum Level { Low=1, Medium=2, High=3 }
Level n = Medium;
int o = n;
```

Rust lets you do the same:

```rust
enum Level {
    Low = 1, Medium = 2, High = 3
}
let n = Level::Medium;
let o: u8 = n;
```

Rust lets you specify the underlying type for numeric Enums:

```rust
#[repr(u8)]
enum Level {
    Low = 1, Medium = 2, High = 3
}
let n = Level::Medium;
```

## Enumerations Can Contain Data

Rust enumerations can also contain data. They are effectively a tagged union, or variant. They will be the size of the largest possible member. The `match` command is the best way to access data within an enumeration.

```rust
enum Command {
    DoNothing,
    Count(i32), // A tuple-style enumeration entry
    Search{ term: String, max_depth: i32 }, // A structure-style enumeration entry
}

let c = Command:DoNothing;
let c = Command::Count(12);
let c = Command::Search { term: "term".to_string(), max_deptth: 12 };

match c {
    Command::DoNothing => {}
    Command::Count(n) => {
        for i in 0..n { println!("{n}") }
    }
    Command::Search{ term, max_depth } => {}
}
```

It's important to remember that an enumeration *only* contains data for the assigned value---it is equal to exactly one option.

Remember we've used `Option` and `Result`? They are enumerations, using generics.

## Option

Rust doesn't have `null` values (it does in FFI code, but not in "safe" Rust). Whenever a value may or may not be present, it is wrapped in an `Option`. Options are *generic* (we'll talk about that in the generics section)---it can contain pretty much anything. The declaration for `Option` looks like this:

```rust
enum Option<T> { None, Some(T) }
```

You've seen `unwrap()` (an associated function that returns the option's content or panics). You can also access an Option with a `match` statement:

```rust
match my_option {
    Some(x) => // Do something with x
    None => {}
}
```

The "if let" statement is a one-option `match`. You can use it to destructure an Option. It's often preferable, because there are only two possibilities:

```rust
if let Some(x) = my_option {
    // You can use x here
} else {
    // If you want to do something else
}
```

> `if let` is conditional upon destructuring succeeding. So `let x = Some(x)` is pattern matching. If it succeeded, then `if let` fires. You can also use `while let` to perform the comparison on an iterator.

## Result

`Result` is also an enumeration, indicating a fallible action. It's very similar to the new `std::expected` in C++. Rust's Results are:

```rust
enum Result<T, E> {
    Ok(T)
    Err(E)
}
```
They are *generic* (just like options), effectively templated in C++ parlance. When an operation may fail, it returns either `Ok(good_value)` or `Err(error type)`. We'll talk a lot more about this in Error Handling.

## Enumerations can have Associated Functions, too

You can use `impl` blocks with enumerations, too.

```rust
enum MyEnum { A, B }

impl MyEnum {
    fn new() -> Self { MyEnum::A } // A constructor
    fn print_me(&self) {
        match self {
            MyEnum::A => println!("The first option!"),
            MyEnum::B => println!("The second option!"),
        }
    }
}

fn main() {
    let e = MyEnum::new();
    e.print_me();
}
```