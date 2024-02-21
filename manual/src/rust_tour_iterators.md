# Iterators

Just like C++, Rust uses iterators to provide a rich set of algorithms---and many crates such as `IterTools` use this to build even more functionality.

For loops in Rust *are* iterators:

```rust
fn main() {
    // These are the same:
    let my_vec = vec![1,2,3,4];
    for n in my_vec {
        println!("{n}");
    }

    let my_vec = vec![1,2,3,4];
    for n in my_vec.into_iter() {
        println!("{n}");
    }
}
```

These are also *consuming* iterators - they don't return a reference to the item in the collection, they *move* it into the loop scope and it is dropped at the end of the scope. You can't use `my_vec` after iterating with a consuming iterator. To iterate references:

```rust
fn main() {
    // These are the same:
    let my_vec = vec![1,2,3,4];
    for n in &my_vec {
        println!("{n}");
    }

    //let my_vec = vec![1,2,3,4];
    // No need to recreate the vector now
    for n in my_vec.iter() {
        println!("{n}");
    }
}
```

If you prefer a more iterator-based approach, you can also do the following:

```rust
fn main() {
    let my_vec = vec![1,2,3,4];
    my_vec.iter().for_each(|n| println!("{n}"));
    // We pass in a closure
}
```

This is equivalent to the C++:

```cpp
#include <stdio.h>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4};
    std::for_each(v.begin(), v.end(), [](int const& elem) {
        printf("%d\n", elem);
    });
    return 0;
}
```

Iterators are frequently chained together (much like the new C++ Ranges system). For example:

```rust
fn main() {
    let my_vec = vec![1,2,3,4];

    // Create a vector or strings
    let my_new_vec: Vec<String> = my_vec
        .iter()
        .map(|n| n.to_string()) // Map converts each entry to another type
        .collect();

    let max = my_vec.iter().max();
    let min = my_vec.iter().min();
    let sum: u32 = my_vec.iter().sum();
    let count = my_vec.iter().count();

    let sum_with_fold = my_vec.iter().fold(0, |acc, x| acc + x);

    let all_the_numbers: Vec<(&u32, &String)> = my_vec.iter().zip(my_new_vec.iter()).collect();
    println!("{all_the_numbers:?}");

    my_vec
        .iter()
        .filter(|n| **n > 2) // Dereferencing because we have two layers of reference
        .for_each(|n| println!("{n}"));
}
```

In other words, most of the algorithms in C++ are implemented. There's a *lot* more on the Rust documentation site: [https://doc.rust-lang.org/std/iter/trait.Iterator.html#](https://doc.rust-lang.org/std/iter/trait.Iterator.html#)

We'll talk about parallel iteration later.