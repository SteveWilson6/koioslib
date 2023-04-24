#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <cstring>

int main()
{
        int* ip = (int*)::malloc(sizeof(int));
        ::memset(ip, 1, sizeof(int));

        int* rip = (int*)::realloc(ip, sizeof(int) * 2);

        ::std::cout << (void*)ip << ::std::endl;
        ::std::cout << (void*)rip << ::std::endl;
        
        
        free(ip);
}
