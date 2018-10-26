MIPS_CC = mips-linux-gnu-gcc
MIPS_OBJCOPY = mips-linux-gnu-objcopy

build/main.o: src/main.cpp src/main.hpp
	g++ -std=c++11 -c src/main.cpp -o build/main.o
 
build/helpers.o: src/helpers.cpp src/helpers.hpp
	g++ -std=c++11 -c src/helpers.cpp -o build/helpers.o

simulator: build/main.o build/helpers.o
	mkdir -p bin
	g++ build/main.o build/helpers.o -o bin/mips_simulator

testbench: 
	mkdir -p bin
	cp -a testbench.sh bin/mips_testbench
	chmod 755 bin/mips_testbench
clean:
	rm build/*.o