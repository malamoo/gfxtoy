# Geosmith

Simulates physical geography in an interactive voxel playground.

Shape the landscape using erosion, weathering, tectonics, volcanism, climate, and more!

## Supported platforms

- MinGW
- Linux

## Dependencies

- OpenGL
- [GLFW platform dependencies](https://www.glfw.org/docs/latest/compile_guide.html)
- make
- CMake
- Git

## Build

Ensure GLFW static lib is built after cloning for the first time:
```shell
cd lib/glfw
git submodule init
git submodule update
mkdir build
cmake -S . -B build \
  -D GLFW_BUILD_EXAMPLES=OFF \
  -D GLFW_BUILD_TESTS=OFF \
  -D GLFW_BUILD_DOCS=OFF
# -G "MinGW Makefiles", if MinGW
cmake --build build
```

From project root directory: `make`