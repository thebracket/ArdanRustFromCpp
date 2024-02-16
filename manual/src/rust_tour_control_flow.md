# Control Flow

Rust offers similar control-flow options to C and C++.

## If Statements

In C or C++, you are probably used to:

```c
if (i == 5) {
    // Do something
} else {
    // Do something else
}
```

The Rust syntax is almost identical:

```rust
fn main() {
    let i = 6;
    if i == 5 {
        // Do something
        println!("5");
    } else {
        // Do something else
        println!("Other");
    }
}
```

## Switch Statements

You're probably also used to:

```c
int i = 5;
switch (i) {
    case 5: printf("5\n"); break;
    case 6: printf("6\n"); break;
    default: printf("Something else\n"); break; 
}
```

Rust's equivalent is called `match`, and is a little different:

```rust
fn main() {
    let i = 5;
    match i {
        5 => println!("5"),
        6 => println!("6"),
        _ => println!("Something else"),
    }
}
```

`match` can do a *lot* more than that, but let's focus on what we have here:

* There's no `break;`---matched cases do not fall through.
* The syntax is different: `(case) => (expression)`.
* `default` is replaced with `_` --- which is Rust's general "something else" symbol.

If you need multiple lines, it's similar to C also:

```rust
fn main() {
    let i = 5;
    match i {
        5 => {
            println!("5");
            println!("5 is a good number.");
        }
        6 => println!("6"),
        _ => println!("Something else"),
    }
}
```

> There's also a special "one case match" called "if let", but we're going to worry about that later.