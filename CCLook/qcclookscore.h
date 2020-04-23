/************************************************************
**
** @Name: ����
** @Description: ����ͳ�Ƽ���ʾ
** @Date: 2013/04/19 19:30
**
*************************************************************/

#ifndef QCCLOOKSCORE_H
#define QCCLOOKSCORE_H

#include <QGraphicsItem>
#include <QtWidgets>
#include "globaldefines.h"

class QCCLookScore : public QGraphicsItem
{

public:
	QCCLookScore(QRectF rect);
	~QCCLookScore();

/// �ӿ�
public:
	// ���ӷ���
	void addScore(int delta)
	{
		m_iScore = (m_iScore + delta > 0) ? m_iScore + delta : 0;
		update();
	}
	// ��ȡ����
	int getScore() const
	{
		return m_iScore;
	}
	// ���÷���
	int reset()
	{
		m_iScore = 0;
		update();
	}

/// �麯������
public:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	void advance(int phase);

/// ˽�к���
private:
	// ͨ�����ֻ�ȡͼƬָ��
	void getPixmapFromNum(int num, QPixmap*& first, QPixmap*& second);

private:
	QRectF m_rect;
	int m_iScore;			// ����
	QPixmap m_numPic[10];	// ����ͼƬ
};

#endif // QCCLOOKSCORE_H
