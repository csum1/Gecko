.PHONY: build
build:
	# for multi-config generators
	# cmake --build build --target all --config Debug
	cmake --build build --target all

# --fresh : deletes CMakeCache.txt and CMakeFiles

.PHONY: setup
setup:
	cmake -S . -B build -G Ninja \
		-DCMAKE_CXX_COMPILER=clang++ \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		--fresh --log-context \
		--preset=vcpkg
		# --profiling-output=cmake-trace.json --profiling-format=google-trace
	ln -s build/compile_commands.json .

.PHONY: setup-rel
setup-rel:
	cmake -S . -B build -G Ninja \
		-DCMAKE_CXX_COMPILER=clang++ \
		-DCMAKE_BUILD_TYPE=Release \
		--fresh --log-context 

.PHONY: clean
clean:
	rm -r build
	rm -r .cache
	rm compile_commands.json

# View google-trace with ui.perfetto.dev (perfetto.dev has much more to offer)
