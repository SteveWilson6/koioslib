{
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-std=c++20",
            "-Iincludes",
            "-isystem",
            "/home/wilson/.xmake/packages/g/gtest/1.12.1/77b9096bc4b34d9282f672d36b015ba9/include"
        }
    },
    depfiles_gcc = "thread_pool_test.o: test/thread_pool_test.cpp  includes/koioslib/thread_pool/thread_pool.hpp\
",
    files = {
        "test/thread_pool_test.cpp"
    }
}