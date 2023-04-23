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
    depfiles_gcc = "main.o: example/main.cpp\
",
    files = {
        "example/main.cpp"
    }
}