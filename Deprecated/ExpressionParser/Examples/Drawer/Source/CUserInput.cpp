#include "CUserInput.h"

#include "CAddOperation.h"
#include "CSubtractOperation.h"
#include "CMultiplyOperation.h"
#include "CDivideOperation.h"
#include "CPowerOperation.h"

#include "CSinFunction.h"
#include "CCosFunction.h"
#include "CTanFunction.h"
#include "CExpFunction.h"
#include "CLogFunction.h"

CUserInput::CUserInput(QWidget *parent):
	QWidget(parent)
{
	m_Manager = new CExpressionEvaluationManager;

	m_Manager->addSeparatorCharacter(' ');
	m_Manager->addDecimalSeparator('.');
	m_Manager->setArgumentSeparator(',');

	m_Manager->registerOperator('+', [](IElement* a, IElement* b)->IElement* {return new CAddOperation(a, b); }, 0);
	m_Manager->registerOperator('-', [](IElement* a, IElement* b)->IElement* {return new CSubtractOperation(a, b); }, 0);
	m_Manager->registerOperator('*', [](IElement* a, IElement* b)->IElement* {return new CMultiplyOperation(a, b); }, 1);
	m_Manager->registerOperator('/', [](IElement* a, IElement* b)->IElement* {return new CDivideOperation(a, b); }, 1);
	m_Manager->registerOperator('^', [](IElement* a, IElement* b)->IElement* {return new CPowerOperation(a, b); }, 2, false);

	m_Manager->registerFunction("sin", [](const vector<IElement*>& args)->IElement* {return new CSinFunction(args); });
	m_Manager->registerFunction("cos", [](const vector<IElement*>& args)->IElement* {return new CCosFunction(args); });
	m_Manager->registerFunction("tan", [](const vector<IElement*>& args)->IElement* {return new CTanFunction(args); });
	m_Manager->registerFunction("exp", [](const vector<IElement*>& args)->IElement* {return new CExpFunction(args); });
	m_Manager->registerFunction("log", [](const vector<IElement*>& args)->IElement* {return new CLogFunction(args); });

	m_MainLayout = new QVBoxLayout;
	setLayout(m_MainLayout);
	{
		int heightOfInput = 30;

		m_FunctionInput = new QTextEdit;
		m_FunctionInput->setFixedHeight(heightOfInput);
		m_MainLayout->addWidget(m_FunctionInput);

		m_FunctionLayout = new QHBoxLayout;
		m_MainLayout->addLayout(m_FunctionLayout);
		{
			m_AnalyzeButton = new QPushButton;
			m_AnalyzeButton->setText("Analyze");
			QObject::connect(m_AnalyzeButton, &QPushButton::released, this, &CUserInput::onAnalyzeFunction);
			m_FunctionLayout->addWidget(m_AnalyzeButton);

			m_GraphFunction = new QPushButton;
			m_GraphFunction->setText("Graph function");
			QObject::connect(m_GraphFunction, &QPushButton::released, this, &CUserInput::onGraphFunction);
			m_FunctionLayout->addWidget(m_GraphFunction);
		}
		
		m_ErrorText = new QTextEdit;
		m_ErrorText->setFixedHeight(heightOfInput);
		m_ErrorText->setReadOnly(true);
		m_MainLayout->addWidget(m_ErrorText);

		m_ConstrainsLayout = new QHBoxLayout;
		m_MainLayout->addLayout(m_ConstrainsLayout);
		{
			m_XLayout = new QVBoxLayout;
			m_ConstrainsLayout->addLayout(m_XLayout);
			{
				m_XMin = new QLineEdit;
				m_XMin->setText(QString::number(m_XYMin.x()));
				m_XMin->setFixedHeight(heightOfInput);
				m_XMin->setValidator(new QDoubleValidator(-1e6, 1e6, 2, this));
				QObject::connect(m_XMin, &QLineEdit::textChanged, this, &CUserInput::onChangedXMin);
				m_XLayout->addWidget(m_XMin);

				m_XMax = new QLineEdit;
				m_XMax->setText(QString::number(m_XYMax.x()));
				m_XMax->setFixedHeight(heightOfInput);
				m_XMax->setValidator(new QDoubleValidator(-1e6, 1e6, 2, this));
				QObject::connect(m_XMax, &QLineEdit::textChanged, this, &CUserInput::onChangedXMax);
				m_XLayout->addWidget(m_XMax);
			}
			
			m_YLayout = new QVBoxLayout;
			m_ConstrainsLayout->addLayout(m_YLayout);
			{
				m_YMin = new QLineEdit;
				m_YMin->setText(QString::number(m_XYMin.y()));
				m_YMin->setFixedHeight(heightOfInput);
				m_YMin->setValidator(new QDoubleValidator(-1e6, 1e6, 2, this));
				QObject::connect(m_YMin, &QLineEdit::textChanged, this, &CUserInput::onChangedYMin);
				m_YLayout->addWidget(m_YMin);

				m_YMax = new QLineEdit;
				m_YMax->setText(QString::number(m_XYMax.y()));
				m_YMax->setFixedHeight(heightOfInput);
				m_YMax->setValidator(new QDoubleValidator(-1e6, 1e6, 4, this));
				QObject::connect(m_YMax, &QLineEdit::textChanged, this, &CUserInput::onChangedYMax);
				m_YLayout->addWidget(m_YMax);
			}
		}

		m_Graph = new CCanvas;
		m_MainLayout->addWidget(m_Graph);
		m_Graph->setXYConstrains(m_XYMin, m_XYMax);
		m_Graph->setMinimumSize(QSize(640, 480));
	}
}

CUserInput::~CUserInput()
{
	delete m_Manager;
}

void CUserInput::onAnalyzeFunction()
{
	CExpressionEvaluationManager::ErrorCode errorCode = CExpressionEvaluationManager::ErrorCode::None;
	auto expression = m_Manager->createExpression(m_FunctionInput->toPlainText().toStdString(), &errorCode);
	if (!expression)
	{
		switch (errorCode)
		{
		case CExpressionEvaluationManager::ErrorCode::DoubleDecimalSeparator:
			m_ErrorText->setText("DoubleDecimalSeparator!");
			break;
		case CExpressionEvaluationManager::ErrorCode::NotEnoughParenthesis:
			m_ErrorText->setText("NotEnoughParenthesis!");
			break;
		case CExpressionEvaluationManager::ErrorCode::IncorrentPositionOfOperator:
			m_ErrorText->setText("IncorrentPositionOfOperator!");
			break;
		case CExpressionEvaluationManager::ErrorCode::NotEnoughArguments:
			m_ErrorText->setText("NotEnoughArguments!");
			break;
		case CExpressionEvaluationManager::ErrorCode::InvalidExpression:
			m_ErrorText->setText("InvalidExpression!");
			break;
		}
	}
	else
	{
		m_ErrorText->setText("");

		delete expression;
	}
}

void CUserInput::onGraphFunction()
{
	onAnalyzeFunction();

	auto expression = m_Manager->createExpression(m_FunctionInput->toPlainText().toStdString());
	if (expression)
	{
		m_Graph->setExpression(expression);
	}
}

void CUserInput::onChangedXMin(const QString& newText)
{
	m_XYMin.setX(newText.toDouble());
	m_Graph->setXYConstrains(m_XYMin, m_XYMax);
}

void CUserInput::onChangedXMax(const QString& newText)
{
	m_XYMax.setX(newText.toDouble());
	m_Graph->setXYConstrains(m_XYMin, m_XYMax);
}

void CUserInput::onChangedYMin(const QString& newText)
{
	m_XYMin.setY(newText.toDouble());
	m_Graph->setXYConstrains(m_XYMin, m_XYMax);
}

void CUserInput::onChangedYMax(const QString& newText)
{
	m_XYMax.setY(newText.toDouble());
	m_Graph->setXYConstrains(m_XYMin, m_XYMax);
}
