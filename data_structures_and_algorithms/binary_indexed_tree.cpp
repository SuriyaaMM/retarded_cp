#include <vector>

/*
implementation of binary_indexed_tree (aka fenwick tree)
@note
    - implementation always cares about inclusive ranges that is
    prefix(std::size_t i) will return answer from [1 ... i] inclusive
    similarly for between(std::size_t r, std::size_t l)
    - absolutely no boundary points will be checked, callee responsibility
    to check any out of index queries (this keeps the tree extremely fast)
    - all the functions are inlined (they're simple for loops)
    - accumulator will not be promoted to bigger type, you have to
    custom invoke it using the required template you want for the accumulator.
    also nothing will be checked for the += and + operator overloads of the
    accumulator type, it is once again callers responsibility to get things
    set up.
*/
template <typename __T, typename __T_Accumulator> struct binary_indexed_tree {
    std::size_t __n;
    std::vector<__T> __tree;

  private:
    [[nodiscard]]
    static inline constexpr std::size_t __remove_lmsb(std::size_t i) noexcept {
        return i - (i & -i);
    }
    [[nodiscard]]
    static inline constexpr std::size_t
    __propagate_lmsb(std::size_t i) noexcept {
        return i + (i & -i);
    }

  public:
    binary_indexed_tree(const std::size_t n) : __n(n), __tree(n + 1, 0) {}

    inline const __T_Accumulator prefix(std::size_t i) const noexcept {
        __T_Accumulator __accumulator = 0;
        for (; i != 0; i = __remove_lmsb(i)) __accumulator += __tree[i];
        return __accumulator;
    }
    inline void update(std::size_t i, const __T &value) noexcept {
        for (; i <= __n; i = __propagate_lmsb(i)) __tree[i] += value;
    }
    inline const __T_Accumulator between(std::size_t l,
                                         std::size_t r) const noexcept {
        return prefix(r) - prefix(l - 1);
    }
};
