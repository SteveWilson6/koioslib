#ifndef KOIOS_THREAD_POOL_THREAD_POOL
#define KOIOS_THREAD_POOL_THREAD_POOL

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <type_traits>
#include <concepts>
#include <functional>
#include <memory>
#include <thread>
#include <future>

namespace wilson {

class easy_thread_pool {
public:
        explicit easy_thread_pool(size_t counts);
        ~easy_thread_pool();
        
        template<typename F, typename... Args>
                requires(::std::same_as<void, ::std::result_of_t<F(Args...)>>)
        void enqueue(F&& f, Args&&... args) {
                ::std::lock_guard lk{ mut_ };
                tasks_.emplace(
                [f = ::std::forward<F>(f), args... ] () mutable { 
                        f(args...);
                });
                
                cond_.notify_one();
        }

        template<typename F, typename... Args>
        auto enqueue_get_future(F&& f, Args&&... args) {
                using return_type = ::std::result_of_t<F(Args...)>;
                auto task_p = ::std::make_shared<::std::packaged_task<return_type()>>( 
                [f = ::std::forward<F>(f), args...] () mutable { 
                        return f(args...);
                });
                auto fut = task_p->get_future();

                ::std::unique_lock lk{ mut_ };
                tasks_.emplace([t = ::std::move(task_p)]{ (*t)(); });
                lk.unlock();
                cond_.notify_one();

                return fut;
        }

        void stop() noexcept;
        void stop_immediately() noexcept;
        void join() noexcept;
        void stop_and_join() noexcept { stop(); join(); }

private:
        void worker() noexcept;

private:
        ::std::mutex mut_;
        ::std::condition_variable cond_;
        ::std::queue<::std::function<void()>> tasks_;
        bool stop_requested_{ false };

        ::std::vector<::std::jthread> workers_;
};
using thread_pool = easy_thread_pool;

} // namesapce wilson

#endif // KOIOS_THREAD_POOL_THREAD_POOL
