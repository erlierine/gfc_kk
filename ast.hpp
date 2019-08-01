#ifndef __AST_HPP__
#define __AST_HPP__ 1

#include <iostream>
#include <string> 
#include <vector>

class ExprAST{
public:
    virtual ExprAST* compile3ac() const = 0;
    virtual std::string print() const = 0;
    virtual ~ExprAST(){}
    static int label;
    static int tempNum;
};

class NumberExprAST : public ExprAST{
public:
    NumberExprAST(int v)
        :_value(v){}
    ExprAST* compile3ac() const;
    std::string print() const;
private:
    int _value;
};

class VariableExprAST : public ExprAST{
public:
    VariableExprAST(const std::string &n)
        :_name(n){}
    ExprAST* compile3ac() const;
    std::string print() const;
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
    ~InnerExprAST();
protected:
    std::vector<ExprAST*> _v;
};

class IncrExprAST : public InnerExprAST{
public:
    IncrExprAST(ExprAST* e1)
        :InnerExprAST(e1){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class DecrExprAST : public InnerExprAST{
public:
    DecrExprAST(ExprAST* e1)
        :InnerExprAST(e1){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class UMinusExprAST : public InnerExprAST{
public:
    UMinusExprAST(ExprAST *e1)
        :InnerExprAST(e1){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class AddExprAST : public InnerExprAST{
public:
    AddExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class SubExprAST : public InnerExprAST{
public:
    SubExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class MulExprAST : public InnerExprAST{
public:
    MulExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class DivExprAST : public InnerExprAST{
public:
    DivExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class ModExprAST : public InnerExprAST{
public:
    ModExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class LtExprAST : public InnerExprAST{
public:
    LtExprAST(ExprAST *e1, ExprAST *e2) 
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class LtEqExprAST : public InnerExprAST{
public:
    LtEqExprAST(ExprAST *e1, ExprAST *e2) 
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class GtExprAST : public InnerExprAST{
public:
    GtExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class GtEqExprAST : public InnerExprAST{
public:
    GtEqExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class NEqExprAST : public InnerExprAST{
public:
    NEqExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class EqExprAST : public InnerExprAST{
public:
    EqExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class AssignExprAST : public InnerExprAST{
public:
    AssignExprAST(std::string s, ExprAST* e)
        :InnerExprAST(e), _name(s){};
    ExprAST* compile3ac() const;
    std::string print() const;
private:
    std::string _name;
};

class IfExprAST : public InnerExprAST{
public:
    IfExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class IfElseExprAST: public InnerExprAST{
public:
    IfElseExprAST(ExprAST *e1, ExprAST *e2, ExprAST *e3)
        :InnerExprAST(e1, e2, e3){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class ForExprAST : public InnerExprAST{
public:
    ForExprAST(ExprAST *e1, ExprAST *e2, ExprAST *e3, ExprAST *e4)
        :InnerExprAST(e1, e2, e3, e4){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class WhileExprAST : public InnerExprAST{
public:
    WhileExprAST(ExprAST *e1, ExprAST *e2)
        :InnerExprAST(e1, e2){}
    ExprAST* compile3ac() const;
    std::string print() const;
};

class Block : public InnerExprAST{
public:
    Block(std::vector<ExprAST*> v)
        :InnerExprAST(v){}
    ExprAST* compile3ac() const;
    std::string print() const;
    void addExpr(ExprAST* e);
};
#endif