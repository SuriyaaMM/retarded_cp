#![warn(non_camel_case_types)]
use std::vec;

use proconio::input;

type pair_t = (i64, i64);
type graph_t = Vec<Vec<i64>>;
type wgraph_t = Vec<Vec<pair_t>>;

fn solve() {}

fn main() -> std::io::Result<()> {
    unsafe {
        std::env::set_var("RUST_BACKTRACE", "1");
    }
    solve();
    Ok(())
}
