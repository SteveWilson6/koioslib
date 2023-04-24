#ifndef KOIOSLIB_TASK_RTEURN_TRAITS
#define KOIOSLIB_TASK_RTEURN_TRAITS

#include <type_traits>
#include <memory>

namespace wilson {

template<typename Ret>
requires(not ::std::is_reference_v<Ret>)
struct return_traits
{
        using store_type = ::std::remove_reference_t<Ret>*;
        using return_type = Ret;
        constexpr bool is_ref_v = true;
};

template<typename Ret>
requires(::std::is_reference_v<Ret>)
struct return_traits
{
        using store_type = ::std::unique_ptr<Ret>;
        using return_type = Ret;
        constexpr bool is_ref_v = false;
};

template<>
struct return_traits<void> {};

} // namespace wilson

#endif // KOIOSLIB_TASK_RTEURN_TRAITS
