#pragma once

#include <functional>
#include <string>
#include <map>
#include <cmath>

using namespace std;

class IElement
{
public:
	virtual ~IElement();
public:
	virtual long double getValue() = 0;
	virtual string getErrors() = 0;

	virtual long double getValue(const map<string, long double>& parameters) = 0;
	virtual string getErrors(const map<string, long double>& parameters) = 0;
};

