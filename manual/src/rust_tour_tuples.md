# Tuples & Destructuring

Tuples in Rust are a bit easier to use than their C++ cousins. In C++:

```cpp
std::tuple<std::string, double> tuple = {"Hello", 3.14};
let s = std::get<0>(tuple);
let n = std::get<1>(tuple);
```

In Rust, you can define a tuple with parentheses:

```rust
fn main() {
    let tuple = ( "Hello".to_string(), 3.14 );
    let n = tuple.1;
}
```

Rust also supports *destructuring*:

```rust
fn main() {
    let tuple = { "Hello".to_string(), 3.14 };
    let (name, value) = tuple;
}
```
