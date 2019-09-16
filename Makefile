tac: lex.yy.o parser.tab.o ast.o
	g++  -std=c++14 -Wall -o $@ $^
lex.yy.o: lex.yy.c parser.tab.hpp
	g++  -std=c++14 -Wno-sign-compare -Wall -c -o $@ $<
lex.yy.c: lexer.lex
	flex  $<
parser.tab.o: parser.tab.cpp parser.tab.hpp ast.hpp
	g++  -std=c++14 -Wall -c -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
ast.o: ast.cpp ast.hpp
	g++  -std=c++14 -Wall -c -o $@ $<

.PHONY: clean

clean:
	rm -f *tab* lex.yy.* *.o *output tac