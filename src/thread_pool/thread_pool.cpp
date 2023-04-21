#include "koioslib/thread_pool/thread_pool.hpp"

namespace wilson {

easy_thread_pool::easy_thread_pool(size_t counts) {
        for (size_t i = 0; i < counts; ++i) {
                workers_.emplace_back([this]{ worker(); });
        }
}

easy_thread_pool::~easy_thread_pool()
{
        stop();
}

void easy_thread_pool::stop() noexcept
{
        ::std::lock_guard lk{ mut_ };
        stop_requested_ = true;
        cond_.notify_all();
}

void easy_thread_pool::stop_immediately() noexcept
{
        ::std::lock_guard lk{ mut_ };
        tasks_ = ::std::queue<::std::function<void()>>{};
        stop_requested_ = true;
        cond_.notify_all();
}

void easy_thread_pool::worker() noexcept {
        while (true) {
                ::std::unique_lock lk{ mut_ };
                cond_.wait(lk, [this]{ 
                        return stop_requested_ || !tasks_.empty(); 
                });
                if (stop_requested_ && tasks_.empty())
                        return;
                ::std::function<void()> task = ::std::move(tasks_.front());
                tasks_.pop();
                lk.unlock();
                try { task(); } catch (...) {}
        }
}

void easy_thread_pool::join() noexcept
{
        for (auto& thr : workers_) {
                thr.join();
        }
}

} // namespace wilson
