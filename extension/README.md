# Libtcc Extension
This is a extension for libtcc, which builds libtcc1.a at runtime.

The name of libtcc1.a is defined by [LIBTCC1_NAME](#LIBTCC1_NAME).

## How to enable the extension?
The extension is enabled by default and you can disable it by setting
**LIBTCC_ENABLE_EXTENSION** to *FALSE*.


## How does the extension work?
The extension looks every `atcc_new()` call, if libtcc-\*.a exists in [LIBTCC1_DEST_PATH](#LIBTCC1_DEST_PATH)
and compiles it if this is not the case.


## Methods
The extension provides additional methods which can be included with *libtcc_ext.h*.

---
#### <a name="atcc_configure_state">TCCState\* atcc_configure_state(TCCState\* state)</a>
Sets the include and lib paths and the error function for the passed *state*.

---
#### <a name="atcc_new">TCCState\* atcc_new()</a>
Compiles libtcc1.a if required (and possible) and creates a new TCCState\* configured with
[atcc_configure_state](#atcc_configure_state).  
Returns the created TCCState\* or NULL if creation was not possible.

---
#### <a name="atcc_make_ar">int atcc_make_ar(const char* name, int fileCount, char** files</a>
Creates an \*.a archive with the given file name, from the passed file names from *files*. *fileCount* must
contain the number of Elements contained in *files*.  
Returns -1 on failure.

**The full path including the file extension must be passed!**

---
#### <a name="atcc_build_libtcc1">int atcc_build_libtcc1()</a>
Builds libtcc1.a from source located in [LIBTCC1_SRC_PATH](#LIBTCC1_SRC_PATH) with [LIBTCC1_NAME](#LIBTCC1_NAME) as name
in [LIBTCC1_DEST_PATH](#LIBTCC1_DEST_PATH). The object files get compiled in [LIBTCC1_OBJ_PATH](#LIBTCC1_OBJ_PATH).  
Returns -1 on failure.

---
#### <a name="atcc_set_error_func">void atcc_set_error_func(void\* error_opaque, TCCErrorFunc error_func)</a>
Sets the error/warning callback for every TCCState which will be configured by
[atcc_configure_state](#atcc_configure_state).

---
#### <a name="atcc_set_include_path">void atcc_set_include_path(const char* path)</a>
Sets [LIBTCC_INCLUDE_PATH](#LIBTCC_INCLUDE_PATH) at runtime.

---
#### <a name="atcc_set_libtcc1_name">void atcc_set_libtcc1_name(const char* name)</a>
Sets [LIBTCC1_NAME](#LIBTCC1_NAME) at runtime.

---
#### <a name="atcc_set_libtcc1_src_path">void atcc_set_libtcc1_src_path(const char* path)</a>
Sets [LIBTCC1_SRC_PATH](#LIBTCC1_SRC_PATH) at runtime.

---
#### <a name="atcc_set_libtcc1_obj_path">void atcc_set_libtcc1_obj_path(const char* path)</a>
Sets [LIBTCC1_OBJ_PATH](#LIBTCC1_OBJ_PATH) at runtime.

---
#### <a name="atcc_set_libtcc1_dest_path">void atcc_set_libtcc1_dest_path(const char* path)</a>
Sets [LIBTCC1_DEST_PATH](#LIBTCC1_DEST_PATH) at runtime.

---

## CMake Variables
#### <a name="LIBTCC_INCLUDE_PATH">LIBTCC_INCLUDE_PATH</a>
Specifies the include path of libtcc for every TCCState which will be configured which will be configured by
[atcc_configure_state](#atcc_configure_state).  
By default this is "*include/*".

---
#### <a name="LIBTCC1_NAME">LIBTCC1_NAME</a>
Specifies the name of libtcc1.  
By default this is "libtcc1-\*.a" where "\*" is target specific (e.g. on x86_64 the library is called libtcc1-x86_64.a).

---
#### <a name="LIBTCC1_SRC_PATH">LIBTCC1_SRC_PATH</a>
Specifies the path to the source files for libtcc1.a.  
By default this is "*lib_libtcc1/*" (**This should not be changed if you have no good reason!**).

**The path must end with a "/"!**

---
#### <a name="LIBTCC1_OBJ_PATH">LIBTCC1_OBJ_PATH</a>
Specifies the destination folder in which the object files for the compilation of libtcc1.a are placed. These are
deleted after compilation and packing.  
By default this is "*lib/*"

**The path must end with a "/"!**

---
#### <a name="LIBTCC1_DEST_PATH">LIBTCC1_DEST_PATH</a>
Specifies the destination folder in which libtcc1.a is placed.  
By default this is "*lib/*"

**The path must end with a "/"!**
