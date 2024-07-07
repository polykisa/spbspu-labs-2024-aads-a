#include "calculatePostfix.hpp"
#include <iostream>
#include <limits>
#include "stack.hpp"

long long int baranov::calculatePostfix(Queue< Token > & exp)
{
  Stack< Token > stack;
  while (!exp.empty())
  {
    Token t = exp.front();
    exp.pop();
    if (t.type == TokenType::OPERAND)
    {
      stack.push(t);
    }
    else if (t.type == TokenType::OPERATION)
    {
      if (stack.size() < 2)
      {
        throw std::logic_error("Invalit postfix expression");
      }
      long long int a = stack.top().value.operand.value;
      stack.pop();
      long long int b = stack.top().value.operand.value;
      long long int result = 0;

      switch (t.value.operation.type)
      {
        case OperationType::ADDITION:
          result = sum(b, a);
          break;
        case OperationType::SUBTRACTION:
          result = sum(b, -a);
          break;
        case OperationType::MULTIPLICATION:
          result = multiply(b, a);
          break;
        case OperationType::DIVISION:
          result = devide(b, a);
          break;
      }
      stack.top().value.operand.value = result;
    }
    else
    {
      throw std::logic_error("Invalid postfix expression");
    }
  }
  if (stack.size() != 1 || stack.top().type != TokenType::OPERAND)
  {
    throw std::logic_error("Invalid postfix expression");
  }
  return stack.top().value.operand.value;
}

long long int baranov::sum(long long int a, long long int b) {
  const long long int max = std::numeric_limits< long long int >::max();
  const long long int min = std::numeric_limits< long long int >::min();
  if (same_sign(a, b) && (a > 0)) {
    if (max - a >= b) {
      return a + b;
    }
  }
  else if (same_sign(a, b) && (a < 0)) {
    if (min - a <= b) {
      return a + b;
    }
  }
  else if (!same_sign(a, b)) {
    return a + b;
  }
  throw std::overflow_error("Addition overflow");
}

long long int baranov::multiply(long long int a, long long int b)
{
  long long int result = a * b;
  if (b != 0 && result / b != a)
  {
    throw std::overflow_error("Mulptiplication overflow");
  }
  return result;
}

long long int baranov::devide(long long int a, long long int b)
{
  long long int min = std::numeric_limits< long long int >::min();
  if (b == 0)
  {
    throw std::logic_error("Division by zero");
  }
  else if (a == min && b == -1)
  {
    throw std::overflow_error("Division overflow");
  }
  return a / b;
}

int baranov::sign(long long int val) {
  return (val > 0) ? 1 : ((val < 0) ? -1 : 0);
}

bool baranov::same_sign(long long int a, long long int b) {
  return sign(a) * sign(b) > 0;
}

