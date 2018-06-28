#pragma once

#include "IElement.h"

#include <vector>

typedef std::function<IElement*(const vector<IElement*>& childrenArguments)> FFunctionConstructor;

class IFunction : public IElement
{
public:
	virtual ~IFunction() override;
	virtual size_t getArgumentsCount() = 0;
protected:
	vector<IElement*> m_Arguments;
};

