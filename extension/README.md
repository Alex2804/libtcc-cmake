# Libtcc Extension
This is a extension for libtcc, which builds libtcc1-\*.a at runtime and places it in [LIBTCC1_DEST_PATH](#LIBTCC1_SRC_PATH).

The name of libtcc1-\*.a depends on the architecture to build for (e.g on 32 Bit the library is called libtcc1-64.a).

If you use Microsofts Visual C/C++ Compiler for CMake with the extension, then you have to move *"libtcc_test.exe"* to the root of the build directory or "*lib/(libtcc1-\*.a)*" and "*include/*" to the location of *"libtcc_test.exe"* or (simplest solution) use "*Ninja*" as build system (by passing "*-G "Ninja"*" to cmake).

## How to enable the extension
The extension should be enabled by default and you can disable it by setting
**LIBTCC_ENABLE_EXTENSION** to *FALSE*.

## CMake Variables
##### LIBTCC1_SRC_PATH <a name="LIBTCC1_SRC_PATH"></a>
Specifies the path to the source files for libtcc1-\*.a.  
By default this is "*lib_libtcc1/*" (**This should not be changed if you have no good reason!**).

**The path must end with a "/"!**


---
##### LIBTCC1_DEST_PATH <a name="LIBTCC1_DEST_PATH"></a>
Specifies the destination folder in which libtcc1-\*.a is placed.  
In addition, the object files are also created here. These are deleted after compilation and packing.  
By default this is "*lib/*"

**The path must end with a "/"!**
