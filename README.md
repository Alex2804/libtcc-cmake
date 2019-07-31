This Project aims to build libtcc as static or shared library with CMake.

## Usage
You can embed this CMake project as a subdirectory or build it as every other CMake script.

Make sure that you change the CMake variables according to your needs.

The default values should be enough to build a static library to link against with the required
dependencies in "path/to/binary/dir/lib/tcc/"

You must pass the location of the dependencies to every *TCCState** with the following 3 lines:
````c
tcc_add_library_path(tccState, "lib/tcc/lib/");
tcc_set_lib_path(tccState, "lib/tcc/lib/");
tcc_add_include_path(tccState, "lib/tcc/include/");
````

---
## CMake Variables
##### TCC_BUILD_TYPE <a name="TCC_BUILD_TYPE"></a>

Possible Values:
- SHARED *(Default)*
- STATIC

Defines if the Library should be static or shared  
(**it is required to write the values in uppercase!**).

---
##### TCC_LIB_NAME <a name="TCC_LIB_NAME"></a>
Defines the name of the library file.
By default this is "*tcc*" or "*tcc-(Platform specific postfix)*"
depending on whether [TCC_TARGET_SPECIFIC_NAME](#TCC_TARGET_SPECIFIC_NAME) is true or false.

---
##### TCC_TARGET_SPECIFIC_NAME <a name="TCC_TARGET_SPECIFIC_NAME"></a>
Possible Values:
- True
- False *(Default)*

Defines if the target architecture should be contained in the resulting library (**Ignored if TCC_LIB_NAME is defined**!).

---
##### TCC_INSTALL_RUNTIME <a name="TCC_INSTALL_RUNTIME"></a>
Possible Values:
- True *(Default)*
- False

Defines if the runtime library and include headers get copied into "*lib*" and "*include*"
at "[TCC_RUNTIME_TARGET_DIR](#TCC_RUNTIME_TARGET_DIR)/**lib/tcc/**".

---
##### TCC_RUNTIME_TARGET_DIR <a name="TCC_RUNTIME_TARGET_DIR"></a>
Defines the directory where to copy the runtime library and headers.
By default this is *CMAKE_BINARY_DIR*.

---
##### TCC_INSTALL_SHARED <a name="TCC_INSTALL_SHARED_TO_BINARY"></a>
Possible Values:
- True *(Default)*
- False

Defines whether the resulting shared library will be copied to [TCC_SHARED_TARGET_DIR](#TCC_SHARED_TARGET_DIR),
assuming a shared library is created.

---
##### TCC_SHARED_TARGET_DIR <a name="TCC_SHARED_TARGET_DIR"></a>
Defines the directory where to copy the shared library into, assuming a shared library is created and [TCC_INSTALL_SHARED](#TCC_INSTALL_SHARED) is true.

---
##### TCC_TARGET_ARCHITECTURE <a name="TCC_TARGET_ARCHITECTURE"></a>
Defines the architecture to build for (should be recognized automatically if not defined).