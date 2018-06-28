#pragma once

#include "IElement.h"

class CValue : public IElement
{
public:
	CValue(long double value);
	virtual ~CValue() override;
public:
	virtual long double getValue() override;
	virtual string getErrors() override;

	virtual long double getValue(const map<string, long double>& parameters) override;
	virtual string getErrors(const map<string, long double>& parameters) override;
private:
	long double m_Value;
};

