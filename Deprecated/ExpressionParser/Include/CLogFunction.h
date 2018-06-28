#pragma once

#include "IFunction.h"

class CLogFunction : public IFunction
{
public:
	CLogFunction(const vector<IElement*>& arguments);
public:
	virtual long double getValue() override;
	virtual string getErrors() override;

	virtual long double getValue(const map<string, long double>& parameters) override;
	virtual string getErrors(const map<string, long double>& parameters) override;

	virtual size_t getArgumentsCount() override;
};

