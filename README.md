# ced

Simple text editor made with Qt.

# Build

Clone git repo:

> git clone https://github.com/Luka287/ced.git

> cd ced

Build an app:

> cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja "-DCMAKE_PREFIX_PATH=/path/to/Qt;/path/to/llvm" /path/to/qtcreator_sources

> cmake --build .