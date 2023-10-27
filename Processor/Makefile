G++ = g++


all: object

object:
	@ $(G++) $(FLAGS) src/main.cpp src/processor.cpp ../Input_to_buf/src/input.cpp src/stack.cpp -o out
run:
	@ ./out ../Assembler.txt
