#ifndef KOIOS_TASK_CONCEPTS
#define KOIOS_TASK_CONCEPTS

#include <coroutine>
#include <concepts>
#include <utility>

namespace wilson {

template<typename A>
concept awaitable_concept = requires(A a) {
        { a.await_ready() } -> ::std::same_as<bool>;
        { a.await_resume() };
        { a.await_suspend(::std::declval<::std::coroutine_handle<>>()) };
};
        
}

#endif // KOIOS_TASK_CONCEPTS
