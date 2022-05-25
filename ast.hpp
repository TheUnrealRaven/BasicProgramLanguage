#ifndef __AST__
#define __AST__1

class Expr
{
   public:
      virtual int value() const = 0;
      virtual Expr* copy() const = 0;
      virtual ~Expr() { }
   
   private:
};

class ExprStr
{
      public:
            virtual std::string value() const = 0;
            virtual ExprStr* copy() const = 0;
            virtual ~ExprStr() {}
};
   

class StrConstant: public ExprStr
{
      public:
            StrConstant(std::string tmp)
            :_value(std::move(tmp)) {}
            
            virtual std::string value() const override;
            virtual ExprStr* copy() const override;
      private:
            std::string _value;
};

class BinOpStr: public ExprStr
{
      public:
            BinOpStr(ExprStr *l, ExprStr *r)
            :_left(l), _right(r) {}
            
            //todo move/copy assignemnt/constuctor
            
            ~BinOpStr();
      protected:
            ExprStr *_left = nullptr;
            ExprStr *_right = nullptr;
            
};

class StrMulAst: public BinOpStr
{
      public:
            StrMulAst(int mul, ExprStr *r)
            :BinOpStr(nullptr, r), _mul(mul) {}
            StrMulAst(ExprStr *l, int mul)
            :BinOpStr(l, nullptr),_mul(mul) { _indicator = true;}
            StrMulAst(ExprStr *l, ExprStr *r)
            :BinOpStr(l, r) {}
            
            virtual std::string value() const override;
            virtual ExprStr* copy() const override;
            
            
    private:
      int _mul;
      bool _indicator = false;
      std::string calculate() const;
};

class StrAddAst: public BinOpStr
{
      public:
            StrAddAst(ExprStr *l, ExprStr *r)
            :BinOpStr(l, r) {}
            virtual std::string value() const override;
            virtual ExprStr* copy() const override;
            
};

class OneOperandAst: public Expr
{
      public:
            OneOperandAst(Expr* expr)
            :_expr(expr)
            {}
            
            OneOperandAst(const OneOperandAst& tmp);
            OneOperandAst(OneOperandAst&& tmp);
            
            OneOperandAst& operator=(const OneOperandAst& tmp);
            OneOperandAst& operator=(OneOperandAst&& tmp);
            
            ~OneOperandAst();
            
      protected:
            Expr *_expr;
};

class UnaryMinusAst:public OneOperandAst
{
      public:
            UnaryMinusAst(Expr* expr)
            :OneOperandAst(expr) {}
            
            virtual int value() const override;
            virtual Expr* copy() const override;
             

};


class BinOp: public Expr
{     
      public:
       BinOp(Expr *first, Expr *second)
       :lhs(first), rhs(second)
       {}
         
       BinOp(const BinOp& tmp);
       BinOp& operator=(const BinOp& tmp);
       BinOp(BinOp&&) noexcept;
       BinOp& operator=(BinOp&&) noexcept;
       
      
      ~BinOp();
      protected:
            Expr *lhs;
            Expr *rhs;
};


class Constant: public Expr
{
    public:
      Constant(int x)
      :_val(x)
      {}
      
      virtual int value() const override;
      
      virtual Expr* copy() const override;
      
   private:
      int _val;

};



class AddExprAst: public BinOp
{
   public:
      AddExprAst(Expr *l, Expr *r)
      :BinOp(l, r) {}
      virtual int value() const override;
      virtual Expr *copy() const override;

};

class SubExprAst: public BinOp
{
      public:
            SubExprAst(Expr *l, Expr *r)
            :BinOp(l, r) {}
            virtual int value() const override;
            virtual Expr* copy() const override;
};

class MulExprAst: public BinOp
{
      public:
            MulExprAst(Expr *l, Expr *r)
            :BinOp(l, r) {}
            
            virtual int value() const override;
            virtual Expr* copy() const override;
};

class DivExprAst: public BinOp
{
      public:
            DivExprAst(Expr *l, Expr *r)
            :BinOp(l, r) { }
            
            virtual int value() const override;
            virtual Expr* copy() const override;
};

class ModExprAst: public BinOp
{
      public:
            ModExprAst(Expr *l, Expr *r)
            :BinOp(l, r) {}
            
            virtual int value() const override;
            virtual Expr* copy() const override;
};



class IncExprAst: public OneOperandAst
{
      public:
            IncExprAst(Expr *expr)
            :OneOperandAst(expr) {}
            
            virtual int value() const override;
            virtual Expr* copy() const override;
};

class DecExprAst: public OneOperandAst
{
      public:
            DecExprAst(Expr *expr)
            :OneOperandAst(expr)
            {}
            
            virtual int value() const override;
            virtual Expr* copy() const override;
};

class EqualAstExpr: public BinOp
{
      public:
            EqualAstExpr(Expr *l, Expr *r)
            :BinOp(l, r) {}
      
            virtual int value() const override;
            virtual Expr* copy() const override;
};

class NeEqualExpr: public BinOp
{
      public:
             NeEqualExpr(Expr *l, Expr *r)
            :BinOp(l, r) {}
      
            virtual int value() const override;
            virtual Expr* copy() const override;
};

class LessEqualExprAst: public BinOp
{
      public:
            LessEqualExprAst(Expr *l, Expr *r)
            :BinOp(l, r) {}
      
            virtual int value() const override;
            virtual Expr* copy() const override;
};

class GreaterEqualExprAst: public BinOp
{
      public:
            GreaterEqualExprAst(Expr *l, Expr *r)
            :BinOp(l, r) {}
      
            virtual int value() const override;
            virtual Expr* copy() const override;
};

class GreaterExprAst: public BinOp
{
      public:
            GreaterExprAst(Expr *l, Expr *r)
            :BinOp(l, r) {}
            
            virtual int value() const override;
            virtual Expr* copy() const override;

};

class LessExprAst: public BinOp
{
      public:
            LessExprAst(Expr *l, Expr *r)
            :BinOp(l, r) {}
            
            virtual int value() const override;
            virtual Expr* copy() const override;
};


#endif
