#include "IOperation.h"

IOperation::IOperation()
{
	m_A = nullptr;
	m_B = nullptr;
}

IOperation::~IOperation()
{
	if (m_A)
	{
		delete m_A;
	}

	if (m_B)
	{
		delete m_B;
	}
}
