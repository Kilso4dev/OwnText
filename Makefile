
EXEC_NAME = vemacs


compile-easy:
	gcc -g -o ${EXEC_NAME} ./termCurses.c -lncurses
# run:
#	./build/${EXEC_NAME}


clean:
	rm -f -r ./build
	rm -f -r ./cmake-build-debug


prepare: clean;
	mkdir -p build && \
	cd build && \
	cmake ..

compile:
	if [ ! -d "build" ]; then make prepare; fi
	cd build && \
	make

run: compile;
	cd build && ./${EXEC_NAME}


