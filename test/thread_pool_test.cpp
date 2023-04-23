#include "koioslib/thread_pool/thread_pool.hpp"
#include "gtest/gtest.h"
#include "fmt/core.h"

// ======== GTEST TEST CLASS ========

class thread_pool_test : public ::testing::Test {
protected:
        wilson::thread_pool tp{ 10 };
};

// ==================================

int success = 1;
int failure = 0;

class foo { 
public:
        foo() = default;
        foo(foo&& f) noexcept 
                : val_{ ::std::exchange(f.val_, failure) } 
        { 
                //fmt::print("foo moved\n"); 
        }

        foo(const foo& f) noexcept 
                : val_{ f.val_ } 
        { 
                //fmt::print("foo copied\n"); 
        }

        ~foo() { val_ = failure; }

        int val() const noexcept { return val_; }

private:
        int val_{ success };
};

class returned_ref_functor {
public:
        int operator()(foo f) const noexcept { return f.val(); }

        returned_ref_functor() = default;

        returned_ref_functor(returned_ref_functor&& f) noexcept {
                //fmt::print("returned_ref_functor moved\n"); 
        }

        returned_ref_functor(const returned_ref_functor& f) noexcept { 
                //fmt::print("returned_ref_functor copied\n"); 
        }
};

TEST_F(thread_pool_test, enqueue_works) {
        foo f{};
        ::std::future<int> f1, f2;
        ASSERT_NO_THROW(f1 = tp.enqueue_get_future(returned_ref_functor{}, foo{}));
        ASSERT_NO_THROW(f2 = tp.enqueue_get_future(returned_ref_functor{}, f));
        ASSERT_EQ(f1.get(), success);
        ASSERT_EQ(f2.get(), success);
}
