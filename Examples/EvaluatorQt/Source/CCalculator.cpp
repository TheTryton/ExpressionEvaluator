#include "CCalculator.h"
#include "ExpressionEvaluator.h"

#include <string>
#include <map>

CCalculator::CCalculator(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout;
	setLayout(layout);
	{
		m_Equation = new QLineEdit;
		layout->addWidget(m_Equation);
		m_EvaluateEquation = new QPushButton;
		m_EvaluateEquation->setText("Evaluate");
		QObject::connect(m_EvaluateEquation, &QPushButton::released, this, &CCalculator::eval);
		layout->addWidget(m_EvaluateEquation);
		m_ErrorBar = new QLineEdit;
		m_ErrorBar->setReadOnly(true);
		layout->addWidget(m_ErrorBar);
		m_Output = new QLineEdit;
		m_Output->setReadOnly(true);
		layout->addWidget(m_Output);

		m_VariablesLayout = new QVBoxLayout;
		{
			QPushButton* m_AddButton = new QPushButton;
			m_AddButton->setText("+");
			QObject::connect(m_AddButton, &QPushButton::released, this, &CCalculator::add);
			m_VariablesLayout->addWidget(m_AddButton);
		}

		layout->addLayout(m_VariablesLayout);
	}
}

CCalculator::~CCalculator()
{
}

void CCalculator::add()
{
	variable var;

	var.group = new QWidget;
	var.layout = new QHBoxLayout;
	var.group->setLayout(var.layout);

	var.title = new QLineEdit;
	var.value = new QLineEdit;
	var.value->setValidator(new QDoubleValidator(-1e7, 1e7, 6));
	var.remove = new QPushButton;
	var.remove->setText("-");
	var.add = new QPushButton;
	var.add->setText("+");

	var.layout->addWidget(var.title);
	var.layout->addWidget(var.value);
	var.layout->addWidget(var.remove);
	var.layout->addWidget(var.add);

	QObject::connect(var.remove, &QPushButton::released, this, [=]() {
		m_VariablesLayout->removeWidget(var.group);
		for (int i = 0; i < this->m_Variables.size(); i++)
		{
			if (this->m_Variables[i].group == var.group)
			{
				this->m_Variables.removeAt(i);
				break;

			}
		}
		delete var.group;
	});
	QObject::connect(var.add, &QPushButton::released, this, &CCalculator::add);

	m_VariablesLayout->insertWidget(0, var.group);
	m_Variables.push_back(var);
}

void CCalculator::eval()
{
	std::string text = m_Equation->text().toStdString();
	std::map<std::string, long double> vars;
	for (auto& varb : m_Variables)
	{
		std::string name = varb.title->text().toStdString();
		double value = varb.value->text().toDouble();
		vars[name] = value;
	}

	ExpressionEvaluator::CExpressionEvaluator eval;
	auto output = eval.parse(text);
	if (!output)
	{
		m_ErrorBar->setText(QString::fromStdString(eval.getErrorString()));
	}
	else
	{
		m_ErrorBar->setText("");
		m_Output->setText(QString::number((double)output->getValue(vars)));
		delete output;
	}
}
