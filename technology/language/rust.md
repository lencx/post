# Rust

## [Install](https://www.rust-lang.org/en-US/install.html)

```bash
# Linux or macOS
curl https://sh.rustup.rs -sSf | sh

# update and uninstall
rustup update
rustup self uninstall

# rust version
# rustc x.y.z (abcabcabc yyyy-mm-dd)
rustc --version

# doc
rustup doc
```

## Cargo

```bash
# cargo verison
cargo --version

# help information
# create a new cargo package at <path>
cargo new --help

cargo build

# building for release
cargo build --release

cargo run

cargo check
```