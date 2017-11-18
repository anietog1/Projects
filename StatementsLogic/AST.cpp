#include "AST.h"
#include "Calculator.h"
#include <iostream>

using namespace std;

Calculator* calc = Calculator::getInstance();

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right):
  AST(),
  leftTree(left),
  rightTree(right)
{}

BinaryNode::~BinaryNode() {
  try {
    delete leftTree;
  } catch (...) {}

  try {
    delete rightTree;
  } catch(...) {}
}
   
AST* BinaryNode::getLeftSubTree() const {
  return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
  return rightTree;
}

UnaryNode::UnaryNode(AST* sub):
  AST(),
  subTree(sub)
{}

UnaryNode::~UnaryNode() {
  try {
    delete subTree;
  } catch (...) {}
}
   
AST* UnaryNode::getSubTree() const {
  return subTree;
}

OrNode::OrNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

bool OrNode::evaluate() {
  return getLeftSubTree()->evaluate() || getRightSubTree()->evaluate();
}

AndNode::AndNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

bool AndNode::evaluate() {
  return getLeftSubTree()->evaluate() && getRightSubTree()->evaluate();
}

StatementNode::StatementNode(bool val) :
  AST(),
  val(val)
{}

bool StatementNode::evaluate() {
  return val;
}

ImplNode::ImplNode(AST* left, AST* right):
  BinaryNode(left, right){}

bool ImplNode::evaluate(){
  return ! getLeftSubTree()->evaluate() || getRightSubTree()->evaluate();
}

EquivNode::EquivNode(AST* left, AST* right):
  BinaryNode(left, right){}

bool EquivNode::evaluate(){
  bool left = getLeftSubTree()->evaluate();
  bool right = getRightSubTree()->evaluate();
  return (!left && !right) || (left && right);
}

NegNode::NegNode(AST* sub)
  :UnaryNode(sub)
{}

bool NegNode::evaluate(){
  return ! getSubTree()->evaluate();
}

AssignNode::AssignNode(const string& idname, AST* sub)
  :UnaryNode(sub),idname(idname)
{}

bool AssignNode::evaluate(){
  bool value = getSubTree()->evaluate();
  (*calc)[idname] = value;

  return value;
}

QueryNode::QueryNode(AST* sub):
  UnaryNode(sub)
{}

bool QueryNode::evaluate(){
  bool value = sub->evaluate();
  cout << value << endl;

  return value;
}
