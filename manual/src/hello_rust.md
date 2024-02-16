# Hello World in Rust

Here's "Hello World" in Rust:

```rust
fn main() {
    println!("Hello, World!");
}
```

You can actually run that from the Playground. To run it locally, you actually need a full Rust project. The easy way to make this project is to open a terminal and type:

```bash
cargo new hello_world
```

By default, this even auto-generates the body of the "hello, world" program!

`Cargo` is Rust's swiss-army knife tool. It's a build system, a dependency manager, wraps a linter, can run unit tests and benchmarks --- it's also extendable. In this case, we're asking `Cargo` to make us a new project named `hello_world`.

Cargo creates the following structure:

```bash
hello_world/
hello_world/src/
hello_world/src/main.rs
hello_world/Cargo.toml
hello_world/.git
hello_world/.gitignore
```

> If you don't want to create a Git project, add the flags `--vcs none`. If you are already inside a git project, it won't try and nest another one inside.

The `Cargo.toml` file represents the project *manifest*---outlining project metadata. It looks like this:

```toml
[package]
name = "hello_world"
version = "0.1.0"
edition = "2021"

# See more keys and their definitions at https://doc.rust-lang.org/cargo/reference/manifest.html

[dependencies]
```

* The `package` section represents meta-data about the "crate" itself (Rust packages things into crates, which are handled by Cargo).
    * `name` specifies the output name, and also the name by which the project is referenced if other projects link to it.
    * `version` is a semantic (major.minor.patch) version number.
    * `edition` specifies which *editition* of the Rust language the project uses. Every 3-4 years, a new edition is released. Previous editions continue to compile, and edition versions are the opportunity for the Rust Core teams to make changes to the base language. Things can/will be deprecated (and eventually removed), added, and syntax may change.
* `dependencies` can be ignored for now. If you depend on other packages, they are listed here. We'll talk about that later.

So how do we compile our program?

```bash
cd hello_world
cargo build
```

The executable is now in `hello_world/target/debug/hello_world` (with a `.exe` on the end if you are in Windows).

## Takeaways

* You didn't include anything! Well you did, but by default parts of the Rust standard library are automatically included in the current scope.
* Your binary was statically linked. The entire Rust standard library is in there! (That's why it's 4.3 Mb in a debug build on Linux, as opposed to 17k for C++ and C. It's quite large - 2-3 Mb - if you statically link the C or C++, too).
* You didn't need any tools outside of the Rust ecosystem. Cargo took care of it all, and installing with `rustup` gave you the entire package.
* Compilation was decently fast---you'd hope so for Hello World.

Let's talk a bit about syntax.