#include <iostream>
#include <thread>
#include <chrono>

using namespace ::std::chrono_literals;

int main()
{
        ::std::this_thread::sleep_for(3s);
        ::std::cout << "example app" << ::std::endl;
}
