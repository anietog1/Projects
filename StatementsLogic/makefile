Token.o: Token.cpp Token.h

Scanner.o: Scanner.cpp Token.cpp Scanner.h Token.h

Calculator.o: Calculator.cpp Calculator.h

AST.o: AST.cpp Calculator.cpp AST.h Calculator.h

Parser.o: Parser.cpp AST.cpp Scanner.cpp Token.cpp Parser.h AST.h Scanner.h Token.h

clean:
	rm *.o *~ *.exe *.stackdump
