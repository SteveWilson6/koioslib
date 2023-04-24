#ifndef KOIOSLIB_TASK_TASK
#define KOIOSLIB_TASK_TASK

#include <coroutine>
#include "koioslib/task/promises.hpp"
#include "koioslib/task/return_traits.hpp"

namespace wilson
{

template<typename Ret>
class task
{
public:
        using promise_type = promise<task, return_traits<Ret>>;

        constexpr bool await_ready() const noexcept { return false; }
        void await_suspend(::std::coroutine_handle<> h) noexcept {
                // TODO
        }

        Ret await_resume() noexcept {
                // TODO
        }

public:
        ~task() {
                h_.destroy();
        }

private:
        ::std::coroutine_handle<promise_type> h_;
};

}

#endif // KOIOSLIB_TASK_TASK
