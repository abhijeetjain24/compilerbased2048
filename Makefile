all: assignment.lpp assignment.ypp
	 bison -d assignment.ypp
	flex -o lex.yy.cpp assignment.lpp
	g++ lex.yy.cpp assignment.tab.cpp assign.cpp -o output
	./output
clean:
	rm -f *.o output *tab.* lex.yy.cpp