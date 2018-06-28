#pragma once

#include "IElement.h"

typedef std::function<IElement*(IElement* left, IElement* right)> FOperationConstructor;

class IOperation : public IElement
{
protected:
	IOperation();
public:
	virtual ~IOperation() override;
protected:
	IElement * m_A;
	IElement * m_B;
};


