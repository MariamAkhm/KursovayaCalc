#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>


struct Token
{
    char kind;
    double value;
};

struct Expression
{
    std::stack<Token> numbers;
    std::stack<Token> operations;
};

int getRang(char expressionElement)
{
    if (expressionElement == '+' ||  expressionElement == '-')
    {
        return 2;
    }
    if (expressionElement == '*' || expressionElement == '/')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Expression calculateSubExpression(Expression expresion)
{
    std::stack<Token> numbers = expresion.numbers;
    std::stack<Token> operations = expresion.operations;
    Token item;

    double leftOperand, rightOperand, operationResult;
    leftOperand = numbers.top().value;
    numbers.pop();

    char currentOperationType = operations.top().kind;
    switch (currentOperationType) 
    {
    case '+':
        rightOperand = numbers.top().value;
        numbers.pop();
        operationResult = leftOperand + rightOperand;
        item.kind = '0';
        item.value = operationResult;
        numbers.push(item);
        operations.pop();
        break;
    case '-':
        rightOperand = numbers.top().value;
        numbers.pop();
        operationResult = rightOperand - leftOperand;
        item.kind = '0';
        item.value = operationResult;
        numbers.push(item);
        operations.pop();
        break;
    case '*':
        rightOperand = numbers.top().value;
        numbers.pop();
        operationResult = leftOperand * rightOperand;
        item.kind = '0';
        item.value = operationResult;
        numbers.push(item);
        operations.pop();
        break;
    case '/':
        rightOperand = numbers.top().value;
        if (leftOperand == 0)
        {
            throw std::exception("На 0 делить нельзя");
        }
        else
        {
            numbers.pop();
            operationResult = (rightOperand / leftOperand);
            item.kind = '0';
            item.value = operationResult;
            numbers.push(item);
            operations.pop();
            break;
        }

    default:
        throw std::exception("Неподдерживаемая операция: " + operations.top().kind);
    }

    Expression answer;
    answer.numbers = numbers;
    answer.operations = operations;

    return answer;
}



double calculate(std::string str)
{
    std::stringstream sstr{ str };

    char currentExpressionElement;
    bool minusFlag = true;
    std::stack<Token> numbers;
    std::stack<Token> operations;
    Token item;
    while (true)
    {
        currentExpressionElement = sstr.peek();
        if (currentExpressionElement == '\377')
        {
            break;
        }
        if (currentExpressionElement == ' ')
        {
            sstr.ignore();
            continue;
        }
        if (currentExpressionElement >= '0' && currentExpressionElement <= '9'
          ||  currentExpressionElement == '-' && minusFlag == 1)
        {
            sstr >> item.value;
            item.kind = '0';
            numbers.push(item);
            minusFlag = 0;
            continue;
        }
        if (currentExpressionElement == '+' || currentExpressionElement == '-' && minusFlag == 0
           || currentExpressionElement == '*' || currentExpressionElement == '/')
        {
            if (operations.size() == 0)
            {
                item.kind = currentExpressionElement;
                item.value = 0;
                operations.push(item);
                sstr.ignore();
                continue;
            }
            if (operations.size() != 0 && getRang(currentExpressionElement) > getRang(operations.top().kind))
            {
                item.kind = currentExpressionElement;
                item.value = 0;
                operations.push(item);
                sstr.ignore();
                continue;
            }
            if (operations.size() != 0 && getRang(currentExpressionElement) <= getRang(operations.top().kind))
            {
                Expression expression;
                expression.numbers = numbers;
                expression.operations = operations;

                Expression newExpression = calculateSubExpression(expression);
                numbers = newExpression.numbers;
                operations = newExpression.operations;
                continue;
            }
        }
        if (currentExpressionElement == '(')
        {
            item.kind = currentExpressionElement;
            item.value = 0;
            operations.push(item);
            sstr.ignore();
            continue;
        }
        if (currentExpressionElement == ')')
        {
            while (operations.top().kind != '(')
            {
                Expression expression;
                expression.numbers = numbers;
                expression.operations = operations;
                    Expression newExpression = calculateSubExpression(expression);
                numbers = newExpression.numbers;
                operations = newExpression.operations;
                continue; 
            }
            operations.pop();
            sstr.ignore();
            continue;
        }
        else
        {
            throw std::exception("Неверно введено выражение");
        }
    }

    while (!operations.empty())
    {
        Expression expression;
        expression.numbers = numbers;
        expression.operations = operations;

        Expression newExpression = calculateSubExpression(expression);
        numbers = newExpression.numbers;
        operations = newExpression.operations;
    }

    return numbers.top().value;
}

int main()
{
    setlocale(LC_ALL, "rus");
    std::string str;
    std::getline(std::cin, str);

    try
    {
        double answer = calculate(str);
        std::cout << answer;
    }
    catch (std::exception err)
    {
        std::cout << err.what() << std::endl;
    }

    return 0;
}