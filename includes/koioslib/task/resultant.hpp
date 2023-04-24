#ifndef KOIOS_TASK_RESULTANT
#define KOIOS_TASK_RESULTANT

#include <coroutine>
#include <cassert>

#include "koioslib/task/return_traits.hpp"
#include "koioslib/task/return_policies.hpp"

namespace wilson {

struct resultant_base {
        ::std::coroutine_handle<> caller_;
};

template<typename RetT>
class resultant : protected resultant_base {
        using return_type = typename RetTraits::return_type;
        using store_type = typename RetTraits::store_type;
public:
        template<typename T>
        requires (
                ::std::convertible_to<T, return_type> and
                ::std::constructible_from<return_type, T>)
        void return_value(T&& v) {
                storage_ = return_policy<RetT>{}.set_value(::std::forward<T>(t));
                assert(caller_);
                // TODO notify suspended. By calling a async context func
        }

        // suspended will call this.
        decltype(auto) get_result() {
                return return_policy<RetT>{}.get_value(storage_);
        }

private:
        store_type storage_;
};

template<>
class resultant<return_traits<void>> : protected resultant_base {
public:
        void return_void() {
                assert(caller_);
                // TODO notify suspended. By calling a async context func
        }
};

} // namespace wilson

#endif // KOIOS_TASK_RETURN_VALUE_OR_NOTHING
