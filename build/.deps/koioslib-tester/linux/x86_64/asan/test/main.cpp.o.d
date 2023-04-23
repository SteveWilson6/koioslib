{
    depfiles_gcc = "main.o: test/main.cpp includes/koioslib/thread_pool/thread_pool.hpp\
",
    files = {
        "test/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-std=c++20",
            "-Iincludes"
        }
    }
}