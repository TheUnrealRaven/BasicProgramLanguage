#ifndef __COND__HPP
#define __COND__HPP

#include "ast.hpp"
#include <vector>
using namespace std;


class Instruction 
{
      public:
            virtual void run() const = 0;
            virtual Instruction* copy() = 0;
            virtual ~Instruction() {}
};

class PrintStrings: public Instruction
{
      public:
            PrintStrings(ExprStr* expr)
            :str(expr) {}
            
            virtual void run() const override;
            virtual Instruction* copy() override;
            ~PrintStrings();
            
                 
      private:
            ExprStr* str;
};

class IfElseCondition: public Instruction
{
      public:
            IfElseCondition(Expr *expr,Instruction* instr)
            :expression(expr), instr(instr){}
            
            virtual ~IfElseCondition();
            Instruction* copy() override;
            void run() const override;
            IfElseCondition& operator=(const IfElseCondition& op);
            IfElseCondition(const IfElseCondition *con);
      
      private:
            Expr *expression;
            Instruction *instr;

};

class WhileCondition: public Instruction
{
      public:
            WhileCondition(vector<Instruction*> *instrs, Expr *exression)
            :instructions(instrs), expression(expression) {}
            
            Instruction* copy() override;
            void run() const override;
            
            
            ~WhileCondition();
      
      
      private:
            vector<Instruction*> *instructions;
            Expr *expression;

};

// if else naredba





#endif
