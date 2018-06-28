#include "CCanvas.h"

#include <QPainter>
#include <QMap>

CCanvas::CCanvas(QWidget *parent):
	QWidget(parent)
{
	m_CurrentExpression = nullptr;
}

CCanvas::~CCanvas()
{
	if (m_CurrentExpression)
	{
		delete m_CurrentExpression;
	}
}

void CCanvas::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);

	QSize screenSize = QSize(painter.device()->width(), painter.device()->height());

	QPen pen;
	pen.setColor(QColor(0, 0, 0));
	pen.setWidth(3);

	painter.setPen(pen);

	//X Line
	{
		quint32 xPixelStart = 0;
		quint32 xPixelEnd = screenSize.width();

		quint32 yPixelStart = (1.0 - (0.0 - m_XYMin.y()) / (m_XYMax.y() - m_XYMin.y()))*screenSize.height();
		quint32 yPixelEnd = (1.0 - (0.0 - m_XYMin.y()) / (m_XYMax.y() - m_XYMin.y()))*screenSize.height();

		QLine line = QLine(
			QPoint(xPixelStart, yPixelStart),
			QPoint(xPixelEnd, yPixelEnd)
		);

		painter.drawLine(line);
	}

	//Y Line
	{
		quint32 xPixelStart = (1.0 - (0.0 - m_XYMin.x()) / (m_XYMax.x() - m_XYMin.x()))*screenSize.width();
		quint32 xPixelEnd = (1.0 - (0.0 - m_XYMin.x()) / (m_XYMax.x() - m_XYMin.x()))*screenSize.width();

		quint32 yPixelStart = 0;
		quint32 yPixelEnd = screenSize.height();

		QLine line = QLine(
			QPoint(xPixelStart, yPixelStart),
			QPoint(xPixelEnd, yPixelEnd)
		);

		painter.drawLine(line);
	}

	pen.setColor(QColor(0, 0, 255));

	painter.setPen(pen);

	long double startX = m_XYMin.x();
	long double endX = m_XYMax.x();
	quint32 numPoints = painter.device()->width()/4;
	long double step = (endX - startX) / numPoints;

	long double x = startX;
	for (quint32 i = 0; i < numPoints-1; i++,x+=step)
	{
		quint32 xPixelStart = screenSize.width() / (float)numPoints * i;
		quint32 xPixelEnd = screenSize.width() / (float)numPoints * (i+1);

		quint32 yPixelStart = (1.0 - (evalExpression(x) - m_XYMin.y()) / (m_XYMax.y() - m_XYMin.y()))*screenSize.height();
		quint32 yPixelEnd = (1.0 - (evalExpression(x + step) - m_XYMin.y()) / (m_XYMax.y() - m_XYMin.y()))*screenSize.height();

		QLine line = QLine(
			QPoint(xPixelStart, yPixelStart),
			QPoint(xPixelEnd, yPixelEnd)
		);

		painter.drawLine(line);
	}
}

void CCanvas::setExpression(CExpression * expression)
{
	if (m_CurrentExpression)
	{
		delete m_CurrentExpression;
	}

	m_CurrentExpression = expression;

	repaint();
}

void CCanvas::setXYConstrains(const QPointF & xyMin, const QPointF & xyMax)
{
	m_XYMin = xyMin;
	m_XYMax = xyMax;
	repaint();
}

long double CCanvas::evalExpression(long double x)
{
	if (m_CurrentExpression)
	{
		QMap<string, long double> params;
		params["x"] = x;
		return m_CurrentExpression->getValue(params.toStdMap());
	}
	return 0;
}
