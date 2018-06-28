#include "CCosFunction.h"

CCosFunction::CCosFunction(const vector<IElement*>& arguments)
{
	m_Arguments = arguments;
}

long double CCosFunction::getValue()
{
	if (m_Arguments.size() >= 1)
	{
		if (m_Arguments[0])
		{
			return cos(m_Arguments[0]->getValue());
		}
	}

	return 0;
}

string CCosFunction::getErrors()
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

	return "not enough tan arguments! \n";
}

long double CCosFunction::getValue(const map<string, long double>& parameters)
{
	if (m_Arguments.size() >= 1)
	{
		if (m_Arguments[0])
		{
			return cos(m_Arguments[0]->getValue(parameters));
		}
	}

	return 0;
}

string CCosFunction::getErrors(const map<string, long double>& parameters)
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

	return "not enough tan arguments! \n";
}

size_t CCosFunction::getArgumentsCount()
{
	return 1;
}
