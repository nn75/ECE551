#include <sstream>
#include <string>

class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
  long number;

 public:
  NumExpression(long num) : number(num) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << number;
    return ss.str();
  }
};

class opExpression : public Expression
{
  Expression * lhss;
  Expression * rhss;
  const char * op;

 public:
  opExpression(Expression * lhs, Expression * rhs, const char * ope) {
    lhss = lhs;
    rhss = rhs;
    op = ope;
  }
  virtual std::string toString() const {
    std::stringstream ss;
    ss << '(' << lhss->toString() << ' ' << op << ' ' << rhss->toString() << ')';
    return ss.str();
  }
  virtual ~opExpression() {
    delete lhss;
    delete rhss;
  }
};

class PlusExpression : public opExpression
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : opExpression(lhs, rhs, "+") {}
};
