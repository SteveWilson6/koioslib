{
    files = {
        "src/thread_pool/thread_pool.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fPIC",
            "-Wall",
            "-Werror",
            "-std=c++20",
            "-Iincludes"
        }
    },
    depfiles_gcc = "thread_pool.o: src/thread_pool/thread_pool.cpp  includes/koioslib/thread_pool/thread_pool.hpp\
"
}