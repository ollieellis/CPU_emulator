CC = g++
CPPFLAGS = -W -Wall
 # For MIPS binaries. Turn on all warnings, enable all optimisations and link everything statically
MIPS_CC = mips-linux-gnu-gcc
MIPS_OBJCOPY = mips-linux-gnu-objcopy
MIPS_OBJDUMP = mips-linux-gnu-objdump
MIPS_CPPFLAGS = -W -Wall -O3 -fno-builtin -march=mips1 -mfp32
MIPS_LDFLAGS = -nostdlib -Wl,-melf32btsmip -march=mips1 -nostartfiles -mno-check-zero-division -Wl,--gpsize=0 -static -Wl,-Bstatic -Wl,--build-id=none
 # Compile C file (.c) into MIPS object file (.o)
%.mips.o: %.c
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@
 # Assemble MIPS assembly file (.s) into MIPS object file (.o)
%.mips.o: %.s
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@
 # Link MIPS object file (.o), producing .elf, using memory locations specified in spec
%.mips.elf: %.mips.o
	$(MIPS_CC) $(MIPS_CPPFLAGS) $(MIPS_LDFLAGS) -T linker.ld $< -o $@
 # Extract binary instructions only from linked object file (.elf)
%.mips.bin: %.mips.elf
	$(MIPS_OBJCOPY) -O binary --only-section=.text $< $@
 # Disassemble linked object file (.elf), pulling out instructions as MIPS assembly file (.s)
%.mips.s : %.mips.elf
	$(MIPS_OBJDUMP) -j .text -D $< > $@

# build/simulator.o: src/simulator.cpp src/simulator.hpp
# 	g++ -std=c++11 -c src/simulator.cpp -o build/simulator.o
 
# build/helpers.o: src/helpers.cpp src/helpers.hpp
# 	g++ -std=c++11 -c src/helpers.cpp -o build/helpers.o

# build/memory.o: src/memory.cpp src/memory.hpp
# 	g++ -std=c++11 -c src/memory.cpp -o build/memory.o

# build/registers.o: src/registers.cpp src/registers.hpp
# 	g++ -std=c++11 -c src/registers.cpp -o build/registers.o

build/%.o : src/%.cpp src/%.hpp
	mkdir -p build
	g++ -std=c++11 -c $< -o $@

simulator: build/simulator.o build/helpers.o build/memory.o build/registers.o build/instructions.o  
	mkdir -p bin
	g++ -std=c++11 build/simulator.o build/helpers.o build/memory.o build/registers.o build/instructions.o -o bin/mips_simulator

testbench: 
	mkdir -p bin
	cp -a test/testbench.sh bin/mips_testbench
	chmod 755 bin/mips_testbench
clean:
	rm build/*.o