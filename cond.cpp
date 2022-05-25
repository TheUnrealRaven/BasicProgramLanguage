#ifndef __COND__
#define __COND__


#include <iostream>
#include "cond.hpp"

using namespace std;

 void PrintStrings::run() const
 {
      cout << str->value() << endl;
 }
Instruction* PrintStrings::copy()
{
      return new PrintStrings(*this);
}
PrintStrings::~PrintStrings()
{
      if(str != nullptr)
            delete str; 
}



IfElseCondition::~IfElseCondition()
{
      if(expression != nullptr && _instr1 != nullptr && _instr2 != nullptr)
      {
            delete expression;
            delete _instr1;
            delete _instr2;
      } 
}
Instruction* IfElseCondition::copy() 
{
      return new IfElseCondition(*this);
}
void IfElseCondition::run() const 
{
      if(expression->value() != 0)
            _instr1->run();
      else
            _instr2->run();
}
IfElseCondition& IfElseCondition::operator=(const IfElseCondition& op)
{
      if(this != &op)
      {
            delete expression;
            delete _instr1;
            delete _instr2;
            
            this->expression = op.expression->copy();
            this->_instr1 = op._instr1->copy();
            this->_instr2 = op._instr2->copy();
      }
      
      return *this;
}
IfElseCondition::IfElseCondition(const IfElseCondition *con)
{
      this->expression = con->expression->copy();
      this->_instr1 = con->_instr1->copy();
      this->_instr2 = con->_instr2->copy();
}

Instruction* WhileCondition::copy()
{
      return new WhileCondition(*this);
}

void WhileCondition::run() const 
{
      while(expression->value())
      {
            auto begin = instructions->begin();
            auto end = instructions->end();
            
            while(begin != end)
            {
                  (*begin)->run();
                  begin++;
            }     
      }
}



WhileCondition::~WhileCondition()
{
      
      auto begin = instructions->begin();
      auto end = instructions->end();
      
      while(begin != end)
      {
            delete (*begin);
            begin++;
      }
      delete instructions;
      
}



#endif
