add_rules("mode.debug", "mode.release")

add_requires("fmt", "gflags", "gtest")
add_packages("fmt", "gflags", "gtest")
set_languages("c++20")

target("koioslib")
    set_version("0.0.1")
    set_kind("shared")
    set_warnings("all", "error")
    add_cxflags("-Wconversion", { force = true })
    add_includedirs("includes", { public = true })
    add_files(
        "src/thread_pool/*.cpp"
    )
    set_toolchains("gcc")
    on_install(function (target)
        os.cp(target:targetfile(), "/usr/lib")
        os.cp("includes/*", "/usr/include/koioslib/")
        print("installed")
    end)

target("koioslib-unittest")
    set_kind("binary")
    add_files("test/*.cpp")
    add_deps("koioslib")
    add_includedirs("includes", { public = true })
    add_packages("gtest")
    set_toolchains("gcc")
    on_install(function (target)
        -- nothing
    end)
    after_build(function (target)
        print("☑️execute unit tests:☑️ ")
        os.exec(target:targetfile())
    end)
    on_run(function (target)
        -- nothing
    end)

target("example")
    set_kind("binary")
    add_cxflags("-Wconversion", { force = true })
    add_files("example/*.cpp")
    add_deps("koioslib")
    add_includedirs("includes")
    set_toolchains("gcc")
    on_install(function (target)
        -- nothing
    end)
    on_run(function (target)
        print("now execute example program!")
        print("⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️⬇️")
        os.exec(target:targetfile())
        print("⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️⬆️")
        print("example program exited!")
    end)

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

