# Rc and Arc - Shared Pointer

Sometimes, ownership becomes confusing. Particularly if you are sending data off to be processed in more than one thread, you can end up with shared ownership---and exactly when something should be dropped from memory becomes confusing.

Rust has `Rc` (for "reference counted") as a wrapper type for this. (There's also `Arc` - atomic reference counted - for multi-threaded situations).

You can turn any variable into a reference-counted variable (on the *heap*) by wrapping it in `Rc`:

> This is in `projects/part2/refcount`

```rust
use std::rc::Rc;

struct MyStruct {}

impl Drop for MyStruct {
    fn drop(&mut self) {
        println!("Dropping");
    }
}

fn move_it(n: Rc<MyStruct>) {
    println!("Moved");
}

fn ref_it(n: &MyStruct) {
    // Do something
}

fn main() {
    let shared = Rc::new(MyStruct{});
    move_it(shared.clone());
    ref_it(&shared);
}
```

So we take a reference, move a clone (the `Rc` type is designed to have `clone()` called whenever you want a new shared pointer to the original)---and the data is only dropped once. It is shared between all the functions. You can use this to spread data widely between functions.

You can't *mutate* the contents of an `Rc` without some additional help.

Arc is the same thing, but it replaces the reference counter with an atomic---a guaranteed synchronized (and still very fast) thread-safe counter.

```rust
use std::sync::Arc;

struct MyStruct {}

impl Drop for MyStruct {
    fn drop(&mut self) {
        println!("Dropping");
    }
}

fn move_it(n: Arc<MyStruct>) {
    println!("Moved");
}

fn ref_it(n: &MyStruct) {
    // Do something
}

fn main() {
    let shared = Arc::new(MyStruct{});
    move_it(shared.clone());
    ref_it(&shared);
}
```