#include <iostream>
#include <string>
#include <fstream>
#include "ast.hpp"

std::ofstream OutFile("tac.txt");

int ExprAST::label = 0;
int ExprAST::tempNum = 0;

InnerExprAST::~InnerExprAST(){
    for (unsigned i = 0; i < _v.size(); i++)
        delete _v[i];   
}

InnerExprAST::InnerExprAST(ExprAST *e1){
    _v.push_back(e1);
}
InnerExprAST::InnerExprAST(ExprAST *e1, ExprAST *e2){
    _v.push_back(e1);
    _v.push_back(e2); 
}
InnerExprAST::InnerExprAST(ExprAST *e1, ExprAST *e2, ExprAST *e3){
    _v.push_back(e1);
    _v.push_back(e2);
    _v.push_back(e3);
}
InnerExprAST::InnerExprAST(ExprAST *e1, ExprAST *e2, ExprAST *e3, ExprAST *e4){
    _v.push_back(e1);
    _v.push_back(e2);
    _v.push_back(e3);
    _v.push_back(e4);
}

ExprAST* NumberExprAST::compile3ac() const{
    return new NumberExprAST(_value);
}
std::string NumberExprAST::print() const{
    return std::to_string(_value);
}

ExprAST* VariableExprAST::compile3ac() const{
    return new VariableExprAST(_name);
}

std::string VariableExprAST::print() const{
    return _name;
}

ExprAST* AddExprAST::compile3ac() const{
     ExprAST* res1 = _v[0]->compile3ac();
     ExprAST* res2 = _v[1]->compile3ac();
     
     int temp = tempNum++;
     std::string tempName = "t" + std::to_string(temp);
     
     OutFile << tempName << " := " ;
     OutFile << res1->print() << " + " << res2->print() << std::endl;
     
     delete res1;
     delete res2;
     
     return new VariableExprAST(tempName);
}

std::string AddExprAST::print() const{
    return _v[0]->print() + " + " + _v[1]->print();
}

ExprAST* SubExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    ExprAST* res2 = _v[1]->compile3ac();
    
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << " - " << res2->print() << std::endl;
    
    delete res1;
    delete res2;
     
    return new VariableExprAST(tempName);
}
 
std::string SubExprAST::print() const{
    return _v[0]->print() + " - " + _v[1]->print();
}

ExprAST* MulExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    ExprAST* res2 = _v[1]->compile3ac();
    
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
     
    OutFile << tempName << " := " ;
    OutFile << res1->print() << " * " << res2->print() << std::endl;
     
    delete res1;
    delete res2;
     
    return new VariableExprAST(tempName);
}

std::string MulExprAST::print() const{
    return _v[0]->print() + " * " + _v[1]->print();
}

ExprAST* DivExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    ExprAST* res2 = _v[1]->compile3ac();
    
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << " / " << res2->print() << std::endl;
     
    delete res1;
    delete res2;
    
    return new VariableExprAST(tempName);      
}

std::string DivExprAST::print() const{
    return _v[0]->print() + " / " + _v[1]->print();
}

ExprAST* ModExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    ExprAST* res2 = _v[1]->compile3ac();
    
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << " % " << res2->print() << std::endl;
     
    delete res1;
    delete res2;
    
    return new VariableExprAST(tempName);      
}

std::string ModExprAST::print() const{
    return _v[0]->print() + " % " + _v[1]->print();
}

ExprAST* UMinusExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << "- " << res1->print() << std::endl;
     
    delete res1;
    
    return new VariableExprAST(tempName);      
}

std::string UMinusExprAST::print() const{
    return "- " + _v[0]->print() ;
}

ExprAST* IncrExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << "++" << std::endl;
     
    delete res1;
    
    return new VariableExprAST(tempName);      
}

std::string IncrExprAST::print() const{
    return _v[0]->print() + "++" ;
}

ExprAST* DecrExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << "--" <<std::endl;
     
    delete res1;
    
    return new VariableExprAST(tempName);      
}

std::string DecrExprAST::print() const{
    return _v[0]->print() + "--" ;
}

ExprAST* LtExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    ExprAST* res2 = _v[1]->compile3ac();
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << " < " << res2->print() << std::endl;
     
    delete res1;
    delete res2;
    
    return new VariableExprAST(tempName);
}
std::string LtExprAST::print() const{
    return _v[0]->print() + " < " + _v[1]->print();
}

ExprAST* LtEqExprAST::compile3ac() const{
    std::cout << _v[0]->print() <<std::endl;
    ExprAST* res1 = _v[0]->compile3ac();
    ExprAST* res2 = _v[1]->compile3ac();
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << " <= " << res2->print() << std::endl;
     
    delete res1;
    delete res2;
    
    return new VariableExprAST(tempName);
}
std::string LtEqExprAST::print() const{
    return _v[0]->print() + " <= " + _v[1]->print();
}
ExprAST* GtExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    ExprAST* res2 = _v[1]->compile3ac();
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << " > " << res2->print() << std::endl;
     
    delete res1;
    delete res2;
    
    return new VariableExprAST(tempName);
}
std::string GtExprAST::print() const{
    return _v[0]->print() + " > " + _v[1]->print();
}

ExprAST* GtEqExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    ExprAST* res2 = _v[1]->compile3ac();
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << " >= " << res2->print() << std::endl;
     
    delete res1;
    delete res2;
    
    return new VariableExprAST(tempName);
}
std::string GtEqExprAST::print() const{
    return _v[0]->print() + " >= " + _v[1]->print();
}

ExprAST* EqExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    ExprAST* res2 = _v[1]->compile3ac();
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << " == " << res2->print() << std::endl;
     
    delete res1;
    delete res2;
    
    return new VariableExprAST(tempName);
}
std::string EqExprAST::print() const{
    return _v[0]->print() + " == " + _v[1]->print();
}
ExprAST* NEqExprAST::compile3ac() const{
    ExprAST* res1 = _v[0]->compile3ac();
    ExprAST* res2 = _v[1]->compile3ac();
    int temp = tempNum++;
    std::string tempName = "t" + std::to_string(temp);
    
    OutFile << tempName << " := " ;
    OutFile << res1->print() << " != " << res2->print() << std::endl;
     
    delete res1;
    delete res2;
    
    return new VariableExprAST(tempName);
}
std::string NEqExprAST::print() const{
    return _v[0]->print() + " != " + _v[1]->print();
}

ExprAST* AssignExprAST::compile3ac() const{
    ExprAST* res = _v[0]->compile3ac();
    OutFile << _name << " := "<< res->print() << std::endl;
    delete res;

    return nullptr;
}
std::string AssignExprAST::print() const{
    return _name + " := " + _v[0]->print();
}

ExprAST* IfExprAST::compile3ac() const{
    int lblAfter = ++label;
    ExprAST* cond = _v[0]->compile3ac();
    
    OutFile << "ifFalse " << cond->print() << " goto L" << lblAfter << std::endl;
    
    _v[1]->compile3ac();
    
    OutFile << "L" << lblAfter << std::endl;
    return nullptr;
}

std::string IfExprAST::print() const{
    return "if(" + _v[0]->print() + "){\n" + _v[1]->print() + "\n}";
}

ExprAST* IfElseExprAST::compile3ac() const{
    int lblElse = ++label;
    int lblIf = ++label;
        
    ExprAST* cond = _v[0]->compile3ac();
    
    OutFile << "ifFalse " << cond->print() << " goto L" << lblElse << std::endl;
    
    _v[1]->compile3ac();
    
    OutFile << "goto L" << lblIf<< std::endl;    
    
    OutFile << "L" << lblElse << std::endl;
        
    _v[2]->compile3ac();
    
    OutFile << "L" << lblIf << std::endl;
    
    return nullptr;
}

std::string IfElseExprAST::print() const{
    return "if(" + _v[0]->print() + "){\n" + _v[1]->print() + "\n}else{\n" + _v[2]->print() + "\n}";
}

ExprAST* WhileExprAST::compile3ac() const{
    int lblBefore = ++label;
    int lblAfter = ++label;
    
    OutFile << "L" << lblBefore << std::endl;
    
    ExprAST* cond = _v[0]->compile3ac();
    
    OutFile << "ifFalse " << cond->print() << " goto L" << lblAfter << std::endl;
    
    _v[1]->compile3ac();
    
    OutFile << "goto L" << lblBefore << std::endl;
    
    OutFile << "L" << lblAfter << std::endl;
    
    return nullptr;
}

std::string WhileExprAST::print() const{
    return "while(" + _v[0]->print() + "){\n" + _v[1]->print() + "\n}";
}

ExprAST* ForExprAST::compile3ac() const{
    int lblBefore = ++label;
    int lblAfter = ++label;
    
    _v[0]->compile3ac();
    
    OutFile << "L" << lblBefore << std::endl;
    
    ExprAST* cond = _v[1]->compile3ac();
    
    OutFile << "ifFalse " << cond->print() << " goto L" << lblAfter << std::endl;
    
    _v[3]->compile3ac();
    
    _v[2]->compile3ac();
    
    OutFile << "goto L" << lblBefore << std::endl;
    
    OutFile << "L" << lblAfter << std::endl;
    
    return nullptr;
}

std::string ForExprAST::print() const{
    return "for(" + _v[0]->print() + ";" + _v[1]->print() + ";" + _v[2]->print() + "){\n" + _v[3]->print() + "\n}";
}

ExprAST* Block::compile3ac() const{
    for (unsigned i = 0; i < _v.size(); i++){
        _v[i]->compile3ac(); 
    }
    return nullptr;
}

std::string Block::print() const{
    std::string s = "";
    for (unsigned i = 0; i < _v.size(); i++){
        s += _v[i]->print(); 
    }
    return s;
}

void Block::addExpr(ExprAST* e){
    _v.push_back(e);
}

