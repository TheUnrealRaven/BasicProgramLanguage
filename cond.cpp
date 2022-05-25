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
      if(expression != nullptr && instr != nullptr)
      {
            delete expression;
            delete instr;
      } 
}
Instruction* IfElseCondition::copy() 
{
      return new IfElseCondition(*this);
}
void IfElseCondition::run() const 
{
      if(expression->value() != 0)
            instr->run();
}
IfElseCondition& IfElseCondition::operator=(const IfElseCondition& op)
{
      if(this != &op)
      {
            delete expression;
            delete instr;
            
            this->expression = op.expression->copy();
            this->instr = op.instr->copy();
      }
      
      return *this;
}
IfElseCondition::IfElseCondition(const IfElseCondition *con)
{
      this->expression = con->expression->copy();
      this->instr = con->instr->copy();
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
