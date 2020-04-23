#include "qcclookitem.h"

QCCLookItem::QCCLookItem(QString fileName)
	: QGraphicsItem(0)
	, m_iStatus(NORMAL)
	, m_pixmap(fileName)
	, m_iAlpha(0)
{
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton);
}

QCCLookItem::~QCCLookItem()
{

}

/// �麯������
QRectF QCCLookItem::boundingRect() const
{
	return QRectF(-BlockSize / 2, -BlockSize / 2, BlockSize, BlockSize);
}

void QCCLookItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	switch (m_iStatus)
	{
	case NORMAL:
		{
			drawBlock(painter, QColor(0, 0, 0, 255));
			break;
		}
	case HOVER:
		{
			drawBlock(painter, QColor(255, 100, 100, 255));
			break;
		}
	case TOGGLE:
		{
			drawBlock(painter, QColor(255, 0, 0, 255));
			break;
		}
	case TIP:
		{
			drawBlock(painter, QColor(0, 255, 0, 255));
			break;
		}
	case FADING:
		{
			drawBlock(painter, QColor(255, 0, 0, 255));
			// ��䱳��ɫʹ����ʧ
			painter->fillRect(boundingRect(), QColor(255, 255, 255, m_iAlpha));
			break;
		}
	case UNVISIABLE:
		{
			break;
		}
	}

}

void QCCLookItem::advance(int phase)
{
	if (m_iStatus == FADING)
	{
		int delta = GetTickCount() - m_lastTime;
		if (delta <= AnimationTime)
		{
			m_iAlpha = 255 * delta / AnimationTime ;
			update();
		}
		else
		{
			m_iStatus = UNVISIABLE;
			QCCLScene* qScene = static_cast<QCCLScene*>(scene());
			qScene->reduceBlock(m_index);
			qScene->removeItem(this);
		}
	}
}

/// �ӿ�
void QCCLookItem::setToggle(bool status)
{
	if (status == true)
		m_iStatus = TOGGLE;
	else
		m_iStatus = NORMAL;
	update();
}

bool QCCLookItem::isToggle() const
{
	if (m_iStatus == TOGGLE)
		return true;
	else
		return false;
}

/// �¼�
void QCCLookItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	if (m_iStatus < FADING && m_iStatus != TOGGLE)
	{
		m_iStatus = HOVER;
		update();
	}
}

void QCCLookItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	if (m_iStatus < FADING && m_iStatus != TOGGLE)
	{
		m_iStatus = NORMAL;
		update();
	}
}

void QCCLookItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_iStatus >= FADING)
		return;

	QCCLScene* scene = static_cast<QCCLScene*>(this->scene());

	if (m_iStatus != TOGGLE)
	{
		m_iStatus = TOGGLE;
		scene->addSelectedBlocks(this);
	}
	else
	{
		m_iStatus = HOVER;
		scene->removeSelectedBlocks(this);
	}

	update();
}

/// ˽�к���
void QCCLookItem::drawBlock(QPainter* painter, QColor color)
{
	QPainterPath qInnerPath;

	qInnerPath.addRect(-BlockSize / 2 + 4, -BlockSize / 2 + 4, BlockSize - 8, BlockSize - 8);
	painter->drawPixmap(-BlockSize / 2 + 4, -BlockSize / 2 + 4, BlockSize - 8, BlockSize - 8, m_pixmap);
	painter->setPen(QPen(QBrush(color), 3));
	painter->drawPath(qInnerPath);	
}