# Libtcc Extension
This is a extension for libtcc, which builds libtcc1-*.a at runtime and places it in [LIBTCC1_DEST_PATH](#LIBTCC1_SRC_PATH).

The name of libtcc1-*.a depends on the architecture to build for (e.g on 32 Bit the library is called libtcc1-64.a).

## CMake Variables
##### LIBTCC1_SRC_PATH <a name="LIBTCC1_SRC_PATH"></a>
Specifies the path to the source files for libtcc1-*.a.  
By default this is "*lib_libtcc1/*" (**This should not be changed if you have no good reason!**).

**The path must end with a "/"!**


---
##### LIBTCC1_DEST_PATH <a name="LIBTCC1_DEST_PATH"></a>
Specifies the destination folder in which libtcc1-*.a is placed.  
In addition, the object files are also created here. These are deleted after compilation and packing.  
By default this is "*lib/*"

**The path must end with a "/"!**