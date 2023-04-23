#include "koioslib/thread_pool/thread_pool.hpp"
#include "gtest/gtest.h"
#include "fmt/core.h"

#include <vector> // ::std::vector<::std::future<int>> 
#include <string_view>

using namespace ::std::string_view_literals;

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

class returned_val_passed_functor {
public:
        int operator()(foo f) const noexcept { return f.val(); }

        returned_val_passed_functor() = default;

        returned_val_passed_functor(returned_val_passed_functor&& f) noexcept {
                //fmt::print("returned_val_passed_functor moved\n"); 
        }

        returned_val_passed_functor(const returned_val_passed_functor& f) noexcept { 
                //fmt::print("returned_val_passed_functor copied\n"); 
        }
};

class nonreturned_val_passed_functor {
public:
        void operator()(foo f) const { 
                if (f.val() != success)
                        throw "test failed"sv;
        }

        nonreturned_val_passed_functor() = default;

        nonreturned_val_passed_functor(returned_val_passed_functor&& f) noexcept {
                //fmt::print("returned_val_passed_functor moved\n"); 
        }

        nonreturned_val_passed_functor(const returned_val_passed_functor& f) noexcept { 
                //fmt::print("returned_val_passed_functor copied\n"); 
        }
};

int regular_returned_ref_passed_func(foo& f) {
        return f.val();;
}

void regular_nonreturned_const_ref_passed_func(const foo& f) {
        if (f.val() != success)
                throw "test failed"sv;
}

TEST_F(thread_pool_test, enqueue_get_future_works) {
        foo f{};

        ASSERT_EQ(tp.enqueue_get_future(returned_val_passed_functor{}, foo{}).get()         , success);
        ASSERT_EQ(tp.enqueue_get_future(returned_val_passed_functor{}, f).get()             , success);
        ASSERT_EQ(tp.enqueue_get_future(regular_returned_ref_passed_func, f).get()          , success);
        ASSERT_EQ(tp.enqueue_get_future(returned_val_passed_functor{}, ::std::move(f)).get(), success);

        foo f2{};
        ASSERT_EQ(tp.enqueue_get_future([]{ return success; }).get()                   , success);
        ASSERT_EQ(tp.enqueue_get_future([f2]{ return f2.val(); }).get()                , success);
        ASSERT_EQ(tp.enqueue_get_future([&f2]{ return f2.val(); }).get()               , success);
        ASSERT_EQ(tp.enqueue_get_future([f = ::std::move(f2)]{ return f.val(); }).get(), success);
}

TEST_F(thread_pool_test, enqueue_works) {
        foo f{};

        ASSERT_NO_THROW(tp.enqueue(nonreturned_val_passed_functor{}, foo{})             );
        ASSERT_NO_THROW(tp.enqueue(nonreturned_val_passed_functor{}, f)                 );
        ASSERT_NO_THROW(tp.enqueue(regular_nonreturned_const_ref_passed_func, f)        );
        ASSERT_NO_THROW(tp.enqueue(nonreturned_val_passed_functor{}, ::std::move(f))    );

        ASSERT_NO_THROW(tp.enqueue([f] { if (f.val() != success) throw "test failed"sv; }));
        ASSERT_NO_THROW(tp.enqueue([&f] { if (f.val() != success) throw "test failed"sv; }));
        ASSERT_NO_THROW(tp.enqueue([f = ::std::move(f)] { if (f.val() != success) throw "test failed"sv; }));
}
