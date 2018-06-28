#include "IFunction.h"

IFunction::~IFunction()
{
	for (auto& element : m_Arguments)
	{
		if (element)
		{
			delete element;
		}
	}
}
