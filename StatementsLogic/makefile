stlogic: Main.o Parser.o Scanner.o AST.o Token.o Calculator.o
	g++ -o $@ $^

Main.o: Parser.cpp AST.cpp Parser.h AST.h Exceptions.h

Parser.o: Parser.cpp Scanner.cpp Token.cpp AST.cpp Parser.h Scanner.h Token.h AST.h Exceptions.h

Scanner.o: Scanner.cpp Token.cpp Scanner.h Token.h Exceptions.h

AST.o: AST.cpp AST.h Exceptions.h

Token.o: Token.cpp Token.h

Calculator.o: Calculator.cpp Calculator.h

clean:
	rm -f *.o *.exe* *~ \#*
