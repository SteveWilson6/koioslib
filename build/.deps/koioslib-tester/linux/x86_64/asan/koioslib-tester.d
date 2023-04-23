{
    files = {
        "build/.objs/koioslib-tester/linux/x86_64/asan/test/main.cpp.o"
    },
    values = {
        "/usr/bin/g++",
        {
            "-m64",
            "-L/usr/lib",
            "-Lbuild/linux/x86_64/asan",
            "-Wl,-rpath=$ORIGIN",
            "-lfmt",
            "-lgflags",
            "-lkoioslib"
        }
    }
}