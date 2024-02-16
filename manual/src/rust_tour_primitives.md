# Primitive Types

C is notoriously a little vague about type names:

```c
#include <stdio.h>

int main() {
    char c = 'a';
    unsigned char uc = 12;
    int i = 123;
    unsigned int ui = 123;
    short s = 123;
    unsigned short us = 123;
    long l = 123;
    unsigned long ul = 123;

    printf("%d    %ld\n", c, sizeof(c));
    printf("%d    %ld\n", uc, sizeof(uc));
    printf("%d    %ld\n", i, sizeof(i));
    printf("%d    %ld\n", ui, sizeof(ui));
    printf("%d    %ld\n", s, sizeof(s));
    printf("%d    %ld\n", us, sizeof(us));
    printf("%ld    %ld\n", l, sizeof(l));
    printf("%ld    %ld\n", ul, sizeof(ul));
    return 0;
}
```

The output will actually vary by platform. On my 64-bit Linux system I get:

```
97    1
12    1
123    4
123    4
123    2
123    2
123    8
123    8
```

Many C programmers prefer to be a bit more specific and use specifically sized types instead:

```c
#include <stdio.h>
#include <stdint.h>

int main() {
    int8_t c = 'a';
    uint8_t uc = 12;
    int32_t i = 123;
    uint32_t ui = 123;
    int16_t s = 123;
    uint16_t us = 123;
    int64_t l = 123;
    uint64_t ul = 123;

    printf("%d    %ld\n", c, sizeof(c));
    printf("%d    %ld\n", uc, sizeof(uc));
    printf("%d    %ld\n", i, sizeof(i));
    printf("%d    %ld\n", ui, sizeof(ui));
    printf("%d    %ld\n", s, sizeof(s));
    printf("%d    %ld\n", us, sizeof(us));
    printf("%ld    %ld\n", l, sizeof(l));
    printf("%ld    %ld\n", ul, sizeof(ul));
    return 0;
}
```

That's a bit more specific. If you're writing cross-platform code, it's often helpful to know exactly how large a variable is!

Additionally, `size_t` defines the "integral type"---an integer that matches the size of your platform. So on 64-bit Linux, `size_t` is 64-bits. On 32-bit Linux, it is 32-bits.

## Rust Primitive Types

Rust only defines the explicitly sized types (and `usize`/`isize` for the integral type):

```rust
use std::mem::size_of;

fn main() {
    let c: i8 = 97;
    let uc: u8 = 10;
    let i: i32 = 123;
    let ui: u32 = 123;
    let s: i16 = 123;
    let us: u16 = 123;
    let l: i64 = 123;
    let ul: u64 = 123;
    let vl: i128 = 123;
    let uvl: u128 = 123;
    let is: isize = 123;
    let us: usize = 123;
    let f: f32 = 123.4;
    let d: f64 = 123.4;

    println!("{c}, {}", size_of::<i8>());
    println!("{uc}, {}", size_of::<u8>());
    println!("{i}, {}", size_of::<i32>());
    println!("{ui}, {}", size_of::<u32>());
    println!("{s}, {}", size_of::<i16>());
    println!("{us}, {}", size_of::<u16>());
    println!("{l}, {}", size_of::<i64>());
    println!("{ul}, {}", size_of::<u64>());
    println!("{vl}, {}", size_of::<i128>());
    println!("{uvl}, {}", size_of::<u128>());
    println!("{is}, {}", size_of::<isize>());
    println!("{us}, {}", size_of::<usize>());
    println!("{f}, {}", size_of::<f32>());
    println!("{d}, {}", size_of::<f64>());
}
```

> We'll talk about the `use` in more detail later. You are importing a single function from the `std::mem` namespace. There's no copy/paste. You could also type `std::mem::size_of` every time.

Some takeaways:

* Each type is explicitly defined as `i<size>` or `u<size>`.
* Bytes (`u8/i8`) are not chars! We'll talk about `char` in a bit. They are special!
* `println!` can take variable names (but not complex expressions) in `{name}`, or  you can use `{}` as a placeholder and fill in the blanks as a parameter. `println!` defies Rust's normal syntax, which is why its a macro!

# Auto

C++ introduced `auto`. So you can do:

```cpp
auto i = 5;
```

That makes the compiler figure out what `i` is, based on its usages (or a default). Rust las the same thing, you don't *have* to specify a type at each declaration. This is perfectly valid (and easier to read/type):

```rust
fn main() {
    let n = 123;
}
```

Rust also supports suffixes for specifying type:

```rust
fn main() {
    let i = 123i32;
    let f = 123.4f32;
    let d = 123.4f64;
}
```