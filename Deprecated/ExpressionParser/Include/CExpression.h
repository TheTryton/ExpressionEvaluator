#pragma once

#include "IElement.h"

#include <vector>

class CExpression : IElement
{
	friend class CExpressionEvaluationManager;
private:
	CExpression();
public:
	~CExpression();
public:
	virtual long double getValue() override;

	virtual string getErrors() override;

	virtual long double getValue(const map<string, long double>& parameters) override;
	virtual string getErrors(const map<string, long double>& parameters) override;

	vector<string> getParameterNames();
private:
	IElement * m_RootElement;
	vector<string> m_Parameters;
};

