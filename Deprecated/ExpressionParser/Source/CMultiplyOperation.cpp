#include "CMultiplyOperation.h"

CMultiplyOperation::CMultiplyOperation(IElement * a, IElement * b)
{
	m_A = a;
	m_B = b;
}

long double CMultiplyOperation::getValue()
{
	if (m_A && m_B)
	{
		return m_A->getValue() * m_B->getValue();
	}

	return 0;
}

string CMultiplyOperation::getErrors()
{
	if (!m_A || !m_B)
	{
		return "not enough multiply operands! \n";
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

long double CMultiplyOperation::getValue(const map<string, long double>& parameters)
{
	if (m_A && m_B)
	{
		return m_A->getValue(parameters) * m_B->getValue(parameters);
	}

	return 0;
}

string CMultiplyOperation::getErrors(const map<string, long double>& parameters)
{
	if (!m_A || !m_B)
	{
		return "not enough multiply operands! \n";
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
