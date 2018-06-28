#include "CSinFunction.h"

CSinFunction::CSinFunction(const vector<IElement*>& arguments)
{
	m_Arguments = arguments;
}

long double CSinFunction::getValue()
{
	if (m_Arguments.size() >= 1)
	{
		if (m_Arguments[0])
		{
			return sin(m_Arguments[0]->getValue());
		}
	}

	return 0;
}

string CSinFunction::getErrors()
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

long double CSinFunction::getValue(const map<string, long double>& parameters)
{
	if (m_Arguments.size() >= 1)
	{
		if (m_Arguments[0])
		{
			return sin(m_Arguments[0]->getValue(parameters));
		}
	}

	return 0;
}

string CSinFunction::getErrors(const map<string, long double>& parameters)
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

size_t CSinFunction::getArgumentsCount()
{
	return 1;
}
