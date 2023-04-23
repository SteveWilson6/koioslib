{
    files = {
        "test/main.cpp"
    },
    depfiles_gcc = "main.o: test/main.cpp\
",
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
    }
}