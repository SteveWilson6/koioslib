{
    files = {
        "build/.objs/koioslib/linux/x86_64/debug/src/thread_pool/thread_pool.cpp.o"
    },
    values = {
        "/usr/bin/g++",
        {
            "-shared",
            "-m64",
            "-fPIC",
            "-L/usr/lib",
            "-L/home/wilson/.xmake/packages/g/gtest/1.12.1/77b9096bc4b34d9282f672d36b015ba9/lib",
            "-lfmt",
            "-lgflags",
            "-lgmock",
            "-lgtest",
            "-lgtest_main",
            "-lpthread"
        }
    }
}