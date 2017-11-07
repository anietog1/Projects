#pragma once
#include <string>

enum TokenType{
  OPERATOR, ID, LKEY, RKEY, LPAREN, RPAREN, ASSIGN, OR, AND, IMPL, EQUIV, NEG, KEYWORD, COMMA, QUERY, END, UNRECOGNIZED
};

class Token {
 public:
  Token();
  Token(TokenType typ, int line, int col);
  virtual ~Token();
  TokenType getType() const;
  int getLine() const;
  int getCol() const;
  virtual string getLex() const;
 private:
  TokenType type;
  int line,col;
};

class LexicalToken: public Token {
 public:
  LexicalToken(TokenType typ, std::string* lex, int line, int col);
  ~LexicalToken();
  virtual std::string getLex() const;
 private:
  std::string* lexeme;
};
