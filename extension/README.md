# Libtcc Extension
This is a extension for libtcc, which builds libtcc1-\*.a at runtime and places it in [LIBTCC1_DEST_PATH](#LIBTCC1_SRC_PATH).

The name of libtcc1-\*.a depends on the architecture to build for (e.g on 32 Bit the library is called libtcc1-32.a).

If you use Microsofts Visual C/C++ Compiler for CMake with the extension, then you have to move *"libtcc_test.exe"* to the root of the build directory or "*lib/(libtcc1-\*.a)*" and "*include/*" to the location of *"libtcc_test.exe"* or (simplest solution) use "*Ninja*" as build system (by passing "*-G "Ninja"*" to cmake).


## How to enable the extension?
The extension should be enabled by default and you can disable it by setting
**LIBTCC_ENABLE_EXTENSION** to *FALSE*.


## How does the extension work?
The extension looks every `tcc_new()` call, if libtcc-\*.a exists in [LIBTCC1_DEST_PATH](#LIBTCC1_SRC_PATH)
and compiles it if this is not the case.


## Methods
The extension provides additional methods which can be included with "libtcc_ext.h".

---
#### <a name="atcc_new">TCCState\* atcc_new()</a>
Creates a new TCCState\*, sets the include and lib path and compiles libtcc1-\*.a if possible.  
Returns the created TCCState\* or NULL if creation was not possible.

---
#### <a name="atcc_make_ar">int atcc_make_ar(const char* name, int fileCount, char** files</a>
Creates an \*.a archive with the given file name, from the passed file names from *files*. *fileCount* must
contain the number of Elements contained in *files*.  
Returns 0 if the archive was successfully created, another value if not.

**The full path including the file extension must be passed!**

---
#### <a name="atcc_build_libtcc1_default">int atcc_build_libtcc1_default()</a>
Builds libtcc1-\*.a from source with an platform dependent name in [LIBTCC1_SRC_PATH](#LIBTCC1_DEST_PATH).
The object files get compiled in [LIBTCC1_DEST_PATH](#LIBTCC1_DEST_PATH).
Returns 0 if libtcc1-\*.a was successfully created, another value if not.

---
#### <a name="atcc_build_libtcc1">int atcc_build_libtcc1(const char* name, const char* destPath, const char* srcPath)</a>
Builds libtcc1-\*.a from source with the passed *name* in *destPath*. The object files get compiled in *destPath*
and the source files must be located in *srcPath*.  
Returns 0 if libtcc1-\*.a was successfully created, another value if not.


## CMake Variables
#### <a name="LIBTCC1_SRC_PATH">LIBTCC1_SRC_PATH</a>
Specifies the path to the source files for libtcc1-\*.a.  
By default this is "*lib_libtcc1/*" (**This should not be changed if you have no good reason!**).

**The path must end with a "/"!**


---
#### <a name="LIBTCC1_DEST_PATH">LIBTCC1_DEST_PATH</a>
Specifies the destination folder in which libtcc1-\*.a is placed.  
In addition, the object files are also created here. These are deleted after compilation and packing.  
By default this is "*lib/*"

**The path must end with a "/"!**
