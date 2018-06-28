#include "ExpressionEvaluator.h"

EXPR_EVAL_NM_ENTER

operatorSymbol::operatorSymbol(uint32_t p)
{
}

functionSymbol::functionSymbol(uint32_t c)
{
	argumentCount = c;
}

IElement::IElement()
{
}

IElement::~IElement()
{
}

CValue::CValue(long double value) : m_Value(value) {}

CValue::~CValue()
{
}

long double CValue::getValue(const map<string, long double>& variables)
{
	return m_Value;
}

long double CValue::getValue()
{
	return m_Value;
}

CDynamicFunctionInstance::CDynamicFunctionInstance(CDynamicFunction * parent, vector<IElement*> arguments) :
	m_Parent(parent),
	m_Arguments(arguments)
{
}

CDynamicFunctionInstance::~CDynamicFunctionInstance()
{

}

long double CDynamicFunctionInstance::getValue(const map<string, long double>& variables)
{
	if (m_Parent && m_Parent->m_FunctionExpression)
	{
		if (m_Arguments.size() >= m_Parent->m_ArgumentNames.size())
		{
			map<string, long double> substitution = variables;

			auto names = m_Parent->m_ArgumentNames;

			for (size_t i = 0; i<names.size(); i++)
			{
				substitution[names[i]] = m_Arguments[i]->getValue(variables);
			}

			return m_Parent->m_FunctionExpression->getValue(substitution);
		}
	}
	return 0.0;
}

long double CDynamicFunctionInstance::getValue()
{
	if (m_Parent && m_Parent->m_FunctionExpression)
	{
		if (m_Arguments.size() >= m_Parent->m_ArgumentNames.size())
		{
			map<string, long double> substitution;

			auto names = m_Parent->m_ArgumentNames;

			for (size_t i = 0; i<names.size(); i++)
			{
				substitution[names[i]] = m_Arguments[i]->getValue();
			}

			return m_Parent->m_FunctionExpression->getValue(substitution);
		}
	}
	return 0.0;
}

CVariable::CVariable(string variableName) : m_VariableName(variableName) {}

CVariable::~CVariable()
{
}

long double CVariable::getValue(const map<string, long double>& variables)
{
	if (variables.find(m_VariableName) != variables.end())
	{
		return variables.at(m_VariableName);
	}

	return 0.0;
}

long double CVariable::getValue()
{
	return 0.0;
}

COperator::COperator(string operSignature, IElement * leftOperand, IElement * rightOperand) :
	m_OperatorSignature(operSignature),
	m_LeftOperand(leftOperand),
	m_RightOperand(rightOperand)
{}

COperator::~COperator()
{
}

long double COperator::getValue(const map<string, long double>& variables)
{
	if (m_LeftOperand && m_RightOperand)
	{
		auto a = m_LeftOperand->getValue(variables);
		auto b = m_RightOperand->getValue(variables);

		if (m_OperatorSignature == "+")
		{
			return a + b;
		}

		if (m_OperatorSignature == "-")
		{
			return a - b;
		}

		if (m_OperatorSignature == "*")
		{
			return a * b;
		}

		if (m_OperatorSignature == "/")
		{
			return a / b;
		}

		if (m_OperatorSignature == "^")
		{
			return pow(a, b);
		}

		if (m_OperatorSignature == "==")
		{
			return fabs(a - b) < DBL_EPSILON;
		}

		if (m_OperatorSignature == "!=")
		{
			return fabs(a - b) > DBL_EPSILON;
		}

		if (m_OperatorSignature == "<=")
		{
			return a <= b;
		}

		if (m_OperatorSignature == ">=")
		{
			return a >= b;
		}

		if (m_OperatorSignature == "<")
		{
			return a < b;
		}

		if (m_OperatorSignature == ">")
		{
			return a > b;
		}

		if (m_OperatorSignature == "||")
		{
			return (fabs(a)>DBL_EPSILON) || (fabs(b)>DBL_EPSILON);
		}

		if (m_OperatorSignature == "&&")
		{
			return (fabs(a)>DBL_EPSILON) && (fabs(b)>DBL_EPSILON);
		}

		if (m_OperatorSignature == "%")
		{
			return fmod(a, b);
		}
	}

	return 0.0;
}

long double COperator::getValue()
{
	if (m_LeftOperand && m_RightOperand)
	{
		auto a = m_LeftOperand->getValue();
		auto b = m_RightOperand->getValue();

		if (m_OperatorSignature == "+")
		{
			return a + b;
		}

		if (m_OperatorSignature == "-")
		{
			return a - b;
		}

		if (m_OperatorSignature == "*")
		{
			return a * b;
		}

		if (m_OperatorSignature == "/")
		{
			return a / b;
		}

		if (m_OperatorSignature == "^")
		{
			return pow(a, b);
		}

		if (m_OperatorSignature == "==")
		{
			return fabs(a - b) < DBL_EPSILON;
		}

		if (m_OperatorSignature == "!=")
		{
			return fabs(a - b) > DBL_EPSILON;
		}

		if (m_OperatorSignature == "<=")
		{
			return a <= b;
		}

		if (m_OperatorSignature == ">=")
		{
			return a >= b;
		}

		if (m_OperatorSignature == "<")
		{
			return a < b;
		}

		if (m_OperatorSignature == ">")
		{
			return a > b;
		}

		if (m_OperatorSignature == "||")
		{
			return (fabs(a)>DBL_EPSILON) || (fabs(b)>DBL_EPSILON);
		}

		if (m_OperatorSignature == "&&")
		{
			return (fabs(a)>DBL_EPSILON) && (fabs(b)>DBL_EPSILON);
		}

		if (m_OperatorSignature == "%")
		{
			return fmod(a, b);
		}
	}

	return 0.0;
}

CFunction::CFunction(string functionSignature, vector<IElement*> arguments) :
	m_FunctionSignature(functionSignature),
	m_Arguments(arguments)
{}

CFunction::~CFunction()
{
}

long double CFunction::getValue(const map<string, long double>& variables)
{
	if (m_Arguments.size() >= 1 && m_Arguments[0])
	{
		auto a0 = m_Arguments[0]->getValue(variables);

		if (m_FunctionSignature == "ln")
		{
			return log(a0);
		}

		if (m_FunctionSignature == "exp")
		{
			return exp(a0);
		}

		if (m_FunctionSignature == "sin")
		{
			return sin(a0);
		}

		if (m_FunctionSignature == "cos")
		{
			return cos(a0);
		}

		if (m_FunctionSignature == "tan" || m_FunctionSignature == "tg")
		{
			return tan(a0);
		}

		if (m_FunctionSignature == "ctg")
		{
			return 1.0 / tan(a0);
		}

		if (m_FunctionSignature == "asin")
		{
			return asin(a0);
		}

		if (m_FunctionSignature == "acos")
		{
			return acos(a0);
		}

		if (m_FunctionSignature == "sqrt")
		{
			return sqrt(a0);
		}

		if (m_Arguments.size() >= 2 && m_Arguments[1])
		{
			auto a1 = m_Arguments[1]->getValue(variables);

			if (m_FunctionSignature == "log")
			{
				return log(a1) / log(a0);
			}

			if (m_FunctionSignature == "atan")
			{
				return atan2(a0, a1);
			}

			if (m_FunctionSignature == "pow")
			{
				return pow(a0, a1);
			}

			if (m_FunctionSignature == "mod")
			{
				return fmod(a0, a1);
			}
		}

		if (m_FunctionSignature == "atan")
		{
			return atan(a0);
		}
	}

	return 0.0;
}

long double CFunction::getValue()
{
	if (m_Arguments.size() >= 1 && m_Arguments[0])
	{
		auto a0 = m_Arguments[0]->getValue();

		if (m_FunctionSignature == "ln")
		{
			return log(a0);
		}

		if (m_FunctionSignature == "exp")
		{
			return exp(a0);
		}

		if (m_FunctionSignature == "sin")
		{
			return sin(a0);
		}

		if (m_FunctionSignature == "cos")
		{
			return cos(a0);
		}

		if (m_FunctionSignature == "tan" || m_FunctionSignature == "tg")
		{
			return tan(a0);
		}

		if (m_FunctionSignature == "ctg")
		{
			return 1.0 / tan(a0);
		}

		if (m_FunctionSignature == "asin")
		{
			return asin(a0);
		}

		if (m_FunctionSignature == "acos")
		{
			return acos(a0);
		}

		if (m_FunctionSignature == "sqrt")
		{
			return sqrt(a0);
		}

		if (m_Arguments.size() >= 2 && m_Arguments[1])
		{
			auto a1 = m_Arguments[1]->getValue();

			if (m_FunctionSignature == "log")
			{
				return log(a1) / log(a0);
			}

			if (m_FunctionSignature == "atan")
			{
				return atan2(a0, a1);
			}

			if (m_FunctionSignature == "pow")
			{
				return pow(a0, a1);
			}

			if (m_FunctionSignature == "mod")
			{
				return fmod(a0, a1);
			}
		}

		if (m_FunctionSignature == "atan")
		{
			return atan(a0);
		}
	}

	return 0.0;
}

CDynamicFunction::CDynamicFunction(string functionSignature, vector<string> arguments, IElement * expression)
	:
	m_FunctionSignature(functionSignature),
	m_ArgumentNames(arguments),
	m_FunctionExpression(expression)
{}

CDynamicFunctionInstance * CDynamicFunction::getInstance(vector<IElement*> arguments)
{
	return new CDynamicFunctionInstance(this, arguments);
}

CExpression::CExpression(IElement * rootElement) :
	m_RootElement(rootElement)
{}

long double CExpression::getValue(const map<string, long double>& variables)
{
	if (m_RootElement)
	{
		auto copy = variables;
		copy["pi"] = M_PI;
		copy["e"] = exp(1);

		return m_RootElement->getValue(copy);
	}

	return 0.0;
}

long double CExpression::getValue()
{
	if (m_RootElement)
	{
		map<string, long double> copy;
		copy["pi"] = M_PI;
		copy["e"] = exp(1);

		return m_RootElement->getValue(copy);
	}

	return 0.0;
}

CExpressionEvaluator::CExpressionEvaluator()
{
	m_LastErrorPosition = 0;

	m_Operators["+"] = operatorSymbol(9);
	m_Operators["-"] = operatorSymbol(9);

	m_Operators["*"] = operatorSymbol(10);
	m_Operators["/"] = operatorSymbol(10);
	m_Operators["%"] = operatorSymbol(10);

	m_Operators["^"] = operatorSymbol(11);

	m_Operators["||"] = operatorSymbol(0);
	m_Operators["&&"] = operatorSymbol(1);

	m_Operators["=="] = operatorSymbol(2);
	m_Operators["!="] = operatorSymbol(2);

	m_Operators["<="] = operatorSymbol(3);
	m_Operators[">="] = operatorSymbol(3);

	m_Operators["<"] = operatorSymbol(3);
	m_Operators[">"] = operatorSymbol(3);

	m_Functions["ln"] = functionSymbol(1);
	m_Functions["log"] = functionSymbol(2);
	m_Functions["exp"] = functionSymbol(1);

	m_Functions["sin"] = functionSymbol(1);
	m_Functions["cos"] = functionSymbol(1);

	m_Functions["tg"] = functionSymbol(1);
	m_Functions["ctg"] = functionSymbol(1);

	m_Functions["tan"] = functionSymbol(1);

	m_Functions["asin"] = functionSymbol(1);
	m_Functions["acos"] = functionSymbol(1);

	m_Functions["atan"] = functionSymbol(1);

	m_Functions["sqrt"] = functionSymbol(1);

	m_Functions["pow"] = functionSymbol(2);
	m_Functions["mod"] = functionSymbol(2);
}

CExpression * CExpressionEvaluator::parse(const string & input)
{
	m_LastErrorPosition = 0;
	m_LastErrorString = "";
	m_LastVariableNames.clear();

	auto parseOut = parse(cleanString(input), 0);
	if (!parseOut)
	{
		return nullptr;
	}
	return new CExpression(parseOut);
}

size_t CExpressionEvaluator::getErrorPosition()
{
	return m_LastErrorPosition;
}

string CExpressionEvaluator::getErrorString()
{
	return m_LastErrorString + " at: " + to_string(m_LastErrorPosition);
}

set<string> CExpressionEvaluator::getVariableNames()
{
	return m_LastVariableNames;
}

CDynamicFunction * CExpressionEvaluator::parseFunction(const string & input)
{
	m_LastErrorPosition = 0;
	m_LastErrorString = "";
	m_LastVariableNames.clear();

	auto inputClear = cleanString(input);

	auto equalsPos = inputClear.find('=');
	if (equalsPos == string::npos)
	{
		m_LastErrorPosition = 0;
		m_LastErrorString = "can't find assignment operator in function declaration";
		return nullptr;
	}

	string wholeFunctionDefinition = inputClear.substr(0, equalsPos);

	auto parenthesisStart = wholeFunctionDefinition.find('(');

	string functionSignature = wholeFunctionDefinition.substr(0, parenthesisStart);

	if (functionSignature == "")
	{
		m_LastErrorPosition = 0;
		m_LastErrorString = "can't find function name in function declaration";
		return nullptr;
	}

	vector<string> argumentNames;

	size_t offset = parenthesisStart + 1;

	while (offset + 1 < wholeFunctionDefinition.size())
	{
		auto pos = wholeFunctionDefinition.find(',', offset);
		if (pos != string::npos)
		{
			argumentNames.push_back(wholeFunctionDefinition.substr(offset, pos - offset));
			offset = pos + 1;
			continue;
		}

		pos = wholeFunctionDefinition.find(')', offset);
		if (pos != string::npos)
		{
			argumentNames.push_back(wholeFunctionDefinition.substr(offset, pos - offset));
			offset = pos + 1;
			continue;
		}

		m_LastErrorPosition = equalsPos;
		m_LastErrorString = "no closing parenthesis in function signature";

		return nullptr;
	}

	IElement* expression = parse(inputClear, equalsPos + 1);
	if (!expression)
	{
		return nullptr;
	}

	return new CDynamicFunction(functionSignature, argumentNames, expression);
}

bool CExpressionEvaluator::addDynamicFunction(CDynamicFunction * function)
{
	if (function)
	{
		m_DynamicFunctions[function->m_FunctionSignature] = function;
		return true;
	}

	return false;
}

IElement * CExpressionEvaluator::parse(const string & input, size_t offset)
{
	stack<string> operatorStack;
	//can be changed to reference operand stack
	stack<IElement*> operandStack;

	bool lastIsNumber = false;

	for (size_t i = offset; i < input.size();)
	{
		if (input[i] == ')' || input[i] == ',')
		{
			m_LastErrorPosition = i;
			m_LastErrorString = "unexpected symbol";
			return nullptr;
		}

		auto outOperator = isOperator(input, i);
		auto outFunction = isFunction(input, i);

		if (input[i] == '(')
		{
			auto parenth = parenthesis(input, i);
			if (!parenth)
			{
				return nullptr;
			}
			operandStack.push(parenth);
			lastIsNumber = true;
			continue;
		}

		if (input[i] == '-')
		{
			if (!lastIsNumber)
			{
				operandStack.push(new CValue(-1));

				i++;

				size_t temp = i;

				if (operatorStack.size() != 0 && operatorStack.top() == "^")
				{
					operatorStack.push("*");
				}
				else
				{
					if (!parseOperator(input, temp, "*", operatorStack, operandStack))
					{
						return nullptr;
					}
				}


				lastIsNumber = true;
				continue;
			}
		}

		if (outFunction.first)
		{
			if (!parseFunction(input, i, outFunction.second, operatorStack, operandStack))
			{
				return nullptr;
			}

			auto value = operandStack.top();
			operandStack.pop();
			operandStack.push(value);

			lastIsNumber = true;

			continue;
		}

		if (outOperator.first)
		{
			if (!parseOperator(input, i, outOperator.second, operatorStack, operandStack))
			{
				return nullptr;
			}

			lastIsNumber = false;

			continue;
		}

		if (isNumber(input[i]))
		{
			if (!parseNumber(input, i, operatorStack, operandStack))
			{
				return nullptr;
			}

			auto value = operandStack.top();
			operandStack.pop();
			operandStack.push(value);

			lastIsNumber = true;

			continue;
		}

		auto variable = evaluateVariable(input, i);
		lastIsNumber = true;
		operandStack.push(variable);
	}

	while (operatorStack.size() > 0)
	{
		if (operandStack.size() < 2)
		{
			m_LastErrorPosition = 0;
			m_LastErrorString = "not enough operands";

			return nullptr;
		}

		auto b = operandStack.top();
		operandStack.pop();
		auto a = operandStack.top();
		operandStack.pop();

		operandStack.push(evaluateOperator(operatorStack.top(), a, b));
		operatorStack.pop();
	}

	if (operandStack.size() != 1)
	{
		m_LastErrorPosition = 0;
		m_LastErrorString = "nothing to evaluate";

		return nullptr;
	}

	return operandStack.top();
}

IElement * CExpressionEvaluator::toNumber(const string & input)
{
	stringstream ss(input);
	long double out;
	ss >> out;
	return new CValue(out);
}

IElement * CExpressionEvaluator::evaluateVariable(const string & input, size_t & offset)
{
	string variableName = "";

	for (size_t i = offset; i < input.size(); i++)
	{
		if (!((input[i] >= '0' && input[i] <= '9') || input[i] == '.') && !isOperator(input, i).first && input[i] != ')'&& input[i] != '(' && input[i] != ',')
		{
			variableName += input[i];
		}
		else
		{
			break;
		}
	}

	m_LastVariableNames.insert(variableName);
	offset += variableName.size();

	return new CVariable(toLower(variableName));
}

bool CExpressionEvaluator::parseFunction(const string & input, size_t & offset, const string & function, stack<string>& operatorStack, stack<IElement*>& operandStack)
{
	//skip function name + left parenthesis
	offset += function.size() + 1;
	auto arguments = functionArgs(input, offset);
	operandStack.push(evaluateFunction(function, arguments));
	return true;
}

bool CExpressionEvaluator::parseNumber(const string & input, size_t & offset, stack<string>& operatorStack, stack<IElement*>& operandStack)
{
	bool decimalSeparator = false;
	bool scientific = false;

	size_t end = 0;

	if (input[offset] == '-')
	{
		offset++;
	}

	for (size_t i = offset; i < input.size(); i++)
	{
		if ((input[i] >= '0') && (input[i] <= '9'))
		{
			end = i;
		}
		else if (!decimalSeparator && input[i] == '.')
		{
			end = i;
			decimalSeparator = true;
		}
		else if (!scientific && input[i] == 'e')
		{
			end = i;
			scientific = true;
		}
		else if (i != 0 && input[i - 1] == 'e' && input[i] == '-')
		{
			end = i;
		}
		else if (decimalSeparator && input[i] == '.')
		{
			m_LastErrorPosition = i;
			m_LastErrorString = "double decimal place";
			return false;
		}
		else if (scientific && input[i] == 'e')
		{
			m_LastErrorPosition = i;
			m_LastErrorString = "double scientific notation";
			return false;
		}
		else
		{
			break;
		}
	}

	string number = input.substr(offset, end - offset + 1);

	if (number[number.size() - 1] == 'e')
	{
		number.pop_back();
	}

	operandStack.push(toNumber(number));

	offset = end + 1;

	return true;
}

bool CExpressionEvaluator::parseOperator(const string & input, size_t & offset, const string & oper, stack<string>& operatorStack, stack<IElement*>& operandStack)
{
	//skip operator

	offset += oper.size();

	if (operatorStack.size() == 0)
	{
		operatorStack.push(oper);
	}
	else if (hasHigherPriority(oper, operatorStack.top()))
	{
		operatorStack.push(oper);
	}
	else
	{
		while (operatorStack.size() > 0 && hasHigherPriority(operatorStack.top(), oper))
		{
			if (operandStack.size() < 2)
			{
				m_LastErrorPosition = offset;
				m_LastErrorString = "not enough operands";

				return false;
			}

			auto b = operandStack.top();
			operandStack.pop();
			auto a = operandStack.top();
			operandStack.pop();

			operandStack.push(evaluateOperator(operatorStack.top(), a, b));
			operatorStack.pop();
		}

		operatorStack.push(oper);
	}

	return true;
}

IElement * CExpressionEvaluator::parenthesis(const string & input, size_t & offset)
{
	size_t end = 0;

	size_t openingParenth = 0;
	size_t closingParenth = 0;

	//first char is left parenthesis
	offset++;

	for (size_t i = offset; i < input.size(); i++)
	{
		if (input[i] == ')')
		{
			closingParenth++;
		}
		else if (input[i] == '(')
		{
			openingParenth++;
		}

		if (closingParenth > openingParenth)
		{
			end = i;
			break;
		}
	}

	string arg = input.substr(offset, end - offset);
	auto out = parse(arg, 0);

	offset = end + 1;

	return out;
}

vector<IElement*> CExpressionEvaluator::functionArgs(const string & input, size_t & offset)
{
	vector<IElement*> arguments;

	bool hitParenthesis = false;

	while (!hitParenthesis)
	{
		arguments.push_back(evaluateArgument(input, offset, hitParenthesis));
		offset++;
	}

	return arguments;
}

IElement * CExpressionEvaluator::evaluateArgument(const string & input, size_t & offset, bool & hitParenthesis)
{
	size_t openingParenth = 0;
	size_t closingParenth = 0;

	for (size_t i = offset; i < input.size(); i++)
	{
		if (input[i] == ',' && openingParenth - closingParenth == 0)
		{
			string arg = input.substr(offset, i - offset);
			auto out = parse(arg, 0);
			offset = i;
			return out;
		}
		else if (input[i] == ')')
		{
			closingParenth++;
		}
		else if (input[i] == '(')
		{
			openingParenth++;
		}

		if (closingParenth > openingParenth)
		{
			hitParenthesis = true;
			string arg = input.substr(offset, i - offset);
			auto out = parse(arg, 0);
			offset = i;
			return out;
		}
	}

	return nullptr;
}

IElement * CExpressionEvaluator::evaluateOperator(string oper, IElement * a, IElement * b)
{
	return new COperator(oper, a, b);
}

IElement * CExpressionEvaluator::evaluateFunction(string function, vector<IElement*> arguments)
{
	for (auto& fn : m_Functions)
	{
		if (fn.first == function && fn.second.argumentCount == arguments.size())
		{
			return new CFunction(function, arguments);
		}
	}

	for (auto& fn : m_DynamicFunctions)
	{
		if (fn.first == function && fn.second && fn.second->m_ArgumentNames.size() == arguments.size())
		{
			return fn.second->getInstance(arguments);
		}
	}

	return nullptr;
}

bool CExpressionEvaluator::hasHigherPriority(string opA, string opB)
{
	return m_Operators[opA].priority > m_Operators[opB].priority;
}

pair<bool, string> CExpressionEvaluator::isOperator(const string & input, size_t offset)
{
	for (auto& oper : m_Operators)
	{
		if (oper.first.size() <= input.size() - offset)
		{
			bool match = true;
			for (size_t i = 0; i < oper.first.size(); i++)
			{
				if (oper.first[i] != input[i + offset])
				{
					match = false;
					break;
				}
			}
			if (match)
			{
				return pair<bool, string>(true, oper.first);
			}
		}
	}

	return pair<bool, string>(false, "");
}

pair<bool, string> CExpressionEvaluator::isFunction(const string & input, size_t offset)
{
	vector<string> matches;

	for (auto& function : m_Functions)
	{
		if (function.first.size() <= input.size() - offset)
		{
			bool match = true;
			for (size_t i = 0; i < function.first.size(); i++)
			{
				if (function.first[i] != input[i + offset])
				{
					match = false;
					break;
				}
			}
			if (match)
			{
				matches.push_back(function.first);
			}
		}
	}

	for (auto& function : m_DynamicFunctions)
	{
		if (function.first.size() <= input.size() - offset)
		{
			bool match = true;
			for (size_t i = 0; i < function.first.size(); i++)
			{
				if (function.first[i] != input[i + offset])
				{
					match = false;
					break;
				}
			}
			if (match)
			{
				matches.push_back(function.first);
			}
		}
	}

	size_t longest = 0;

	if (matches.size() == 0)
	{
		return pair<bool, string>(false, "");
	}

	for (size_t i = 1; i < matches.size(); i++)
	{
		if (matches[i].size() > matches[longest].size())
		{
			longest = i;
		}
	}

	return pair<bool, string>(true, matches[longest]);
}

bool CExpressionEvaluator::isNumber(char a)
{
	return (a >= '0' && a <= '9') || a == '.' || a == 'e' || a == '-';
}

string cleanString(string a)
{
	string out;
	for (auto& c : a)
	{
		if (c != '\n' &&c != ' ' &&c != '\t')
		{
			out += c;
		}
	}
	return out;
}

string toLower(string a)
{
	string out;
	for (auto& c : a)
	{
		out += tolower(c);
	}
	return out;
}

EXPR_EVAL_NM_LEAVE