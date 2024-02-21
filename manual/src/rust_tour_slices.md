# Slices

Slices are analagous to a C++ "view" type, or "span" type. They refer to a contiguous area of memory, usually inside a collection. You can use iterators on a span without needing to know the underlying details of the collection. For example:

```rust
fn sum(values: &[i32]) -> i32 {
    values.iter().sum()
}

fn main() {
    let my_vec = vec![1,2,3,4,5];
    println!("{}", sum(&my_vec));
}
```

Vectors and arrays decay into a slice when you borrow them. You can also use slices to look at just part of a collection of data:

```rust
fn sum(values: &[i32]) -> i32 {
    values.iter().sum()
}

fn main() {
    let my_vec = vec![1,2,3,4,5];
    println!("{}", sum(&my_vec[0..3]));
}
```