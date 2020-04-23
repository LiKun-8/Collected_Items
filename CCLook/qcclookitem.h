/************************************************************
**
** @Name: ����
** @Description: �����������ķ������ʾ
** @Date: 2013/04/19 19:28
**
*************************************************************/

#ifndef QCCLOOKITEM_H
#define QCCLOOKITEM_H

#include <QGraphicsItem>
#include <QtWidgets>

#include "globaldefines.h"
#include "qcclscene.h"

class QCCLScene;

class QCCLookItem : public QGraphicsItem
{

public:
	// ��������ͣ�����£���ʧ�У����ɼ���Ѱ·״̬
	enum status{NORMAL, HOVER, TOGGLE, TIP, FADING, UNVISIABLE, TESTING};
	enum {BLOCK = UserType + 1};

public:
	QCCLookItem(QString fileName);
	~QCCLookItem();
	
/// �麯������
public:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	void advance(int phase);
	int type () const 
	{
		return BLOCK;
	}

/// �¼�
public:
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

/// �ӿ�
public:	
	void setToggle(bool status);
	bool isToggle() const;
	void setStatus(status eStatus)
	{
		m_iStatus = eStatus;
		// ��¼ʱ��
		if (m_iStatus == FADING)
			m_lastTime = GetTickCount();
		update();
	}
	int getStatus() const
	{
		return m_iStatus;
	}
	int getID() const
	{
		return m_iId;
	}
	void setID(int id)
	{
		m_iId = id;
	}
	void setIndex(int index)
	{
		m_index = index;
	}
	int getIndex() const
	{
		return m_index;
	}

private:
	// ��item
	void drawBlock(QPainter* painter, QColor color);
	
private:
	int m_iStatus;				// ��ͨ�����£���ͣ����״̬
	QPixmap m_pixmap;			// ��������ʾ��ͼ��
	int m_iAlpha;				// ������䱳��ɫʹͼƬ����ʧ
	int m_iId;					// ���ڱ�ʾ�������
	int m_index;				// �洢��m_pBlocks�е�����
	int m_lastTime;				// ʱ���¼�����ڶ�����ʾ
};

#endif // QCCLOOKITEM_H
