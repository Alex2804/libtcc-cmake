This Project aims to build libtcc as static or shared library with CMake.

## Usage:
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
## CMake variables:
##### TCC_BUILD_TYPE:

Possible Values:
- STATIC
- SHARED

Defines if the Library should be static or shared  
(**it is required to write the values in uppercase!**).

---
##### TCC_LIB_NAME:

Defines the name of the library file.

---
##### TCC_TARGET_SPECIFIC_NAME:
Possible Values:
- True
- False

Defines if the target architecture should be contained in the resulting library (**Ignored if TCC_LIB_NAME is defined**!).

---
##### TCC_INSTALL_RUNTIME_DEFAULT:
Possible Values:
- True
- False

Defines if the runtime library and include headers get copied into "*lib*" and "*include*"
 at "path/to/binary/dir/**lib/tcc/**".

---
##### TCC_INSTALL_SHARED_TO_BINARY:
Possible Values:
- True
- False

Defines whether the resulting shared library will be copied to the root of the binary directory,
assuming a shared library is created.

---
##### TCC_TARGET_ARCHITECTURE:
Defines the architecture to build for (should be recognized automatically if not defined).