#include "CExpression.h"

CExpression::CExpression()
{
	m_RootElement = nullptr;
}

CExpression::~CExpression()
{
	if (m_RootElement)
	{
		delete m_RootElement;
	}
}

long double CExpression::getValue()
{
	if (m_RootElement)
	{
		return m_RootElement->getValue();
	}

	return 0.0;
}

string CExpression::getErrors()
{
	if (m_RootElement)
	{
		return m_RootElement->getErrors();
	}

	return string();
}

long double CExpression::getValue(const map<string, long double>& parameters)
{
	if (m_RootElement)
	{
		return m_RootElement->getValue(parameters);
	}

	return 0.0;
}

string CExpression::getErrors(const map<string, long double>& parameters)
{
	if (m_RootElement)
	{
		return m_RootElement->getErrors(parameters);
	}

	return string();
}

vector<string> CExpression::getParameterNames()
{
	return m_Parameters;
}

