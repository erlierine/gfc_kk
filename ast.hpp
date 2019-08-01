#ifndef __AST_HPP__
#define __AST_HPP__ 1

#include <iostream>
#include <string> 
#include <vector>

class ExprAST{
public:
    virtual ExprAST* compile3ac();
    virtual void print();
    virtual ~ExprAST(){
        
    }
};

class NumberExprAST : public ExprAST{
public:
    NumberExprAST(int v)
        :_v(v){}
    ExprAST* compile3ac();
    void print();
private:
    double _v;
};

class VariableExprAST : public ExprAST{
public:
    VariableExprAST(const std::string &n)
        :_name(n){}
    ExprAST* compile3ac();
    void print();
private:
    std::string _name;
};
class InnerExprAST : public ExprAST{
public:
    InnerExprAST(const std::vector<ExprAST*> &v)
        :_v(v){}
    InnerExprAST(ExprAST *e1);
    InnerExprAST(ExprAST *e1, ExprAST *e2);
    InnerExprAST(ExprAST *e1, ExprAST *e2, ExprAST *e3);
    InnerExprAST(ExprAST *e1, ExprAST *e2, ExprAST *e3, ExprAST *e4);
    ExprAST* compile3ac();
    void print();
    ~InnerExprAST();
private:
    std::vector<ExprAST*> _v;
};

class AddExprAST : public InnerExprAST{
public:
    AddExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac();
    void print();
};

class SubExprAST : public InnerExprAST{
public:
    SubExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac();
    void print();
};

class MulExprAST : public InnerExprAST{
public:
    MulExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac();
    void print();
};

class DivExprAST : public InnerExprAST{
public:
    DivExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac();
    void print();
};

class LtExprAST : public InnerExprAST{
public:
    LtExprAST(ExprAST *e1, ExprAST *e2) 
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac();
    void print();
};

class GtExprAST : public InnerExprAST{
public:
    GtExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac();
    void print();
};

class AssignExprAst : public InnerExprAST{
public:
    AssignExprAst(std::string s, ExprAST* e)
        :InnerExprAST(e), _name(s){};
    ExprAST* compile3ac();
    void print();
private:
    std::string _name;
};

class IfExprAST : public InnerExprAST{
public:
    IfExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac();
    void print();
};

class IfElseExprAST: public InnerExprAST{
public:
    IfElseExprAST(ExprAST *e1, ExprAST *e2, ExprAST *e3)
        :InnerExprAST(e1, e2, e3){}
    ExprAST* compile3ac();
    void print();
};

class ForExprAST : public InnerExprAST{
public:
    ForExprAST(ExprAST *e1, ExprAST *e2, ExprAST *e3, ExprAST *e4)
        :InnerExprAST(e1, e2, e3, e4){}
    ExprAST* compile3ac();
    void print();
};

#endif