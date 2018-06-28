#include "CPowerOperation.h"

CPowerOperation::CPowerOperation(IElement * a, IElement * b)
{
	m_A = a;
	m_B = b;
}

long double CPowerOperation::getValue()
{
	if (m_A && m_B)
	{
		return pow(m_A->getValue(),m_B->getValue());
	}

	return 0;
}

string CPowerOperation::getErrors()
{
	if (!m_A || !m_B)
	{
		return "not enough power operands! \n";
	}

	string output = "";

	if (m_A)
	{
		output += m_A->getErrors();
	}

	if (m_B)
	{
		output += m_B->getErrors();
	}

	return output;
}

long double CPowerOperation::getValue(const map<string, long double>& parameters)
{
	if (m_A && m_B)
	{
		return pow(m_A->getValue(parameters), m_B->getValue(parameters));
	}

	return 0;
}

string CPowerOperation::getErrors(const map<string, long double>& parameters)
{
	if (!m_A || !m_B)
	{
		return "not enough power operands! \n";
	}

	string output = "";

	if (m_A)
	{
		output += m_A->getErrors(parameters);
	}

	if (m_B)
	{
		output += m_B->getErrors(parameters);
	}

	return output;
}
