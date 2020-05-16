# Libtcc
This Project aims to build libtcc for supported platforms system independent with CMake.

## Usage
You can embed this CMake project as a subdirectory or build it as every other CMake script.

Make sure that you change the CMake variables according to your needs.

## Supported and Tested Platforms
the library was tested with the following operating systems and architectures:
- Linux
    - x86
    - x86_64
    - armeabi with Hardfloat (tested ARMv7a)
    - aarch64 (arm64)
- Android (look [here](https://github.com/Alex2804/libtcc-cmake-android) for a small demo)
    - x86
    - x86_64
    - armeabi (with Hardfloat, tested ARMv7a, take a look at [Issues](#Issues) for limitations on this architecture)
    - aarch64 (arm64)
- Windows
    - x86
    - x86_64
- MacOS
    - x86_64
    
Even though RISC-V 64Bit is supported by libtcc, I have no RISC-V 64 Bit device or emulator to test this, yet.

## Issues
- Valgrind indicates a memory leak when memory is allocated in libtcc compiled code and released in the main application
  (or vice versa). This seems to be a false positive.

- If you allocate memory in tcc compiled code and free it in the main application, the program crashes if it is compiled
  with MSVC (The compiler of libtcc itself is negligible, only the compiler of the main application is crucial).

- On Android ARM (tested ARMv7 but should be the case for most/all arm architectures less than or equal ARMv7) double
  argument passing from libtcc compiled code to other code (or vice versa) (e.g. the main application or c standard
  library) is not working.  
  (**especially ARMv8 (aarch64/arm64) is not affected by this!**)

## <a name="Extension">Extension</a>
There is an extension to compile *libtcc1.a* at runtime.
You can enable or disable the extension with [LIBTCC_ENABLE_EXTENSION](#LIBTCC_ENABLE_EXTENSION).  
For more information like CMake variables look [here](extension/README.md).

---
## CMake Variables
#### <a name="LIBTCC_TEST">LIBTCC_TEST</a>
Possible Values:
- TRUE
- FALSE *(Default)*

Enables or disables the unit tests.

---
#### <a name="LIBTCC_BUILD_TYPE">LIBTCC_BUILD_TYPE</a>
Possible Values:
- SHARED
- STATIC *(Default)*

Defines if the Library should be static or shared

---
#### <a name="LIBTCC_NAME">LIBTCC_NAME</a>
Defines the name of the library file.
By default this is "*libtcc*" or "*libtcc-(Platform specific postfix)*"
depending on whether [LIBTCC_TARGET_SPECIFIC_NAME](#LIBTCC_TARGET_SPECIFIC_NAME) is false or true.

---
#### <a name="LIBTCC_TARGET_SPECIFIC_NAME">LIBTCC_TARGET_SPECIFIC_NAME</a>
Possible Values:
- TRUE
- FALSE *(Default)*

Defines if the target architecture should be contained in the resulting library
(**Ignored if [LIBTCC_NAME](#LIBTCC_NAME) is defined**!).

---
#### <a name="LIBTCC_INSTALL_RUNTIME">LIBTCC_INSTALL_RUNTIME</a>
Possible Values:
- TRUE *(Default)*
- FALSE

Defines if the include headers get copied into "[LIBTCC_RUNTIME_PATH](#LIBTCC_RUNTIME_PATH)**/include/**".

---
#### <a name="LIBTCC_RUNTIME_PATH">LIBTCC_RUNTIME_PATH</a>
Defines the directory where the runtime files (include headers and source files for libtcc1 if the
[extension](#Extension) is enabled) get copied (in subdirectories).  
By default this is "*libtcc/*"-  
**The Path is relative to the binary directory (CMAKE_BINARY_DIR)!**

---
#### <a name="LIBTCC_TARGET_ARCHITECTURE">LIBTCC_TARGET_ARCHITECTURE</a>
Defines the architecture to build for (should be recognized automatically if not defined).

---
#### <a name="LIBTCC_ENABLE_EXTENSION">LIBTCC_ENABLE_EXTENSION</a>
Possible Values:
- TRUE *(Default)*
- FALSE

Enables the [extension](#extension).
