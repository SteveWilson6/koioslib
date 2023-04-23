{
    files = {
        "src/thread_pool/thread_pool.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fPIC",
            "-g",
            "-Wall",
            "-Werror",
            "-O0",
            "-std=c++20",
            "-Iincludes",
            "-isystem",
            "/home/wilson/.xmake/packages/g/gtest/1.12.1/77b9096bc4b34d9282f672d36b015ba9/include"
        }
    },
    depfiles_gcc = "thread_pool.o: src/thread_pool/thread_pool.cpp  includes/koioslib/thread_pool/thread_pool.hpp\
"
}