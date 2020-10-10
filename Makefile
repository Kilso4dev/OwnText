x='vemacs' # DEFAULT

all: compile;

compile:
	mkdir -p build
	cd build && make || (cmake .. && make)

recompile: clean compile;

clean:
	rm -r -f ./build
	rm -f vgcore.*


tests: compile;


run:
	./build/$(x)

run-debug:
	valgrind ./build/$(x)

run-debug-full:
	valgrind --leak-check=full ./build/$(x)
