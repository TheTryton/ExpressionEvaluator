#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <numeric>
#include <set>

#define EOL ';'
#define IF "IF"

#define EXPR_EVAL_NM_ENTER namespace ExpressionEvaluator{
#define EXPR_EVAL_NM_LEAVE }

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

EXPR_EVAL_NM_ENTER

using namespace std;

string cleanString(string a);

string toLower(string a);

struct operatorSymbol
{
	operatorSymbol(uint32_t p = 0);
	uint32_t priority = 0;
};

struct functionSymbol
{
	functionSymbol(uint32_t c = 0);
	uint32_t argumentCount = 0;
};

class IElement
{
protected:
	IElement();
public:
	virtual ~IElement();
public:
	virtual long double getValue(const map<string, long double>& variables) = 0;
	virtual long double getValue() = 0;
};

class CValue : public IElement
{
	friend class CExpressionEvaluator;
private:
	CValue(long double value = 0.0);
public:
	virtual ~CValue() override;
public:
	virtual long double getValue(const map<string, long double>& variables) override;
	
	virtual long double getValue() override;
private:
	long double m_Value;
};

class CVariable : public IElement
{
	friend class CExpressionEvaluator;
private:
	CVariable(string variableName = "");
public:
	virtual ~CVariable() override;
public:
	virtual long double getValue(const map<string, long double>& variables) override;

	virtual long double getValue() override;
private:
	string m_VariableName;
};

class COperator : public IElement
{
	friend class CExpressionEvaluator;
private:
	COperator(string operSignature, IElement* leftOperand, IElement* rightOperand);
public:
	virtual ~COperator() override;
public:
	virtual long double getValue(const map<string, long double>& variables) override;
	
	virtual long double getValue() override;
private:
	string m_OperatorSignature;
	IElement* m_LeftOperand;
	IElement* m_RightOperand;
};

class CFunction : public IElement
{
	friend class CExpressionEvaluator;
private:
	CFunction(string functionSignature, vector<IElement*> arguments);
public:
	virtual ~CFunction() override;
public:
	virtual long double getValue(const map<string, long double>& variables) override;
	
	virtual long double getValue() override;
private:
	string m_FunctionSignature;
	vector<IElement*> m_Arguments;
};

class CDynamicFunction;

class CDynamicFunctionInstance : public IElement
{
	friend class CDynamicFunction;
private:
	CDynamicFunctionInstance(CDynamicFunction* parent, vector<IElement*> arguments);
public:
	virtual ~CDynamicFunctionInstance() override;
public:
	virtual long double getValue(const map<string, long double>& variables) override;
	virtual long double getValue() override;
private:
	CDynamicFunction * m_Parent;
	vector<IElement*> m_Arguments;
};

class CDynamicFunction
{
	friend class CExpressionEvaluator;
	friend class CDynamicFunctionInstance;
private:
	CDynamicFunction(string functionSignature, vector<string> arguments, IElement* expression);
public:
	~CDynamicFunction() {};
public:
	CDynamicFunctionInstance * getInstance(vector<IElement*> arguments);
private:
	string m_FunctionSignature;
	vector<string> m_ArgumentNames;
	IElement* m_FunctionExpression;
};

class CExpression : public IElement
{
	friend class CExpressionEvaluator;
private:
	CExpression(IElement* rootElement);
public:
	virtual ~CExpression() override {};
public:
	virtual long double getValue(const map<string, long double>& variables) override;
	
	virtual long double getValue() override;
private:
	IElement * m_RootElement;
};

class CExpressionEvaluator
{
public:
	CExpressionEvaluator();

	CExpression* parse(const string& input);
	
	size_t getErrorPosition();
	
	string getErrorString();
	
	set<string> getVariableNames();
	
	CDynamicFunction* parseFunction(const string& input);
	
	bool addDynamicFunction(CDynamicFunction* function);
private:
	IElement * parse(const string& input, size_t offset);
	
	IElement* toNumber(const string& input);
	
	IElement* evaluateVariable(const string& input, size_t& offset);

	bool parseFunction(const string& input, size_t& offset, const string& function, stack<string>& operatorStack, stack<IElement*>& operandStack);

	bool parseNumber(const string& input, size_t& offset, stack<string>& operatorStack, stack<IElement*>& operandStack);

	bool parseOperator(const string& input, size_t& offset, const string& oper, stack<string>& operatorStack, stack<IElement*>& operandStack);

	IElement* parenthesis(const string& input, size_t& offset);

	vector<IElement*> functionArgs(const string& input, size_t& offset);

	IElement* evaluateArgument(const string& input, size_t& offset, bool& hitParenthesis);

	IElement* evaluateOperator(string oper, IElement* a, IElement* b);

	IElement* evaluateFunction(string function, vector<IElement*> arguments);

	bool hasHigherPriority(string opA, string opB);
	
	pair<bool, string> isOperator(const string& input, size_t offset);

	pair<bool, string> isFunction(const string& input, size_t offset);

	bool isNumber(char a);
private:
	map<string, operatorSymbol> m_Operators;
	map<string, functionSymbol> m_Functions;
	map<string, CDynamicFunction*> m_DynamicFunctions;

	size_t m_LastErrorPosition;
	string m_LastErrorString;
	set<string> m_LastVariableNames;
};

EXPR_EVAL_NM_LEAVE