# Libtcc
This Project aims to build libtcc for supported platforms system independent with CMake.

## Usage
You can embed this CMake project as a subdirectory or build it as every other CMake script.

Make sure that you change the CMake variables according to your needs.

The default values should be enough to build a static library to link against with the required
dependencies in *"path/to/binary/dir/lib"* and *"path/to/binary/dir/include"*

## <a name="extension">Extension</a>
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
By default this is "*tcc*" or "*tcc-(Platform specific postfix)*"
depending on whether [LIBTCC_TARGET_SPECIFIC_NAME](#LIBTCC_TARGET_SPECIFIC_NAME) is true or false.

---
#### <a name="LIBTCC_TARGET_SPECIFIC_NAME">LIBTCC_TARGET_SPECIFIC_NAME</a>
Possible Values:
- TRUE
- FALSE *(Default)*

Defines if the target architecture should be contained in the resulting library (**Ignored if [LIBTCC_NAME](#LIBTCC_NAME) is defined**!).

---
#### <a name="LIBTCC_INSTALL_RUNTIME">LIBTCC_INSTALL_RUNTIME</a>
Possible Values:
- TRUE *(Default)*
- FALSE

Defines if the include headers get copied into "${CMAKE_BINARY_DIR}**/include/**".

---
#### <a name="LIBTCC_TARGET_ARCHITECTURE">LIBTCC_TARGET_ARCHITECTURE</a>
Defines the architecture to build for (should be recognized automatically if not defined).

---
#### <a name="LIBTCC_ENABLE_EXTENSION">LIBTCC_ENABLE_EXTENSION</a>
Possible Values:
- TRUE *(Default)*
- FALSE

Enables the [extension](#extension).
