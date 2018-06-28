#pragma once

#include <QtWidgets>
#include "CCanvas.h"

#include "CExpressionEvaluationManager.h"
#include "CExpression.h"

class CUserInput : public QWidget
{
	Q_OBJECT

public:
	CUserInput(QWidget *parent = nullptr);
	~CUserInput();
private:
	void onAnalyzeFunction();
	void onGraphFunction();

	void onChangedXMin(const QString& newText);
	void onChangedXMax(const QString& newText);

	void onChangedYMin(const QString& newText);
	void onChangedYMax(const QString& newText);
private:
	QVBoxLayout * m_MainLayout;
	QTextEdit * m_FunctionInput;

	QHBoxLayout* m_FunctionLayout;
	QPushButton * m_AnalyzeButton;
	QPushButton	* m_GraphFunction;

	QTextEdit* m_ErrorText;

	QHBoxLayout* m_ConstrainsLayout;

	QVBoxLayout* m_XLayout;
	QLineEdit* m_XMin;
	QLineEdit* m_XMax;

	QVBoxLayout* m_YLayout;
	QLineEdit* m_YMin;
	QLineEdit* m_YMax;

	CCanvas* m_Graph;

	QPointF m_XYMin = QPointF(-10.0,-10.0);
	QPointF m_XYMax = QPointF(10.0, 10.0);

	CExpressionEvaluationManager* m_Manager;
};
