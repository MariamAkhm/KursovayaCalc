#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>


struct Leksema
{
    char type;
    double value;
};

struct Expression
{
    std::stack<Leksema> numbers;
    std::stack<Leksema> operations;
};

int getRang(char expressionElement)
{
    if (expressionElement == 's' ||  expressionElement == 'c' ||  expressionElement == 't' || expressionElement == 'g' || expressionElement == 'e')
    {
        return 4;
    }
    if (expressionElement == '^')
    {
        return 3;
    }
    if (expressionElement == '+' ||  expressionElement == '-')
    {
        return 1;
    }
    if (expressionElement == '*' || expressionElement == '/')
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

Expression calculateSubExpression(Expression expresion)
{
    std::stack<Leksema> numbers = expresion.numbers;
    std::stack<Leksema> operations = expresion.operations;
    Leksema item;

    double leftOperand, rightOperand, operationResult;
    leftOperand = numbers.top().value;
    numbers.pop();

    char currentOperationType = operations.top().type;
    switch (currentOperationType)
    {
    case '+':
        rightOperand = numbers.top().value;
        numbers.pop();
        operationResult = leftOperand + rightOperand;
        item.type = '0';
        item.value = operationResult;
        numbers.push(item);
        operations.pop();
        break;
    case '-':
        rightOperand = numbers.top().value;
        numbers.pop();
        operationResult = rightOperand - leftOperand;
        item.type = '0';
        item.value = operationResult;
        numbers.push(item);
        operations.pop();
        break;
    case '^':
        rightOperand = numbers.top().value;
        numbers.pop();
        operationResult = pow(rightOperand, leftOperand);
        item.type = '0';
        item.value = operationResult;
        numbers.push(item);
        operations.pop();
        break;
    case '*':
        rightOperand = numbers.top().value;
        numbers.pop();
        operationResult = leftOperand * rightOperand;
        item.type = '0';
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
            item.type = '0';
            item.value = operationResult;
            numbers.push(item);
            operations.pop();
            break;
        }

    default:
        throw std::exception("Неподдерживаемая операция: " + operations.top().type);
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
    std::stack<Leksema> numbers;
    std::stack<Leksema> operations;
    Leksema item;
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
        if (currentExpressionElement == 's' || currentExpressionElement == 'c' || currentExpressionElement == 't'
              ||  currentExpressionElement == 'e')
            {
                char foo[3];
                for (int i = 0; i < 3; i++)
                {
                    currentExpressionElement = sstr.peek();
                    foo[i] = currentExpressionElement;
                    sstr.ignore();
                }
                if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n')
                {
                    item.type = 's';
                    item.value = 0;
                    operations.push(item);
                    continue;
                }
                if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's')
                {
                    item.type = 'c';
                    item.value = 0;
                    operations.push(item);
                    continue;
                }
                if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n')
                {
                    item.type = 't';
                    item.value = 0;
                    operations.push(item);
                    continue;
                }
                if (foo[0] == 'c' && foo[1] == 't' && foo[2] == 'g')
                {
                    item.type = 'g';
                    item.value = 0;
                    operations.push(item);
                    continue;
                }
                if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p')
                {
                    item.type = 'e';
                    item.value = 0;
                    operations.push(item);
                    continue;
                }
            }
        if (currentExpressionElement == 'p')
        {
            item.type = '0';
            const double Pi = acos(-1);
            item.value = Pi;
            numbers.push(item);
            minusFlag = 0;
            sstr.ignore();
            continue;
        }
        if (currentExpressionElement >= '0' && currentExpressionElement <= '9'
          ||  currentExpressionElement == '-' && minusFlag == 1)
        {
            sstr >> item.value;
            item.type = '0';
            numbers.push(item);
            minusFlag = 0;
            continue;
        }
        if (currentExpressionElement == '+' || currentExpressionElement == '-' && minusFlag == 0
           || currentExpressionElement == '*' || currentExpressionElement == '/' || currentExpressionElement == '^')
        {
            if (operations.size() == 0)
            {
                item.type = currentExpressionElement;
                item.value = 0;
                operations.push(item);
                sstr.ignore();
                continue;
            }
            if (operations.size() != 0 && getRang(currentExpressionElement) > getRang(operations.top().type))
            {
                item.type = currentExpressionElement;
                item.value = 0;
                operations.push(item);
                sstr.ignore();
                continue;
            }
            if (operations.size() != 0 && getRang(currentExpressionElement) <= getRang(operations.top().type))
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
            item.type = currentExpressionElement;
            item.value = 0;
            operations.push(item);
            sstr.ignore();
            continue;
        }
        if (currentExpressionElement == ')')
        {
            while (operations.top().type != '(')
            {
                Expression expression;
                expression.numbers = numbers;
                expression.operations = operations;
                    Expression newExpression = calculateSubExpression(expression);
                numbers = newExpression.numbers;
                operations = newExpression.operations;
                continue; //Если все хорошо
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