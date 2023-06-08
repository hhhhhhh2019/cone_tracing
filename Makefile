all: voxelizer engine test

make_dirs:
	mkdir -p bin

test: make_dirs
	make -C test

engine: make_dirs
	make -C engine

voxelizer: make_dirs
	make -C voxelizer

clean:
	make -C test clean
	make -C engine clean
	make -C voxelizer clean
	rm ./bin -r
