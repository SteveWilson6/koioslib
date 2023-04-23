{
    files = {
        "build/.objs/koioslib-example/linux/x86_64/debug/example/main.cpp.o"
    },
    values = {
        "/usr/bin/g++",
        {
            "-m64",
            "-L/usr/lib",
            "-L/home/wilson/.xmake/packages/g/gtest/1.12.1/77b9096bc4b34d9282f672d36b015ba9/lib",
            "-Lbuild/linux/x86_64/debug",
            "-Wl,-rpath=$ORIGIN",
            "-lfmt",
            "-lgflags",
            "-lgmock",
            "-lgtest",
            "-lgtest_main",
            "-lkoioslib",
            "-lpthread"
        }
    }
}