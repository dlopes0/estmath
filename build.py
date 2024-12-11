import sys
import os
import glob
import shutil

BUILD_TYPE    = None
COMPILER      = None
OPTIONS       = None
COMPILE_TESTS = None

if (len(sys.argv) == 2):
    print("estmath build.py v1.0")
    print("(C) David Lopes, 2024")
    print("")
    # Clean build if selected
    if (sys.argv[1] == "clean"):
        if os.path.exists("build"):
            shutil.rmtree("build")
            print("[OK] Cleaned build!")
            exit()
        else:
            print("[!!] No existing build found... Exiting...")
            exit()

    # Create folder if not exists, remove if exists
    if os.path.exists("build"):
        print("[IN] Path exists, recreate build dir...")
        shutil.rmtree("build")
        os.makedirs("build")
    else:
        print("[IN] First time! Create build dir...")
        os.makedirs("build")

    # Define global variables
    print("[IN] Defining global variables...")
    BUILD_TYPE = sys.argv[1]
    if (BUILD_TYPE == "system"):
        COMPILER      = "gcc"
        OPTIONS       = ""
        COMPILE_TESTS = True
    elif (BUILD_TYPE == "avr-atmega328p"):
        COMPILER      = "avr-gcc"
        OPTIONS       = " -mmcu=atmega328p"
        COMPILE_TESTS = False
    else:
        print("[!!] Please select a supported build type...")
        exit()

    print("[OK] Selected '" + BUILD_TYPE + "' as build type!")
    print("      Compiler: " + COMPILER)
    print("       Options: " + OPTIONS)
    print(" Compile Tests? " + str(COMPILE_TESTS))

    # Compile object files
    print("[IN] Compiling object files...")
    for f in glob.glob("src/*.c"):
        f_name = os.path.basename(f)
        f_base = f_name[:f_name.rindex('.')]
        print("     " + COMPILER + " -c -o build/" + f_base + ".o " + f + " -Iinclude" + OPTIONS)
        os.system(COMPILER + " -c -o build/" + f_base + ".o " + f + " -Iinclude" + OPTIONS)

    # Compile static library
    print("[IN] Compiling static library...")
    static_lib_command = "ar rcs build/estmath.a"
    for f in glob.glob("build/*.o"):
        static_lib_command += " "
        static_lib_command += f
    print("     " + static_lib_command)
    os.system(static_lib_command)
    

    # Compile tests
    if (COMPILE_TESTS):
        print("[IN] Compiling test programs...")
        for f in glob.glob("tests/*.c"):
            f_name = os.path.basename(f)
            f_base = f_name[:f_name.rindex('.')]
            os.system(COMPILER + " -c -o build/" + f_base + ".o " + f + " -Iinclude" + OPTIONS)

        for f in glob.glob("tests/*.c"):
            f_name = os.path.basename(f)
            f_base = f_name[:f_name.rindex('.')]
            compile_tests_command = COMPILER + " -o build/" + f_base + ".exe"
            for g in glob.glob("build/*.o"):
                g_name = os.path.basename(g)
                g_base = g_name[:g_name.rindex('.')]
                
                if (not g_base.startswith("test_") or f_base == g_base):
                    compile_tests_command += " "
                    compile_tests_command += g
            compile_tests_command += " -Iinclude" + OPTIONS
            print("     " + compile_tests_command)
            os.system(compile_tests_command)

    print("[OK] Done with the build process!")
else:
    print("Usage: build.py <system|avr-atmega328p>")