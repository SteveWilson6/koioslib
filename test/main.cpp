#include <iostream>
#include "koioslib/thread_pool/thread_pool.hpp"
#include <fmt/core.h>
#include <utility>

using namespace std;

const char* failure{ "failure" };

class foo
{
public:
        foo() = default;
        ~foo() { msg_ = failure; }
        foo(const foo& f) : msg_{ f.msg_ } {  ::std::cout << "copy" << ::std::endl; }
        foo(foo&& f) noexcept : msg_{ ::std::exchange(f.msg_, failure) } { ::std::cout << "move" << ::std::endl; }

        const char* val() const { return msg_; }

private:
        const char* msg_{ "ok" };
};

class func
{
public:
        func() = default;
        func(const func&) { ::std::cout << "copy func" << ::std::endl; }
        func(func&&) noexcept { ::std::cout << "move func" << ::std::endl; }
        void operator()(foo f)
        {
                ::std::cout << f.val() << ::std::endl;
        }
};


int main(int argc, char** argv)
{
        wilson::thread_pool tp{ 1 };
        tp.enqueue([]{});
}

