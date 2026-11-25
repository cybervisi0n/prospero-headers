# prospero-headers
C/C++ headers for use with the system libraries on the PS5. No more loose definitions of sce.*() everywhere!

For meson projects, just add prospero-headers as a dependency in your project and include this project as a subproject. For other build systems, include this repo as a git submodule and add ./include to the include directories.