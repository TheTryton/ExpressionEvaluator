#pragma once

#include <QtWidgets>

struct variable
{
	QWidget* group;
	QHBoxLayout* layout;
	QLineEdit* title;
	QLineEdit* value;
	QPushButton* remove;
	QPushButton* add;
};

class CCalculator : public QWidget
{
	Q_OBJECT

public:
	CCalculator(QWidget *parent = Q_NULLPTR);
	~CCalculator();
private:
	QLineEdit * m_Equation;
	QPushButton* m_EvaluateEquation;
	QLineEdit* m_ErrorBar;
	QLineEdit* m_Output;
	QList<variable> m_Variables;
	QVBoxLayout* m_VariablesLayout;
private:
	void clearLayout(QLayout* layout);

	void add();

	void eval();
};
