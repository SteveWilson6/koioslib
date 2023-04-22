#ifndef KOIOS_UTILITY_DEFER
#define KOIOS_UTILITY_DEFER

/**
 *      This code which I copied from a group chat and
 *      could not refer the original source of this pretty cool idea.
 *      So, if any one found the original source, I'll appriciate for 
 *      telling me, or just make a PR to justify this announcement.
 */

struct defer_dummy{};
template<typename F> struct deferer{ F f; ~deferer() { f(); } };
template<typename F> deferer<F> operator*(defer_dummy, F f) { return { f }; }
#define DEFER_(LINE) zz_defer##LINE
#define DEFER(LINE) DEFER_(LINE)
#define defer auto DEFER(__LINE__) = defer_dummy{} * [&]()

#endif
