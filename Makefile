program: lex.yy.o parser.o ast.o cond.o
	g++ lex.yy.o parser.o ast.o cond.o -o program
ast.o: ast.cpp ast.hpp
	g++ ast.cpp -c -o ast.o
parser.o: parser.tab.cpp parser.tab.hpp ast.hpp
	g++ parser.tab.cpp -c -o parser.o
cond.o: cond.cpp cond.hpp
	g++ cond.cpp -c -o cond.o

lex.yy.o: lex.yy.c parser.tab.hpp
	g++ lex.yy.c -c -o lex.yy.o

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -dv parser.ypp
lex.yy.c: lexer.l
	flex lexer.l
