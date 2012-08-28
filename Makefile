all: parser

clean:
	rm -rf parser.cpp parser.hpp parser tokens.cpp

parser.cpp: parser.y
	bison -d -o $@ $^

parser.hpp: parser.cpp

tokens.cpp: tokens.l parser.hpp
	lex -o $@ $^

parser: parser.cpp codegen.cpp main.cpp tokens.cpp
	g++ -o $@ *.cpp `llvm-config --libs core jit native --cxxflags --ldflags` -D __STDC_LIMIT_MACROS=1 -D __STDC_CONSTANT_MACROS=1

