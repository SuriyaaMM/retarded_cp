#include <bits/stdc++.h>
#include <queue>


void solve() {
    std::int32_t h = 0, w = 0;
    std::cin >> h >> w;

    std::vector<std::vector<char>> grid(h, std::vector<char>(w, '.'));

    for (std::int32_t i = 0; i < h; ++i) {
        for (std::int32_t j = 0; j < w; ++j) {
            char sij = '0';
            std::cin >> sij;
            grid[i][j] = (sij == '#') ? '#' : '.';
        }
    }

    std::int32_t a = 0, b = 0, c = 0, d = 0;
    std::cin >> a >> b >> c >> d;


    std::vector<std::vector<std::int32_t>> f(h,
                                             std::vector<std::int32_t>(w, 1e9));

    std::array<std::int32_t, 4> dxx = {1, -1, 0, 0}, dyy = {0, 0, -1, 1};
    auto valid = [&](std::int32_t i, std::int32_t j) {
        return (i >= 0 && j >= 0 && i < h && j < w);
    };

    f[a - 1][b - 1] = 0;

    using t3 = std::tuple<std::int32_t, std::int32_t, std::int32_t>;

    std::priority_queue<t3, std::vector<t3>, std::greater<>> q;
    q.emplace(0, a - 1, b - 1);

    while (!q.empty()) {
        auto [kicks, i, j] = q.top();
        q.pop();

        for (std::int32_t k = 0; k < 4; ++k) {
            std::int32_t dx = i + dxx[k];
            std::int32_t dy = j + dyy[k];
            std::int32_t dxdx = i + 2 * dxx[k];
            std::int32_t dydy = j + 2 * dyy[k];

            if (valid(dx, dy)) {
                if (f[dx][dy] <= kicks) continue;
                if (grid[dx][dy] == '#') {
                    if (f[dx][dy] > kicks + 1) {
                        f[dx][dy] = kicks + 1;
                        q.emplace(kicks + 1, dx, dy);
                        q.emplace(kicks + 1, dxdx, dydy);
                    }
                } else {
                    if (f[dx][dy] > kicks + 1) {
                        f[dx][dy] = kicks + 1;
                        q.emplace(kicks + 1, dx, dy);
                        q.emplace(kicks + 1, dxdx, dydy);
                    }
                    if (f[dx][dy] > kicks) {
                        f[dx][dy] = kicks;
                        q.emplace(kicks, dx, dy);
                    }
                }
            }
        }
    }

    std::cout << f[c - 1][d - 1] << "\n";
}

int main(int, char **) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::int64_t t = 1;
    // std::cin >> t;
    while (t--) { solve(); }
    return 0;
}
