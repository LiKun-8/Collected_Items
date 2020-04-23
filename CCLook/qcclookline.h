/************************************************************
**
** @Name: ����
** @Description: ����֮�������
** @Date: 2013/04/19 19:29
**
*************************************************************/

#ifndef QCCLOOKLINE_H
#define QCCLOOKLINE_H

#include <QGraphicsItem>
#include <QtWidgets>

#include "globaldefines.h"

class QCCLookLine : public QGraphicsItem
{
public:
	enum status{FADING, UNVISIABLE};
public:
	QCCLookLine(QPainterPath path);
	~QCCLookLine();

/// �麯������
public:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	void advance(int phase);

private:
	QPainterPath m_path;
	int m_iStatus;
	int m_iAlpha;
	int m_lastTime;				// ʱ���¼�����ڶ�����ʾ
};

#endif // QCCLOOKLINE_H
