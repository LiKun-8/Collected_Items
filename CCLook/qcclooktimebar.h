/************************************************************
**
** @Name: ����ʱ
** @Description: ʱ�����������ʾ������
** @Date: 2013/04/19 19:32
**
*************************************************************/

#ifndef QCCLOOKTIMEBAR_H
#define QCCLOOKTIMEBAR_H

#include <QGraphicsItem>
#include <QtWidgets>
#include "globaldefines.h"

class QCCLookTimeBar : public QGraphicsItem
{

public:
	enum status {INIT, START, FINISHED};
	QCCLookTimeBar(QRectF rect, int timecount);
	~QCCLookTimeBar();

/// �ӿ�
public:
	// ��ʼ��ʱ
	void start();
	// ʱ���Ƿ�ľ�
	bool isFinished();
	// ����
	void reset();
	// ��ȡʣ��ʱ��
	int getLastTime()
	{
		return m_iTimeCount;
	}

/// �麯������
public:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	void advance(int phase);

private:
	QRectF m_rect;				// ��ʾ����
	int m_iOriTime;				// ��ʱ��
	int m_iTimeCount;			// ʣ��ʱ��
	QTime m_lastTime;			// ���ڼ�ʱ
	int m_iStatus;				// ��ʶ��ʱ�Ƿ����
};

#endif // QCCLOOKTIMEBAR_H
