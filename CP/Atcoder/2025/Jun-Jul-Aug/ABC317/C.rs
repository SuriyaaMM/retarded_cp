#![warn(non_camel_case_types)]
use std::vec;

use proconio::input;

type pair_t = (i64, i64);
type graph_t = Vec<Vec<i64>>;
type wgraph_t = Vec<Vec<pair_t>>;

fn dfs(
    node: i64,
    weighted_sum: i64,
    graph: &wgraph_t,
    visited: &mut Vec<bool>,
    max_distance: &mut i64,
) {
    visited[node as usize] = true;
    *max_distance = (*max_distance).max(weighted_sum);
    for &(neighbour, w) in graph[node as usize].iter() {
        if !visited[neighbour as usize] {
            dfs(neighbour, weighted_sum + w, graph, visited, max_distance);
        }
    }
    visited[node as usize] = false;
}

fn solve() {
    input! {
        n: usize,
        m: usize,
        edges: [(usize, usize, i64); m]
    }
    // read the graph
    let mut graph: wgraph_t = vec![vec![]; n];
    for (u, v, w) in edges {
        let u = u - 1;
        let v = v - 1;
        graph[u].push((v as i64, w));
        graph[v].push((u as i64, w));
    }

    let mut max_distance: i64 = 0;
    let mut visited: Vec<bool> = vec![false; n];
    // we will perform dfs from each node making it O(n*n!)
    for i in 0..n {
        dfs(i as i64, 0, &graph, &mut visited, &mut max_distance);
    }

    println!("{}", max_distance);
}

fn main() -> std::io::Result<()> {
    // for debugging
    unsafe {
        std::env::set_var("RUST_BACKTRACE", "1");
    }
    solve();
    Ok(())
}
