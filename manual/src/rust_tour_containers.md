# Containers

Rust implements a number of container types, similar to C++ standard library types.

## Arrays

An array in Rust can be declared as follows:

```rust
fn main() {
    let my_array = [1, 2, 3, 4]; // Type is inferred
    let my_array: [u32; 4] = [1, 2, 3, 4]; // Type specified
}
```

Just like C and C++, arrays are stored on the stack. Similar C++:

```cpp
#include <array>

int main() {
    int my_array[4] = {1, 2, 3, 4};
    std::array<int, 4> my_array_std = {1, 2, 3, 4};
    return 0;
}
```

Unlike C, Rust stores the length of the array and bounds-checks accesses. Accessing `my_array[5]` will panic, rather than exposing memory locations.

```c
#include <stdio.h>

int main() {
    int my_array[4] = {1, 2, 3, 4};
    printf("%d", my_array[5]);
    return 0;
}
```

Prints "32767" on my test system. The equivalent Rust fails to compile, but we can fool it by adding a little arithmetic:

```rust
fn main() {
    let array = [1, 2, 3, 4];
    for index in 2..6 {
        println!("{}", array[index]);
    }
}
```
This panics with the error message:

```
thread 'main' panicked at src/main.rs:4:24:
index out of bounds: the len is 4 but the index is 4
```

This is good, safe behavior. (A `get_unchecked` call exists, and requries an `unsafe` block, to elide the bounds checking).

## Vectors

C programmers sometimes complain that in Rust, everything looks like a vector. They aren't wrong: vectors are everywhere. C++ programmers tend to have vectors everywhere too!

A vector is like an array, but: it can grow, and it is stored on the heap. A C++ vector is typically a pointer to an area of heap memory, a notation about size and capacity, and a notation about the type stored inside. Rust vectors are *exactly* the same, including the same growth characteristics: when the capacity is exhausted, they double in size.

Let's add some data to a vector and debug-print it:

```rust
fn main() {
    let mut my_vec = Vec::new();
    my_vec.push(1);
    my_vec.push(2);
    println!("{my_vec:?}");
}
```

This is the same as the C++:

```cpp
#include <stdio.h>
#include <vector>

int main() {
    std::vector<int> my_vec;
    my_vec.push_back(1);
    my_vec.push_back(2);
    for (auto val : my_vec) {
        printf("%d", val);
    }
    return 0;
}
```

Rust is safe by default on bounds-checking:

```rust
fn main() {
    let my_vec = vec![1, 2]; // Helpful macro for initializing vectors
    println!("{}", my_vec[3]);
}
```

Panics with an out-of-bounds error. The direct-equivalent C++:

```cpp
#include <stdio.h>
#include <vector>

int main() {
    std::vector<int> my_vec;
    my_vec.push_back(1);
    my_vec.push_back(2);
    printf("%d", my_vec[3]);
    return 0;
}
```

Prints "0" and terminates normally on my system. (You can use `at` in C++ for a safe version; C++ typically defaults to unsafe, Rust to safe). Just like an array, `get_unchecked` is available for unsafe access (with an `unsafe` tag) if you really need to skip the bounds check.

If you need to pre-allocate a vector, you can use `with_capacity`:

```rust
fn main() {
    let mut my_vec = Vec::with_capacity(100);
    my_vec.push(1);
}
```

`with_capacity` generates an empty vector, but with pre-allocated capacity for the number of elements you want to store.

## HashMap

Rust also includes a `HashMap`. It doesn't offer any ordering guarantees, and is comparable to `std::unordered_map`. It implements "HashBrown" as the default hashing mechanism, which while fast is cryptographically safe---sometimes for performance people use `FxHash` instead.

```rust
use std::collections::HashMap;

fn main() {
    let mut my_map = HashMap::new();
    my_map.insert("Hello".to_string(), 5);
    my_map.insert("World".to_string(), 6);

    if let Some(count) = my_map.get("Hello") {
        println!("{count}");
    }
}
```

## Other Types

Rust implements many other containers:

* `VecDeque` - a vector that acts like a queue, similar to `deque` in C++.
* `LinkedList` - a premade linked-list type (writing linked lists in Rust is notoriously hard)
* `BTreeMap` - a binary tree map that retains order.
* `HashSet` - a direct equivalent to `unordered_set`.
* `BTreeSet` - a set implemented with a binary tree.
* `BinaryHeap` - a heap structure.

There are *many* more available through the crates infrastructure, which we'll cover when we get to dependencies.