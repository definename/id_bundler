echo [*] Build directory is checked...
BUILD_DIR=../build/eclipse-gcc-x64-debug
mkdir -p $BUILD_DIR
pushd $BUILD_DIR

echo [*] CMake is running...
cmake \
	-G"Eclipse CDT4 - Unix Makefiles" \
	"-DCMAKE_BUILD_TYPE=Debug" \
	"-DCMAKE_CONFIGURATION_TYPES=Debug" \
	"-DCMAKE_C_FLAGS=-m64" \
	"-DCMAKE_CXX_FLAGS=-m64" \
	"../../src"

echo [*] Make is running...
make

echo [*] Project generation succeeded!
popd
