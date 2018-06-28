#pragma once

#include "IOperation.h"

class CDivideOperation : public IOperation
{
public:
	CDivideOperation(IElement* a, IElement* b);
public:
	virtual long double getValue() override;
	virtual string getErrors() override;

	virtual long double getValue(const map<string, long double>& parameters) override;
	virtual string getErrors(const map<string, long double>& parameters) override;
};

