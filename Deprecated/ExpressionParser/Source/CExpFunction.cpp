#include "CExpFunction.h"

CExpFunction::CExpFunction(const vector<IElement*>& arguments)
{
	m_Arguments = arguments;
}

long double CExpFunction::getValue()
{
	if (m_Arguments.size() >= 1)
	{
		if (m_Arguments[0])
		{
			return exp(m_Arguments[0]->getValue());
		}
	}

	return 0;
}

string CExpFunction::getErrors()
{
	auto argumentCount = getArgumentsCount();

	if (m_Arguments.size() >= argumentCount)
	{
		string output;
		for (size_t i = 0; i < argumentCount; i++)
		{
			output += m_Arguments[i]->getErrors();
		}
	}

	return "not enough sin arguments! \n";
}

long double CExpFunction::getValue(const map<string, long double>& parameters)
{
	if (m_Arguments.size() >= 1)
	{
		if (m_Arguments[0])
		{
			return exp(m_Arguments[0]->getValue(parameters));
		}
	}

	return 0;
}

string CExpFunction::getErrors(const map<string, long double>& parameters)
{
	auto argumentCount = getArgumentsCount();

	if (m_Arguments.size() >= argumentCount)
	{
		string output;
		for (size_t i = 0; i < argumentCount; i++)
		{
			output += m_Arguments[i]->getErrors(parameters);
		}
	}

	return "not enough sin arguments! \n";
}

size_t CExpFunction::getArgumentsCount()
{
	return 1;
}
