# Box - Unique Pointer

C++ has the wonderful `unique_ptr` type. You heap-allocate a `unique_ptr`, it wraps its contents---and is automatically deleted when the pointer leaves scope. Rust has a type called `Box` that does the same thing.

```rust
struct MyStruct {
    n: i32,
}

fn main() {
    let boxed = Box::new(MyStruct { n: 12 });
}
```

The Rust `Box` type includes a huge number of options. These range from pinning memory in place (so it can't be rearranged) to building `from_raw_parts` to wrap an existing pointer in a Box.