#include "CLogFunction.h"

CLogFunction::CLogFunction(const vector<IElement*>& arguments)
{
	m_Arguments = arguments;
}

long double CLogFunction::getValue()
{
	if (m_Arguments.size() >= 2)
	{
		long double base = 2;
		long double x = 1;

		if (m_Arguments[0])
		{
			base = m_Arguments[0]->getValue();
		}

		if (m_Arguments[1])
		{
			x = m_Arguments[1]->getValue();
		}

		if ((x > 0) && (((base > 0) && (base < 1)) || (base > 1)))
		{
			return log(x) / log(base);
		}
	}

	return 0;
}

string CLogFunction::getErrors()
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

	return "not enough log arguments! \n";
}

long double CLogFunction::getValue(const map<string, long double>& parameters)
{
	if (m_Arguments.size() >= 2)
	{
		long double base = 2;
		long double x = 1;

		if (m_Arguments[0])
		{
			base = m_Arguments[0]->getValue(parameters);
		}

		if (m_Arguments[1])
		{
			x = m_Arguments[1]->getValue(parameters);
		}

		if ((x > 0) && ((base > 0) && (base < 1)) || (base > 1))
		{
			return log(x) / log(base);
		}
	}

	return 0;
}

string CLogFunction::getErrors(const map<string, long double>& parameters)
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

	return "not enough log arguments! \n";
}

size_t CLogFunction::getArgumentsCount()
{
	return 2;
}
