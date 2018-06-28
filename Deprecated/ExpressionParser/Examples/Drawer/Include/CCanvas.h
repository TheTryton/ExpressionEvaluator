#pragma once

#include <QWidget>
#include "CExpression.h"

class CCanvas : public QWidget
{
	Q_OBJECT

public:
	CCanvas(QWidget *parent = nullptr);
	~CCanvas();
protected:
	virtual void paintEvent(QPaintEvent* event) override;
public:
	void setExpression(CExpression* expression);
	void setXYConstrains(const QPointF& xyMin, const QPointF& xyMax);
private:
	long double evalExpression(long double x);
private:
	long double m_Value;
	CExpression* m_CurrentExpression;
	QPointF m_XYMin;
	QPointF m_XYMax;
};
