# Structure Functions

Functions can be attached to structures, as either methods or associated functions.

## Associated Functions

Associated functions use a structure as a *namespace*. They are similar to static C++ functions in a class/struct, in that they aren't associated with an instance of a structure---you use the structure as a namespace for accessing them.

Functions are associated with a structure in Rust with an `impl` block---an implementation block. Associated functions do *not* take a `self` parameter referring to an instance.

```rust
struct MyStruct {}

impl MyStruct {
    pub fn do_something() {
        // Function body
    }
}

fn main() {
    MyStruct::do_something();
}
```

Equivalent C++ looks like this:

```cpp
#include <stdio.h>
#include <stdlib.h>

class MyClass {
    public:
    
    static void do_something() {
        // Function body
    }
};

int main() {
    MyClass::do_something();
    return 0;
}
```

You can use associated functions as a constructor. Constructors aren't special, and you can define as many of them as you want---there's no rule of 3, 5, etc. A constructor is a convention---it's like any other associated function, and by convention it returns the an instance of the type that houses it. You can also refer to the current type with the syntax sugar `Self`:

```rust
struct MyStruct {
    value: i32,
};

impl MyStruct {
    fn new() -> MyStruct {
        Self { value: 3 }
    }

    fn with_param(value: i32) -> Self {
        // Syntax sugar: if you are assigning from a variable of the same name
        // and type, you don't need to write "value:value".
        Self { value }
    }
}
```

A similar C++ constructor would look like this:

```cpp
class MyClass {
    public:
    
    int value;
    
    MyClass(int n) {
        value = n;
    }
};

int main() {
    auto my_class = MyClass(3);
    return 0;
}
```

There's no such thing as a move constructor, copy constructor. There's also no "default constructor", but there's a trait that accomplishes the same thing. Here's the short version using a "derive" (a macro that writes code for you):

```rust
#[derive(Default, Debug)]
struct MyStruct {
    a: i32,
    b: String
}

fn main() {
    println!("{:?}", MyStruct::default());
}
```

You can also explicitly implement `Default`:

```rust
#[derive(Debug)]
struct MyStruct {
    a: i32,
    b: String
}

impl Default for MyStruct {
    fn default() -> Self {
        Self {
            a: 3,
            b: "Hello".into(),
        }
    }
}

fn main() {
    println!("{:?}", MyStruct::default());
}
```

## Methods

You can also define functions that operate on an *instance* of a structure, just like C++ methods. You annotate the access method of the function as the first parameter:

```rust
struct MyClass {
    a: i32
}

impl MyClass {
    fn print_me(&self) {
        println!("{}", self.a);
    }
}

fn main() {
    let mc = MyClass { a: 42 };
    mc.print_me();
}
```

This is equivalent to the C++:

```cpp
#include <stdio.h>
#include <iostream>

class MyClass {
    public:
    
    int value;
    
    MyClass(int n) {
        value = n;
    }
    
    void print_me() {
        std::cout << this->value << "\n";
    }
};

int main() {
    auto my_class = MyClass(3);
    my_class.print_me();
    return 0;
}
```

You can replace `&self` with different types of access to the instance:

* `&self` is most common. It provides a read-only (constant) reference that can access the instance but not change it.
* `&mut self` grants *mutable* access via a reference. Your method can change the instance's contents.
* `self` *moves* the instance into the function---it will be consumed if you don't return it. This is useful for "builder pattern" setups. We'll talk about that when we get to the Rust memory model.