.PHONY: build
build:
	# for multi-config generators
	# cmake --build build --target all --config Debug
	cmake --build build --target all

# --fresh : deletes CMakeCache.txt and CMakeFiles
#

BUILD_DIR=build
COMPILE_CMD_FILE=compile_commands.json

# to work with vulkan c++ modules:
# -DENABLE_CPP20_MODULE=ON
.PHONY: setup
setup:
	cmake -S . -B build -G Ninja \
		-DCMAKE_CXX_COMPILER=clang++ \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DENABLE_CPP20_MODULE=ON \
		--fresh --log-context \
		--preset=vcpkg
		# --profiling-output=cmake-trace.json --profiling-format=google-trace
		[ -e ${COMPILE_CMD_FILE} ] && rm ${COMPILE_CMD_FILE}
		ln -s ${BUILD_DIR}/${COMPILE_CMD_FILE} .

.PHONY: setup-rel
setup-rel:
	cmake -S . -B build -G Ninja \
		-DCMAKE_CXX_COMPILER=clang++ \
		-DCMAKE_BUILD_TYPE=Release \
		--fresh --log-context 

.PHONY: run
run:
	./build/bin/app

.PHONY: clean
clean:
	rm -r build
	rm -r .cache
	rm compile_commands.json

# View google-trace with ui.perfetto.dev (perfetto.dev has much more to offer)
