# Libtcc
This Project aims to build libtcc for supported platforms system independent with cmake.

## Usage
You can embed this CMake project as a subdirectory or build it as every other CMake script.

Make sure that you change the CMake variables according to your needs.

The default values should be enough to build a static library to link against with the required
dependencies in *"path/to/binary/dir/lib"* and *"path/to/binary/dir/include"*

You must pass the location of the dependencies to every *TCCState** with the following 3 lines:
````c
tcc_add_library_path(tccState, "path/to/lib");
tcc_set_lib_path(tccState, "path/to/lib");
tcc_add_include_path(tccState, "path/to/include");
````

You can enable the extension which compiles libtcc1-*.a (which is required to compile some programs)
at runtime with [LIBTCC_ENABLE_EXTENSION](#LIBTCC_ENABLE_EXTENSION).

---
## CMake Variables
##### LIBTCC_BUILD_TYPE <a name="LIBTCC_BUILD_TYPE"></a>
Possible Values:
- SHARED
- STATIC *(Default)*

Defines if the Library should be static or shared  
(**it is required to write the values in uppercase!**).

---
##### LIBTCC_NAME <a name="TCC_LIB_NAME"></a>
Defines the name of the library file.
By default this is "*tcc*" or "*tcc-(Platform specific postfix)*"
depending on whether [LIBTCC_TARGET_SPECIFIC_NAME](#LIBTCC_TARGET_SPECIFIC_NAME) is true or false.

---
##### LIBTCC_TARGET_SPECIFIC_NAME <a name="LIBTCC_TARGET_SPECIFIC_NAME"></a>
Possible Values:
- TRUE
- FALSE *(Default)*

Defines if the target architecture should be contained in the resulting library (**Ignored if LIBTCC_NAME is defined**!).

---
##### LIBTCC_INSTALL_RUNTIME <a name="LIBTCC_INSTALL_RUNTIME"></a>
Possible Values:
- TRUE *(Default)*
- FALSE

Defines if the include headers get copied into
"[LIBTCC_RUNTIME_TARGET_DIR](#LIBTCC_RUNTIME_TARGET_DIR)**/include/**".

---
##### LIBTCC_RUNTIME_TARGET_DIR <a name="LIBTCC_RUNTIME_TARGET_DIR"></a>
Defines the directory where to copy the runtime headers.
By default this is *CMAKE_BINARY_DIR*.

---
##### LIBTCC_INSTALL_SHARED <a name="LIBTCC_INSTALL_SHARED_TO_BINARY"></a>
Possible Values:
- TRUE *(Default)*
- FALSE

Defines whether the resulting shared library will be copied to [LIBTCC_SHARED_TARGET_DIR](#LIBTCC_SHARED_TARGET_DIR),
assuming a shared library is created.

---
##### LIBTCC_SHARED_TARGET_DIR <a name="LIBTCC_SHARED_TARGET_DIR"></a>
Defines the directory where to copy the shared library into, assuming a shared library is created and [LIBTCC_INSTALL_SHARED](#LIBTCC_INSTALL_SHARED) is true.

---
##### LIBTCC_TARGET_ARCHITECTURE <a name="LIBTCC_TARGET_ARCHITECTURE"></a>
Defines the architecture to build for (should be recognized automatically if not defined).

---
##### LIBTCC_ENABLE_EXTENSION <a name="LIBTCC_ENABLE_EXTENSION"></a>
Possible Values:
- TRUE *(Default)*
- FALSE

Enables the extension to compile libtcc1-*.a at runtime
(for more information like CMake variables look [here](extension/README.md))
