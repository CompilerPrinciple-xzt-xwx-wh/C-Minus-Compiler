
OBJS = scanner.o parser.o generator.o ast_builder.o ast_setget.o variable.o globals.o main.o
CC = /usr/bin/clang++-10
LLVM_AS = /usr/lib/llvm-10/bin/llvm-as 
LLI = /usr/lib/llvm-10/bin/lli

LLVM_INCLUDE = -I /usr/lib/llvm-10/include
LLVM_LIBS = -L /usr/lib/llvm-10/lib
LD_FLAGS = -lpthread -ldl -lz -lncurses -rdynamic -L/usr/local/lib -ljsoncpp

.PHONY: build clean test

build:
	flex -o scanner.cpp scanner.l
	bison -d -o parser.cpp parser.yacc
	$(CC) -g $(LLVM_INCLUDE) $(LLVM_LIBS) $(LD_FLAGS) -lLLVM ./*.cpp -o parse

test:
# Q1: quicksort
	@echo "\n\n******Q1: Quicksort******"
	cat ../test/quicksort.c | ./parse > ../test/test1.ll
	llvm-as ../test/test1.ll -o ../test/test1.bc	
	$(CC) ../test/test1.bc -o ../test/test1_exe
	../test/quicksort/linux-amd64 ../test/test1_exe


temp_test:
	cat ../test/test0.c | ./parse > ../test/test0.ll
	llvm-as ../test/test0.ll -o ../test/test0.bc
	$(CC) ../test/test0.bc -o ../test/test0_exe

clean:
	$(RM) -rf $(OBJS) parser.cpp parser.hpp parse scanner.cpp 
	$(RM) -f ../test/*.ll ../test/*.bc ../test/test0/test0_exe ../test/test1/test1_exe ../test/test2/test2_exe ../test/test3/test3_exe
	$(RM) -f ../test/test1/*.bc ../test/test1/*.ll ../test/test2/*.bc ../test/test2/*.ll ../test/test3/*.bc ../test/test3/*.ll 
