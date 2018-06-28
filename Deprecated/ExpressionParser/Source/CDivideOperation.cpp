#include "CDivideOperation.h"

CDivideOperation::CDivideOperation(IElement * a, IElement * b)
{
	m_A = a;
	m_B = b;
}

long double CDivideOperation::getValue()
{
	if (m_A && m_B)
	{
		if (abs(m_B->getValue()) > LDBL_EPSILON)
		{
			return m_A->getValue() / m_B->getValue();
		}
	}

	return 0;
}

string CDivideOperation::getErrors()
{
	if (!m_A || !m_B)
	{
		return "not enough divide operands! \n";
	}

	string output = "";

	if (m_A)
	{
		output += m_A->getErrors();
	}

	if (m_B)
	{
		string m_Bout = m_B->getErrors();
		if (m_Bout.size() == 0)
		{
			if (abs(m_B->getValue()) < LDBL_EPSILON)
			{
				output += "can't divide by 0! \n";
			}
		}
		output += m_Bout;
	}

	return output;
}

long double CDivideOperation::getValue(const map<string, long double>& parameters)
{
	if (m_A && m_B)
	{
		if (abs(m_B->getValue(parameters)) > LDBL_EPSILON)
		{
			return m_A->getValue(parameters) / m_B->getValue(parameters);
		}
	}

	return 0;
}

string CDivideOperation::getErrors(const map<string, long double>& parameters)
{
	if (!m_A || !m_B)
	{
		return "not enough divide operands! \n";
	}

	string output = "";

	if (m_A)
	{
		output += m_A->getErrors(parameters);
	}

	if (m_B)
	{
		string m_Bout = m_B->getErrors(parameters);
		if (m_Bout.size() == 0)
		{
			if (abs(m_B->getValue(parameters)) < LDBL_EPSILON)
			{
				output += "can't divide by 0! \n";
			}
		}
		output += m_Bout;
	}

	return output;
}
