#pragma once
#include <string>

enum TokenType {
  ID, KEYWORD, ASSIGN, LPAREN, RPAREN,
  NEG, AND, OR, IMPL, EQUIV, QUERY, EOF, EOL,
  UNRECOGNIZED
};

class Token {
 public:
  Token();
  Token(TokenType typ, int line, int col);
  virtual ~Token();
  TokenType getType() const;
  int getLine() const;
  int getCol() const;
  virtual std::string getLex() const;
 private:
  TokenType type;
  int line, col;
};

class LexicalToken: public Token {
 public:
  LexicalToken(TokenType typ, std::string* lex, int line, int col);
  ~LexicalToken();
  virtual std::string getLex() const;
 private:
  std::string* lexeme;
};
