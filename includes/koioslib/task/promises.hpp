#ifndef KOIOS_TASK_PROMISES
#define KOIOS_TASK_PROMISES

#include <coroutine>
#include "koioslib/task/resultant.hpp"

namespace wilson {

class promise_base
{
public:
        constexpr ::std::suspend_always initial_suspend() const noexcept {
                return {};
        }
        constexpr ::std::suspend_never final_suspend() const noexcept { 
                return {};
        }
};

template<typename Task, typename RetTraits>
class promise : public promise_base, 
                public resultant<RetTraits>
{
public:
        void set_caller_coro_handler(::std::coroutine_handle<> h) {
                caller_ = h; // derived from grandpa class `resultant_base`
        }

public:
        Task get_return_object() noexcept {
                return { *this };
        }

        void unhandled_exception() const {
                throw;
        }
};

}

#endif // KOIOS_TASK_PROMISES
