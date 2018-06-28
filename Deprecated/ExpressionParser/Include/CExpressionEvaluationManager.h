#pragma once

#include "IElement.h"
#include "IOperation.h"
#include "IFunction.h"

class CExpression;

class CExpressionEvaluationManager
{
public:
	CExpressionEvaluationManager();
public:
	enum class ErrorCode
	{
		DoubleDecimalSeparator,
		NotEnoughParenthesis,
		IncorrentPositionOfOperator,
		NotEnoughArguments,
		InvalidExpression,
		None
	};

	void registerOperator(char operatorCharacter, FOperationConstructor constructor, size_t priority = 0, bool leftAssoc = true);
	void registerFunction(string functionName, FFunctionConstructor constructor);

	void addDecimalSeparator(char separator);
	void addSeparatorCharacter(char separator);
	void setArgumentSeparator(char separator);

	CExpression* createExpression(const string& expression, ErrorCode* errorCode = nullptr);
	CExpression* createExpressionRecursive(const string& expression);
private:
	bool isNumber(char a);
	double toDouble(string symbol);
	
	vector<string> separateSymbols(const string& expression, ErrorCode* errorCode = nullptr);
	typedef pair<vector<string>, vector<string>> RPNOut;
	RPNOut convertToRPN(const vector<string>& input, ErrorCode* errorCode = nullptr);

	bool isOperator(char symbol);
	bool isFunction(string symbol);
	bool isSeparator(char symbol);
	bool isDecimalSeparator(char symbol);
private:
	vector<char> m_DecimalSeparators;
	map<char, FOperationConstructor> m_OperatorCharacters;
	map<char, size_t> m_OperatorPriorities;
	map<char, bool> m_OperatorLeftAssociativity;
	map<string, FFunctionConstructor> m_Functions;
	map<string, size_t> m_FunctionArgumentCounts;
	vector<char> m_Separators;
	char m_ArgumentSeparator;

	ErrorCode m_ErrorCode;
};