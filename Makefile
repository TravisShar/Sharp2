output: main.o SYMBOL.o EXPRESSIONS.o LITERAL.o
	g++ -o runtable main.o SYMBOL.o EXPRESSIONS.o LITERAL.o

main.o: main.cpp
	g++ -c main.cpp

SYMBOL.o: SYMBOL.h EXPRESSIONS.h LITERAL.h SYMBOL.cpp EXPRESSIONS.cpp LITERAL.cpp
	g++ -c SYMBOL.cpp EXPRESSIONS.cpp LITERAL.cpp

clean:
	rm runtable main.o SYMBOL.o EXPRESSIONS.o LITERAL.o