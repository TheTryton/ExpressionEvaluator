#include "CValue.h"

CValue::CValue(long double value)
{
	m_Value = value;
}

CValue::~CValue()
{
}

long double CValue::getValue()
{
	return m_Value;
}

string CValue::getErrors()
{
	return string();
}

long double CValue::getValue(const map<string, long double>& parameters)
{
	return m_Value;
}

string CValue::getErrors(const map<string, long double>& parameters)
{
	return string();
}
