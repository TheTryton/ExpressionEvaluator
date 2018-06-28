#pragma once

#include "IElement.h"

class CParameter : public IElement
{
public:
	CParameter(string parameterName);
	virtual ~CParameter() override;
public:
	virtual long double getValue() override;
	virtual string getErrors() override;

	virtual long double getValue(const map<string, long double>& parameters) override;
	virtual string getErrors(const map<string, long double>& parameters) override;
private:
	string m_ParameterName;
};

