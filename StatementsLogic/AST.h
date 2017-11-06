#pragma once

class AST {
 public:
  AST();
  virtual ~AST() = 0;
  virtual bool evaluate() = 0;
};

class BinaryNode : public AST {
 public:
  BinaryNode(AST* left, AST* right);
  ~BinaryNode();
  AST* getLeftSubTree() const;
  AST* getRightSubTree() const;
 private:
  AST* leftTree;
  AST* rightTree;
};

class UnaryNode : public AST {
 public:
  UnaryNode(AST* sub);
  ~UnaryNode();
  AST* getSubTree() const;
 private:
  AST* subTree;
};

class StatementNode : public AST {
 public:
  StatementNode(bool val);
  bool evaluate();
 private:
  bool val;
};

class OrNode : public BinaryNode {
 public:
  OrNode(AST* left, AST* right);
  bool evaluate();
}

class AndNode : public BinaryNode {
 public:
  AndNode(AST* left, AST* right);
  bool evaluate();
}

class ImplNode : public BinaryNode {
 public:
  ImplNode(AST* left, AST* right);
  bool evaluate();
}

class EquivNode : public BinaryNode {
 public:
  EquivNode(AST* left, AST* right);
  bool evaluate();
}

class NegNode : public UnaryNode {
 public:
  NegNode(AST* sub);
  bool evaluate();
}