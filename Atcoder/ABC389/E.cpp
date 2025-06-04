// https://atcoder.jp/contests/abc389/tasks/abc389_e

#include <iostream>
#include <queue>
#include <vector>

struct product {

    size_t marginal_cost;
    size_t index;
    size_t units_bought;
    size_t price;

    product(size_t cost, size_t index, size_t units, size_t price)
        : marginal_cost(cost),
          index(index),
          units_bought(units),
          price(price) {}
};

struct compare_product {

    bool operator()(const product& left, const product& right) {
        return left.marginal_cost > right.marginal_cost;
    }
};

bool can_buy(size_t index, std::vector<size_t>& prices, size_t budget,
             size_t target_units) {

    std::priority_queue<product, std::vector<product>, compare_product> pq;

    for (size_t i = 0; i < prices.size(); ++i) {
        pq.push(product(prices[i], i, 0, prices[i]));
    }

    size_t total_cost = 0UL, units_bought = 0UL;

    while (units_bought < target_units && !pq.empty()) {

        product current = pq.top();
        pq.pop();

        total_cost += current.marginal_cost;
        ++units_bought;

        if (total_cost > budget)
            return false;

        size_t new_units = ++current.units_bought;
        size_t new_marginal_cost = (2UL * new_units + 1) * current.price;
        pq.push(product(new_marginal_cost, current.index, new_units,
                        current.price));
    }

    return total_cost <= budget;
}

size_t bs(size_t n, std::vector<size_t>& prices, size_t budget) {

    size_t left = 0UL, right = 2000UL;

    while (can_buy(n, prices, budget, right)) {
        right *= 2;
    }

    size_t answer = 0UL;

    while (left <= right) {

        size_t mid = left + (right - left) / 2;
        if (can_buy(n, prices, budget, mid)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return answer;
}

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, m = 0UL;
    std::cin >> n >> m;

    std::vector<size_t> p(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> p[i];
    }

    std::cout << bs(n, p, m) << std::endl;

    return 0;
}