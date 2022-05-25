#include <iostream>

#include "ast.hpp"
using namespace std;

void error(std::string s)
{
      std::cout << "Error: " << s << std::endl;
      exit(EXIT_FAILURE);
}

using namespace std;


int Constant::value() const 
{
      return _val;
}

Expr* Constant::copy() const
{
      return new Constant(*this);
}

BinOp::~BinOp()
{
   if(lhs != nullptr && rhs != nullptr)
   {
      delete lhs;
      delete rhs;
   }
   
}

BinOp::BinOp(const BinOp& tmp)
{    
    cout << "Copy ctor\n"; 
    if(this != &tmp)
    {
      lhs = tmp.lhs->copy();
      rhs = tmp.rhs->copy();
    }
}    

BinOp& BinOp::operator=(const BinOp& tmp)
{
      if(this != &tmp)
      {
         delete lhs;
         delete rhs;
         
         lhs = tmp.lhs->copy();
         rhs = tmp.rhs->copy();
      }      
      return *this;
}

 int AddExprAst::value() const 
 {
      return lhs->value() + rhs->value();
 }
 
 Expr* AddExprAst::copy() const
 {
      return new AddExprAst(*this);
 }
 

BinOp::BinOp(BinOp&& tmp) noexcept
{
      cout << "Move ctro" << endl;
      lhs = std::move(tmp.lhs->copy());
      rhs = std::move(tmp.rhs->copy());
}

BinOp& BinOp::operator=(BinOp&& tmp) noexcept
{
      // I am not shure that this function can be called ever
      cout << "Move assignment" << endl;
      if(this != &tmp)
      {
            delete lhs;
            delete rhs;
            
            lhs = tmp.lhs;
            rhs = tmp.rhs;
            
            tmp.lhs = nullptr;
            tmp.rhs = nullptr;
      }
      return *this;
}



int SubExprAst::value() const
{
      return lhs->value() - rhs->value();
}

Expr* SubExprAst::copy() const
{
      return new SubExprAst(*this);
}

int UnaryMinusAst::value() const 
{
     return -_expr->value();
}
Expr* UnaryMinusAst::copy() const 
{
      return new UnaryMinusAst(*this);
}



int MulExprAst::value() const
{
      return lhs->value() * rhs->value();
}
Expr* MulExprAst::copy() const
{
      return new MulExprAst(*this);
}

int DivExprAst::value() const
{
      if(rhs->value() == 0)
            error("Argument has  value zero\n");
      
      return lhs->value() / rhs->value();
}
Expr* DivExprAst::copy() const
{
      return new DivExprAst(*this);
}


OneOperandAst::OneOperandAst(const OneOperandAst& tmp)
{
      if(this != &tmp)
      {
         _expr = tmp._expr->copy();
      }
}
OneOperandAst::OneOperandAst(OneOperandAst&& tmp)
{
      if(this != &tmp)
            _expr = std::move(tmp._expr->copy());
}
            
OneOperandAst& OneOperandAst::operator=(const OneOperandAst& tmp)
{
      if(this != &tmp)
      {
          delete _expr;
          _expr = tmp._expr->copy();
      }
      return *this;
}
OneOperandAst& OneOperandAst::operator=(OneOperandAst&& tmp)
{
      if(this != &tmp)
      {
          delete _expr;
          _expr = std::move(tmp._expr->copy());
      }
      return *this;
}
            
OneOperandAst::~OneOperandAst()
{
      delete _expr;
}

int IncExprAst::value() const 
{
      int value = _expr->value();
      return ++value;
}
Expr* IncExprAst::copy() const
{
     return new IncExprAst(*this);
}

int DecExprAst::value() const 
{
      int value = _expr->value();
      return --value;
} 

Expr* DecExprAst::copy() const
{
      return new DecExprAst(*this);
}


int EqualAstExpr::value() const 
{
      return lhs->value() == rhs->value();
}
Expr* EqualAstExpr::copy() const
{
      return new EqualAstExpr(*this);
}

int NeEqualExpr::value() const 
{
      return !(lhs->value() == rhs->value());
}
Expr* NeEqualExpr::copy() const
{
      return new NeEqualExpr(*this);
}


int LessEqualExprAst::value() const 
{
      return lhs->value() <= rhs->value();
}
Expr* LessEqualExprAst::copy() const
{
      return new LessEqualExprAst(*this);
}

int GreaterEqualExprAst::value() const 
{
      return  lhs->value() >= rhs->value();
}
Expr* GreaterEqualExprAst::copy() const
{
      return new GreaterEqualExprAst(*this);
}
            
            
int LessExprAst::value() const
{
      return lhs->value() < rhs->value();
}      
Expr* LessExprAst::copy() const
{
      return new LessExprAst(*this);
}

int GreaterExprAst::value() const
{
      return lhs->value() > rhs->value();
}
Expr* GreaterExprAst::copy() const 
{
      return new GreaterExprAst(*this);
}

int ModExprAst::value() const
{
      return lhs->value() % rhs->value();
}
Expr* ModExprAst::copy() const
{
      return new ModExprAst(*this);
}

std::string StrConstant::value() const 
{
      return _value;
}
ExprStr* StrConstant::copy() const
{
      return new StrConstant(*this);
}

BinOpStr::~BinOpStr()
{
      if(_left != nullptr && _right != nullptr)
      {
            delete _left;
            delete _right;
      }
     
}     

std::string StrAddAst::value() const
{
      return _left->value() + _right->value();
}
ExprStr* StrAddAst::copy() const
{
      return new StrAddAst(*this);
}

std::string StrMulAst::value() const
{
      if(_mul <= 0 && _left == nullptr)
            return _right->value();
      else if(_mul <= 0 && _right == nullptr)
            return _left->value();
      else
            return calculate();
}
 
std::string StrMulAst::calculate() const
{
     std::string tmp = _indicator == false ? _right->value() : _left->value();
     std::string returnstr = "";
     for(int i=0; i<_mul; i++)
            returnstr += tmp;
     return returnstr;
}
ExprStr* StrMulAst::copy() const
{
      return new StrMulAst(*this);
}


      







