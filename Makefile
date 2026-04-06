all:
	cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=MinSizeRel  -DCMAKE_INSTALL_PREFIX=$(PWD)/build/install && cmake --build build

install:
	cmake --install build

clean:
	rm -rf build
