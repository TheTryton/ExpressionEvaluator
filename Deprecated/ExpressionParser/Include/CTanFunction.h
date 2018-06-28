#pragma once

#include "IFunction.h"

class CTanFunction : public IFunction
{
public:
	CTanFunction(const vector<IElement*>& arguments);
public:
	virtual long double getValue() override;
	virtual string getErrors() override;

	virtual long double getValue(const map<string, long double>& parameters) override;
	virtual string getErrors(const map<string, long double>& parameters) override;

	virtual size_t getArgumentsCount() override;
};

