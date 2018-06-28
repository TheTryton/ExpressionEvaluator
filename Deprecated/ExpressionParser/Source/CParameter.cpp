#include "CParameter.h"

CParameter::CParameter(string parameterName)
{
	m_ParameterName = parameterName;
}

CParameter::~CParameter()
{
}

long double CParameter::getValue()
{
	return 0;
}

string CParameter::getErrors()
{
	return "parameter " + m_ParameterName + "couldn't be evaluated! \n";
}

long double CParameter::getValue(const map<string, long double>& parameters)
{
	return parameters.at(m_ParameterName);
}

string CParameter::getErrors(const map<string, long double>& parameters)
{
	if(parameters.find(m_ParameterName) == parameters.end())
	{ 
		return "parameter " + m_ParameterName + "couldn't be evaluated! \n";
	}
	return string();
}
