{
    files = {
        "build/.objs/koioslib/linux/x86_64/asan/src/thread_pool/thread_pool.cpp.o"
    },
    values = {
        "/usr/bin/g++",
        {
            "-shared",
            "-m64",
            "-fPIC",
            "-L/usr/lib",
            "-lfmt",
            "-lgflags"
        }
    }
}