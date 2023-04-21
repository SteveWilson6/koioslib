#ifndef KOIOSLIB_TASK_TASK
#define KOIOSLIB_TASK_TASK

#include <coroutine>

namespace wilson
{

template<typename Ret>
class task
{
public:
private:
        struct promise_type
        {
        };

private:
        ::std::coroutine_handle<promise_type> h_;
};

}

#endif // KOIOSLIB_TASK_TASK
