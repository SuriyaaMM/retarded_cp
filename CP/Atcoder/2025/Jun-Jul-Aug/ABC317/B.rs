use proconio::input;

fn solve() {
    input! {
        n: usize,
        mut a: [i64; n]
    }

    a.sort();
    for window in a.windows(2) {
        if window[1] != window[0] + 1 {
            println!("{}", window[0] + 1);
        }
    }
}

fn main() -> std::io::Result<()> {
    solve();
    Ok(())
}
