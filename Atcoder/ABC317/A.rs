use proconio::input;

fn solve() {
    input! {
        n: usize,
        h: usize,
        x: usize,
        potions: [usize; n]
    }

    for (i, &potion) in potions.iter().enumerate() {
        if potion + h >= x {
            println!("{}", i + 1);
            return;
        }
    }
}

fn main() -> std::io::Result<()> {
    solve();
    Ok(())
}
