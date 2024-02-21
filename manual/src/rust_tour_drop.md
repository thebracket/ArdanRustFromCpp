# Destructors - Drop

Rust doesn't explicitly define destructors---there's no need to define a destructor in most cases. So you won't encounter `~MyClass()` functions.

That doesn't mean that Rust has abandoned RAII---Resource Acquisition is Initialiation. Rather, Rust has adopted it wholesale and associated destructors with a trait called `Drop`.

`Drop` is implemented for all of the container types, smart pointers, etc. Whenever a variable leaves scope, the `Drop` trait is called prior to a type being deleted. Let's explicitly implement `Drop` to demonstrate this:

```rust
struct MyStruct {}

impl Drop for MyStruct {
    fn drop(&mut self) {
        println!("I was dropped");
    }
}

fn main() {
    let a= MyStruct{};
}
```

Not too surprisingly---the drop function runs at the end of the program. This applies to local variables in a function, too:

```rust
struct MyStruct {}

impl Drop for MyStruct {
    fn drop(&mut self) {
        println!("I was dropped");
    }
}

fn do_something() {
    let a = MyStruct{};
}

fn main() {
    println!("Calling function");
    do_something();
    println!("Returned");
}
```

Dropping works on variables held by a structure even if the structure doesn't itself explicitly implement `Drop`:

```rust
struct MyContainer { data: Vec<MyStruct> }

struct MyStruct {}

impl Drop for MyStruct {
    fn drop(&mut self) {
        println!("I was dropped");
    }
}

fn main() {
    let mc = MyContainer {
        data: vec![MyStruct{}, MyStruct{}, MyStruct{}]
    };
}
```

So---just like C++---RAII makes it very difficult to accidentally leak memory. We'll go over this in a lot more detail soon.

You can also explicitly drop anything:

```rust
struct MyContainer { data: Vec<MyStruct> }

struct MyStruct {}

impl Drop for MyStruct {
    fn drop(&mut self) {
        println!("I was dropped");
    }
}

fn main() {
    let mc = MyContainer {
        data: vec![MyStruct{}, MyStruct{}, MyStruct{}]
    };
    std::mem::drop(mc);
    // Accessing mc is now a compilation error
}
```