#include "CExpressionEvaluationManager.h"

#include "CExpression.h"
#include "CValue.h"
#include "CParameter.h"

#include <stack>
#include <sstream>
#include <algorithm>

CExpressionEvaluationManager::CExpressionEvaluationManager()
{
}

void CExpressionEvaluationManager::registerOperator(char operatorCharacter, FOperationConstructor constructor, size_t priority, bool leftAssoc)
{
	m_OperatorCharacters[operatorCharacter] = constructor;
	m_OperatorPriorities[operatorCharacter] = priority;
	m_OperatorLeftAssociativity[operatorCharacter] = leftAssoc;
}

void CExpressionEvaluationManager::registerFunction(string functionName, FFunctionConstructor constructor)
{
	m_Functions[functionName] = constructor;
	auto functionInstance = static_cast<IFunction*>(constructor(vector<IElement*>()));
	m_FunctionArgumentCounts[functionName] = functionInstance->getArgumentsCount();
	delete functionInstance;
}

void CExpressionEvaluationManager::addDecimalSeparator(char separator)
{
	m_DecimalSeparators.push_back(separator);
}

void CExpressionEvaluationManager::addSeparatorCharacter(char separator)
{
	m_Separators.push_back(separator);
}

void CExpressionEvaluationManager::setArgumentSeparator(char separator)
{
	m_ArgumentSeparator = separator;
}

CExpression * CExpressionEvaluationManager::createExpression(const string& expression, ErrorCode* errorCode)
{
	auto separatedExpression = separateSymbols(expression, errorCode);
	if (errorCode)
	{
		if (*errorCode != ErrorCode::None)
		{
			return nullptr;
		}
	}
	auto RPN = convertToRPN(separatedExpression, errorCode);
	if (errorCode)
	{
		if (*errorCode != ErrorCode::None)
		{
			return nullptr;
		}
	}

	stack<IElement*> stack;

	for (auto& symbol : RPN.first)
	{
		if (symbol.size() != 0)
		{
			if (isNumber(symbol[0]))
			{
				IElement* symbolEl = new CValue(toDouble(symbol));
				stack.push(symbolEl);
			}
			else if (find(RPN.second.begin(), RPN.second.end(), symbol) != RPN.second.end())
			{
				IElement* symbolEl = new CParameter(symbol);
				stack.push(symbolEl);
			}
			else if (symbol.size() == 1 && isOperator(symbol[0]))
			{
				if (stack.size() < 2)
				{
					if (errorCode)
					{
						*errorCode = ErrorCode::IncorrentPositionOfOperator;
					}

					return nullptr;
				}
				
				IElement* a = stack.top();
				stack.pop();
				IElement* b = stack.top();
				stack.pop();

				IElement* symbolEl = m_OperatorCharacters[symbol[0]](b, a);

				stack.push(symbolEl);
			}
			else if(isFunction(symbol))
			{
				size_t argumentCount = m_FunctionArgumentCounts[symbol];

				if (stack.size() < argumentCount)
				{
					if (errorCode)
					{
						*errorCode = ErrorCode::NotEnoughArguments;
					}

					return nullptr;
				}

				vector<IElement*> arguments(argumentCount);

				for (size_t i = 0; i < argumentCount; i++)
				{
					arguments[argumentCount - 1 - i] = stack.top();
					stack.pop();
				}

				IElement* symbolEl = m_Functions[symbol](arguments);

				stack.push(symbolEl);
			}
		}
	}

	if (stack.size() != 1)
	{
		if (errorCode)
		{
			*errorCode = ErrorCode::InvalidExpression;
		}

		return nullptr;
	}

	CExpression* exp = new CExpression();

	for (auto& parameter : RPN.second)
	{
		exp->m_Parameters.push_back(parameter);
	}

	exp->m_RootElement = stack.top();
	stack.pop();

	return exp;
}

bool CExpressionEvaluationManager::isOperator(char symbol)
{
	vector<char> keys;
	for (auto it = m_OperatorCharacters.begin(); it != m_OperatorCharacters.end(); ++it) {
		keys.push_back(it->first);
	}

	for (auto& operatorCharacter : keys)
	{
		if (symbol == operatorCharacter)
		{
			return true;
		}
	}
	return false;
}

bool CExpressionEvaluationManager::isFunction(string symbol)
{
	vector<string> keys;
	for (auto it = m_Functions.begin(); it != m_Functions.end(); ++it) {
		keys.push_back(it->first);
	}

	for (auto& functionSignature : keys)
	{
		if (symbol == functionSignature)
		{
			return true;
		}
	}
	return false;
}

bool CExpressionEvaluationManager::isSeparator(char symbol)
{
	for (auto& separator : m_Separators)
	{
		if (symbol == separator)
		{
			return true;
		}
	}

	return false;
}

bool CExpressionEvaluationManager::isDecimalSeparator(char symbol)
{
	for (auto& separator : m_DecimalSeparators)
	{
		if (symbol == separator)
		{
			return true;
		}
	}

	return false;
}

bool CExpressionEvaluationManager::isNumber(char a)
{
	return (a >= '0' && a <= '9') || a == '.' || a == 'e' || a == '-';
}

double CExpressionEvaluationManager::toDouble(string symbol)
{
	stringstream ss(symbol);
	double value;
	ss >> value;
	return value;
}

vector<string> CExpressionEvaluationManager::separateSymbols(const string& exp, ErrorCode* errorCode)
{
	vector<string> symbols;
	string expression = exp;

	expression.erase(remove_if(expression.begin(), expression.end(), isspace), expression.end());

	string currentNumber = "";
	bool decimalSeparator = false;
	string currentSymbolString = "";

	for(auto& character: expression)
	{
		if (isNumber(character))
		{
			if (currentSymbolString.size() != 0)
			{
				symbols.push_back(currentSymbolString);
				currentSymbolString = "";
			}
			currentNumber += character;
		}
		else if (isDecimalSeparator(character))
		{
			if (decimalSeparator)
			{
				if (errorCode)
				{
					*errorCode = ErrorCode::DoubleDecimalSeparator;
				}

				return vector<string>();
			}
			decimalSeparator = true;

			if (currentSymbolString.size() != 0)
			{
				symbols.push_back(currentSymbolString);
				currentSymbolString = "";
			}
			currentNumber += character;
		}
		else
		{
			if (currentNumber.size() != 0)
			{
				symbols.push_back(currentNumber);
				currentNumber = "";
				decimalSeparator = false;
			}
			currentSymbolString += character;
		}
	}

	if (currentSymbolString.size() != 0)
	{
		symbols.push_back(currentSymbolString);
	}
	if (currentNumber.size() != 0)
	{
		symbols.push_back(currentNumber);
	}

	return symbols;
}

CExpressionEvaluationManager::RPNOut CExpressionEvaluationManager::convertToRPN(const vector<string>& input, ErrorCode* errorCode)
{
	vector<string> output;
	vector<string> parameters;
	stack<string> stack;

	string currentParameter = "";

	for(auto symbols:input)
	{
		if (symbols.size() != 0)
		{
			if (isNumber(symbols[0]) || isDecimalSeparator(symbols[0]))
			{
				output.push_back(symbols);
			}
			else
			{
				while (symbols.size() != 0)
				{
					bool symbolIsFunction = false;

					vector<string> keys;
					for (auto it = m_Functions.begin(); it != m_Functions.end(); ++it) {
						keys.push_back(it->first);
					}

					for (auto& functionSignature : keys)
					{
						if (symbols.find(functionSignature) == 0)
						{
							if (currentParameter.size() != 0)
							{
								output.push_back(currentParameter);
								parameters.push_back(currentParameter);
								currentParameter = "";
							}

							stack.push(functionSignature);
							symbols.erase(symbols.begin(), symbols.begin() + functionSignature.size() - 1);
							symbolIsFunction = true;
							break;
						}
					}
				
					if (symbolIsFunction)
					{
					}
					
					else if (symbols[0] == m_ArgumentSeparator)
					{
						if (currentParameter.size() != 0)
						{
							output.push_back(currentParameter);
							parameters.push_back(currentParameter);
							currentParameter = "";
						}

						bool foundLeftParenthesis = false;

						while (stack.size() != 0)
						{
							string element = stack.top();
							stack.pop();
							if (element == "(")
							{
								foundLeftParenthesis = true;
								stack.push(element);
								break;
							}
							else
							{
								output.push_back(element);
							}
						}

						if (!foundLeftParenthesis)
						{
							if (errorCode)
							{
								*errorCode = ErrorCode::NotEnoughParenthesis;
							}
							return RPNOut();
						}

						symbols.erase(symbols.begin());
					}
				
					else if (isOperator(symbols[0]))
					{
						if (currentParameter.size() != 0)
						{
							output.push_back(currentParameter);
							parameters.push_back(currentParameter);
							currentParameter = "";
						}

						char o1 = symbols[0];

						while (stack.size()!=0)
						{
							string element = stack.top();
							stack.pop();
							if (element.size() == 1 && isOperator(element[0]))
							{
								char o2 = element[0];

								if (
									((m_OperatorLeftAssociativity[o1]) && (m_OperatorPriorities[o1] <= m_OperatorPriorities[o2])) ||
									((!m_OperatorLeftAssociativity[o1]) && (m_OperatorPriorities[o1] < m_OperatorPriorities[o2]))
									)
								{
									output.push_back(o2 + string(""));
								}
								else
								{
									stack.push(element);
									break;
								}
							}
							else
							{
								stack.push(element);
								break;
							}
						}
					
						stack.push(o1 + string(""));

						symbols.erase(symbols.begin());
					}

					else if (symbols[0] == '(')
					{
						if (currentParameter.size() != 0)
						{
							output.push_back(currentParameter);
							parameters.push_back(currentParameter);
							currentParameter = "";
						}

						stack.push("(");
						symbols.erase(symbols.begin());
					}

					else if (symbols[0] == ')')
					{
						if (currentParameter.size() != 0)
						{
							output.push_back(currentParameter);
							parameters.push_back(currentParameter);
							currentParameter = "";
						}

						bool foundLeftParenthesis = false;

						while (stack.size() != 0)
						{
							string element = stack.top();
							stack.pop();
							if (element == "(")
							{
								foundLeftParenthesis = true;
								if (stack.size() != 0)
								{
									string nextElement = stack.top();
									stack.pop();
									if (isFunction(nextElement))
									{
										output.push_back(nextElement);
									}
									else
									{
										stack.push(nextElement);
									}
								}
								break;
							}
							else
							{
								output.push_back(element);
							}
						}

						if (!foundLeftParenthesis)
						{
							if (errorCode)
							{
								*errorCode = ErrorCode::NotEnoughParenthesis;
							}
							return RPNOut();
						}

						symbols.erase(symbols.begin());
					}
				
					else
					{
						currentParameter += symbols[0];
						symbols.erase(symbols.begin());
					}
				}
			
				if (currentParameter.size() != 0)
				{
					output.push_back(currentParameter);
					parameters.push_back(currentParameter);
					currentParameter = "";
				}
			}
		}
	}

	while (stack.size() != 0)
	{
		string element = stack.top();
		stack.pop();

		if (element == "(" || element == ")")
		{
			if (errorCode)
			{
				*errorCode = ErrorCode::NotEnoughParenthesis;
			}
			return RPNOut();
		}

		output.push_back(element);
	}

	return RPNOut(output, parameters);
}
