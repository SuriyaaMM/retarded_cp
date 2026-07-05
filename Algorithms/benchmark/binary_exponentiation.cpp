#include <bits/stdc++.h>
#include <chrono>
#include <cstddef>

volatile double sink = 0.0;

template <typename __T, typename __T_Accumulator> [[nodiscard]]
inline __T_Accumulator
binary_exponentiate(__T base, __T exp,
                    __T mod = std::numeric_limits<__T>::max()) {
    __T_Accumulator result = 1;
    for (__T_Accumulator basew = base % mod; exp > 0;
         basew = (basew * basew) % mod, exp >>= 1) {
        if ((exp & 1) == 1) result = (result * basew) % mod;
    }
    return result;
}

double benchmark_one(const std::size_t &__restrict__ base,
                     const std::size_t &__restrict__ exp) {
    auto timer_begin = std::chrono::high_resolution_clock::now();

    sink +=
        binary_exponentiate<size_t, size_t>(base, exp,
                                            static_cast<std::size_t>(1e9 + 7));

    auto timer_end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::micro>(timer_end - timer_begin)
        .count();
}

void print_statistics(std::vector<double> &__restrict__ elapsed_times,
                      std::string message) {

    double mean = 0.0;
    for (const auto &time : elapsed_times) mean += time;
    mean /= elapsed_times.size();

    double std = 0.0;
    for (const auto &time : elapsed_times) std += (time - mean) * (time - mean);
    std /= elapsed_times.size() - 1;

    std::ranges::sort(elapsed_times);

    std::cout << "=---------- " << message << " ----------=\n";
    std::cout << "average elapsed time = " << mean << " +- " << std << "us\n";
    std::cout << "median = " << elapsed_times[elapsed_times.size() / 2] << "us"
              << std::endl;
}

void benchmark() {
    constexpr const std::size_t shapes[] = {700000, 125000000, 250000000};

    constexpr const std::size_t n_runs = 4096, base = 17;

    for (const auto &shape : shapes) {
        std::vector<double> elapsed_times(n_runs, 0.0);
        for (std::size_t i = 0; i < n_runs; ++i) {
            elapsed_times[i] = benchmark_one(base, shape);
        }
        print_statistics(elapsed_times, "shape = " + std::to_string(shape));
    }
}

int main(int, char **) {

    benchmark();

    std::cout << "sink = " << sink << std::endl;

    return 0;
}