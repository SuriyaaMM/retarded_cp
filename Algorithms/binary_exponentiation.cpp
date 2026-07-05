#include <limits>

namespace std2 {
/*
implementation of binary exponentiation using modular arithmetic
@note
    - mod should never be 1, in that case doesn't give the correct answer,
    callee's responsibility to make sure base, exp and mod are valid &
    makes sense
    - result must fit in __T_Accumulator, otherwise overflow error might
    be raised and is not handled by the function to be extremely fast
    - complexity O(log2(__T))
    - additionally the function is overloaded with a version that
    doesn't require mod as input (saves modulo cycles)
*/
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
template <typename __T, typename __T_Accumulator> [[nodiscard]]
inline __T_Accumulator binary_exponentiate(__T base, __T exp) {
    __T_Accumulator result = 1;
    for (__T_Accumulator basew = base; exp > 0; basew *= basew, exp >>= 1) {
        if ((exp & 1) == 1) result *= basew;
    }
    return result;
}
} // namespace std2