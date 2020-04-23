#include "qcclscene.h"
#include <Windows.h>
#include <QGraphicsItemAnimation>

QCCLScene::QCCLScene(QObject *parent)
	: QGraphicsScene(parent)
	, m_iStatus(INIT)
	, m_iBlockCount(cxBlocks * cyBlocks)
	, m_background(":/other/background.png")
{

	QTimer* qTimer = new QTimer(this);
	connect(qTimer, SIGNAL(timeout()), this, SLOT(gameMain()));
	qTimer->start(1000 / 30);
}

QCCLScene::~QCCLScene()
{

}

/// ��
void QCCLScene::setPicSets(QStringList images)
{
	m_imageList = images;
}

void QCCLScene::gameMain()
{
	switch (m_iStatus)
	{
	case INIT:
		{
			break;
		}
	case RUNING:
		{
			// ʱ���þ�����Ϸ����
			if (m_timeBar->isFinished())
				m_iStatus = LOSE;

			// �жϷ����Ƿ������ȥ
			if (isBlocksRemovable())
			{
				// ������ȥ
				doRemove();
			}
			else if (m_selectedBlocks.count() == 2)
			{
				// ������ȥ
				doError();
			}

			// �ж������Ƿ����
			if (m_iBlockCount == 0)
				m_iStatus = WIN;

			break;
		}
	case WIN:
		{
			m_score->addScore(m_timeBar->getLastTime());
			m_timeBar->reset();
			addItem(new QCCLookText(tr("YOU WIN!"), QRectF(-Width / 2, -Height / 2, Width, Height)));
			// �ύ����
			emit emitScore(m_score->getScore());
			m_iStatus = INIT;
			break;
		}
	case LOSE:
		{
			// �Ƴ�ʣ�෽��
			for (int i = 0; i != m_pBlocks.count(); i++)
			{
				if (m_pBlocks[i] != NULL)
					removeItem(m_pBlocks[i]);
			}

			removeItem(m_timeBar);
			addItem(new QCCLookText(tr("YOU LOSE!"), QRectF(-Width / 2, -Height / 2, Width, Height)));
			m_iStatus = INIT;
			break;
		}
	}

	advance();
}

void QCCLScene::gameStart()
{
	initBlocks();
	initTimer();
	initScore();
	setBlockAnimation();

	setGameStatus(RUNING);
}

// ��ʼ������
void QCCLScene::initBlocks()
{
	// �������item
	while (items().count() != 0)
		removeItem(items()[0]);

	// ��ʼ������ֱ���ɽ�
	while (!isSovable())
	{
		// ���item
		while (items().count() != 0)
			removeItem(items()[0]);

		// ��ʼ����ǩ��
		QList<int> idBox;
		srand(GetTickCount());
		for (int i = 0; i != cxBlocks * cyBlocks / 2; i++)
		{
			int qRandowmPicNum = rand() % m_imageList.count();
			idBox.append(qRandowmPicNum);
			idBox.append(qRandowmPicNum);
		}

		int x = 0, y = 0;
		m_pBlocks.clear();
		for (int k = 0; k < cxBlocks * cyBlocks; k++)
		{
			QCCLookItem* itemPointer;
			// �ӳ�ǩ���������һ��ͼƬ,������id
			int qRandowmPicNum = rand() % idBox.count();
			itemPointer = new QCCLookItem(m_imageList[idBox[qRandowmPicNum]]);
			itemPointer->setID(idBox[qRandowmPicNum]);
			// �ӳ�ǩ����ȥ�������ǩ
			idBox.removeAt(qRandowmPicNum);

			addItem(itemPointer);
			m_pBlocks.append(itemPointer);
			itemPointer->setIndex(y * cxBlocks + x);
			itemPointer->setPos(-Width / 2 + x * BlockSize + BlockSize / 2, -Height / 2 + y * BlockSize + BlockSize / 2);

			if (x == cxBlocks - 1)
			{
				x = 0;
				y++;
			}
			else
				x++;
		}
	}

	// �޸ķ���״̬Ϊnormal
	for (int i = 0; i != items().count(); i++)
	{
		QCCLookItem* qItemPointer = static_cast<QCCLookItem*>(items().at(i));
		qItemPointer->setStatus(QCCLookItem::NORMAL);
	}

	// ��ʼ��������
	m_iBlockCount = cxBlocks * cyBlocks;
}

void QCCLScene::initTimer()
{
	// ��ʼ��ʱ��
	m_timeBar = new QCCLookTimeBar(QRectF(-Width / 2 + 100, -Height / 2 - Margin + 40, Width - 400, Margin - 80), Time);
	addItem(m_timeBar);
	m_timeBar->start();
	QGraphicsItem* clockPic = addPixmap(QPixmap(":/other/clock.png"));
	clockPic->setPos(-Width / 2, -Height / 2 - Margin + 10);
}

void QCCLScene::initScore()
{
	// ��ʼ������
	QGraphicsItem* scorePic = addPixmap(QPixmap(":/other/score.png"));
	scorePic->setPos(Width / 2 - 260, -Height / 2 - Margin + 15);
	m_score = new QCCLookScore(QRectF(Width / 2 - 180, -Height / 2 - Margin + 25, 150, 60));
	addItem(m_score);
}

// ��ȡ��ʾ
void QCCLScene::getTip()
{
	m_keyList.clear();
	QList<QGraphicsItem*> itemList = items();
	if (!items().count())
		return;

	// ��items����
	for (QList<QGraphicsItem*>::iterator i = itemList.begin(); i != itemList.end(); i++)
	{
		QCCLookItem* qItemPointer = static_cast<QCCLookItem*>(*i);
		if (qItemPointer->type() == QGraphicsItem::UserType + 1)
			m_keyList.insert(qItemPointer->getID(), qItemPointer);
	}

	// �����Ƿ����ҵ�����ȥ�ķ���
	bool bFlag = false;
	QList<int> keys = m_keyList.uniqueKeys();

	for (QList<int>::iterator k = keys.begin(); k != keys.end(); k++)
	{
		// �ھ�����ͬid��item����������ȥ�ķ���
		QList<QCCLookItem*> items = m_keyList.values(*k);
		int i, j;

		// �ж��Ƿ��ҵ�����ȥ�ķ��飬�������¼Ϊi,j
		for (i = 0; i != items.count() - 1;i++)
		{
			j = i + 1;
			for (; j != items.count(); j++)
			{
				if (isBlockRemovable(items[i]->pos(), items[j]->pos()))
				{
					bFlag = true;
					break;
				}
			}

			if (bFlag)
				break;
		}

		// �ҵ����ǳ������˳�ѭ��
		if (bFlag)
		{
			items[i]->setStatus(QCCLookItem::TIP);
			items[j]->setStatus(QCCLookItem::TIP);
			break;
		}
	}
}

/// �ӿ�
// ��ӱ�ѡ�еķ���
bool QCCLScene::addSelectedBlocks(QCCLookItem* item)
{
	if (m_selectedBlocks.count() == 2)
		return false;
	else
	{
		m_selectedBlocks.append(item);
		return true;
	}
}

// ɾ����ѡ�еķ���
bool QCCLScene::removeSelectedBlocks(QCCLookItem* item)
{
	int iCount = m_selectedBlocks.count();

	if (iCount == 0)
		return false;

	for (int i = 0; i < m_selectedBlocks.count(); i++)
		if (m_selectedBlocks[i] == item)
		{
			m_selectedBlocks.removeAt(i);
			return true;
		}

	return false;
}

///�麯������
void QCCLScene::drawBackground(QPainter *painter, const QRectF &rect)
{
	QRectF targetRect = QRectF(-Width / 2 - Margin, -Height / 2 - Margin, Width + Margin * 2, Height + Margin * 2);
	painter->drawPixmap(targetRect, m_background, m_background.rect());
}

/// ˽�к���
bool QCCLScene::isBlocksRemovable()
{
	if (m_selectedBlocks.count() != 2)
		return false;
	else
	{
		if (m_selectedBlocks[0]->getID() != m_selectedBlocks[1]->getID())
			return false;

		// ���·�������¼���
		m_lPoints.clear();

		QPointF i(m_selectedBlocks.at(0)->pos()), j(m_selectedBlocks.at(1)->pos());
		
		return isBlockRemovable(i, j);
	}
}

void QCCLScene::addLines()
{
	QPainterPath qPath;

	qPath.moveTo(m_selectedBlocks.at(0)->pos());

	for (int i = 0; i != m_lPoints.count(); i++)
	{
		qPath.lineTo(m_lPoints[i]);
	}

	qPath.lineTo(m_selectedBlocks.at(1)->pos());
	m_line = new QCCLookLine(qPath);
	addItem(m_line);
}

bool QCCLScene::isBlockRemovable(QPointF i, QPointF j)
{
	if (isInLine(i, j))
	{
		// ֱ����ͨ��ͨ�������۵���ͨ
		if (isAbleToLine(i , j)
			|| isAbleToCorner2(i, j))
			return true;
		else
			return false;
	}
	// ���㲻��һ��ֱ����
	else
	{
		// ͨ��һ���������۵���ͨ
		if (isAbleToCorner(i, j)
			|| isAbleToCorner2(i, j))
		{
			return true;
		}
		else
			return false;
	}
}

bool QCCLScene::isInLine(QPointF i, QPointF j)
{
	if (i.x() == j.x() || i.y() == j.y())
		return true;
	else
		return false;
}

bool QCCLScene::isAbleToLine(QPointF i, QPointF j)
{
	if (i.x() == j .x())
	{
		for (int y = MIN(i.y(), j.y()) + BlockSize; y != MAX(i.y(), j.y()); y += BlockSize)
		{
			if (!isSpace(QPointF(i.x(), y)))
				return false;
		}
	}
	else if (i.y() == j.y())
	{
		for (int x = MIN(i.x(), j.x()) + BlockSize; x != MAX(i.x(), j.x()); x += BlockSize)
		{
			if (!isSpace(QPointF(x, i.y())))
				return false;
		}
	}
	else
		return false;

	return true;
}

bool QCCLScene::isAbleToCorner(QPointF i, QPointF j)
{
	if (isInLine(i, j))
		return false;

	QPointF qCornerPoint[2] = {QPointF(i.x(), j.y()), QPointF(j.x(), i.y())};
	
	for (int k = 0; k != 2; k++)
	{

		if (!isSpace(qCornerPoint[k]))
			continue;
		if (isAbleToLine(qCornerPoint[k], i) && isAbleToLine(qCornerPoint[k], j))
		{
			m_lPoints.append(qCornerPoint[k]);
			return true;
		}
	}
	return false;
}

bool QCCLScene::isAbleToCorner2(QPointF i, QPointF j)
{
	// ����Ѱ��·��
	for (int k = i.y() - BlockSize; i.x() != j.x() && k > -Height / 2 - Margin; k -= BlockSize)
	{
		if (!isSpace(QPointF(i.x(), k)))
			break;

		if (isAbleToCorner(QPointF(i.x(), k), j))
		{
			m_lPoints.prepend(QPointF(i.x(), k));
			return true;
		}
	}

	// ����Ѱ��
	for (int k = i.y() + BlockSize; i.x() != j.x() &&  k < Height / 2 + Margin; k += BlockSize)
	{
		if (!isSpace(QPointF(i.x(), k)))
			break;

		if (isAbleToCorner(QPointF(i.x(), k), j))
		{
			m_lPoints.prepend(QPointF(i.x(), k));
			return true;
		}
	}

	// ����Ѱ��
	for (int k = i.x() - BlockSize; i.y() != j.y() && k > -Width / 2 - Margin; k -= BlockSize)
	{
		if (!isSpace(QPointF(k, i.y())))
			break;

		if (isAbleToCorner(QPointF(k, i.y()), j))
		{
			m_lPoints.prepend(QPointF(k, i.y()));
			return true;
		}
	}

	// ����Ѱ��
	for (int k = i.x() + BlockSize; i.y() != j.y() && k < Width / 2 + Margin; k += BlockSize)
	{
		if (!isSpace(QPointF(k, i.y())))
			break;

		if (isAbleToCorner(QPointF(k, i.y()), j))
		{
			m_lPoints.prepend(QPointF(k, i.y()));
			return true;
		}
	}

	return false;
}

bool QCCLScene::isSpace(QPointF point)
{
	QList<QGraphicsItem*> itemList = items(point);
	if (itemList.count() == 0)
		return true;

	// �Ƿ���itemҲ��Ϊ�յ�
	int iBlockCount = 0;
	for (int i = 0; i != itemList.count(); i++)
		if (itemList[i]->type() == QGraphicsItem::UserType + 1)
			iBlockCount++;
	if (!iBlockCount)
		return true;

	QCCLookItem* qItem = static_cast<QCCLookItem*>(itemList[0]);

	if (qItem->getStatus() < QCCLookItem::FADING)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool QCCLScene::isSovable()
{
	m_keyList.clear();

	// ��items��id����
	QList<QGraphicsItem*> itemList = items();
	if (!items().count())
		return false;

	for (QList<QGraphicsItem*>::iterator i = itemList.begin(); i != itemList.end(); i++)
	{
		QCCLookItem* qItemPointer = static_cast<QCCLookItem*>(*i);
		m_keyList.insert(qItemPointer->getID(), qItemPointer);
	}

	// ���
	while(!m_keyList.isEmpty())
	{
		// �����Ƿ��з����ڴ˴�ѭ����ȥ
		bool bFlag = false;

		QList<int> keys = m_keyList.uniqueKeys();
		for (QList<int>::iterator k = keys.begin(); k != keys.end(); k++)
		{
			// �ھ�����ͬid�ķ�������������ȥ��

			// �����Ƿ��з�������ѭ������ȥ
			bool bSubFlag = false;
			QList<QCCLookItem*> items = m_keyList.values(*k);
			int i, j;

			// �ж��Ƿ���������ͨ���������¼Ϊi,j
			for (i = 0; i != items.count() - 1;i++)
			{
				j = i + 1;
				for (; j != items.count(); j++)
				{
					if (isBlockRemovable(items[i]->pos(), items[j]->pos()))
					{
						// �ҵ���ͨ�ĵ�
						bFlag = true;
						bSubFlag = true;
						break;
					}
				}
				if (bSubFlag)
					break;
			}

			// ɾ����ͨ�ĵ�
			if (bSubFlag)
			{
				m_keyList.remove(*k, items[j]);
				m_keyList.remove(*k, items[i]);
				items[i]->setStatus(QCCLookItem::TESTING);
				items[j]->setStatus(QCCLookItem::TESTING);
			}
		}

		// ���з��鶼�����������޽�
		if (!bFlag)
			return false;
	}

	return true;
}

void QCCLScene::doRemove()
{
	addLines();
	m_selectedBlocks.at(0)->setStatus(QCCLookItem::FADING);
	m_selectedBlocks.at(1)->setStatus(QCCLookItem::FADING);
	m_selectedBlocks.clear();
	// �ӷ�
	m_score->addScore(2);
}

void QCCLScene::doError()
{
	m_selectedBlocks.at(0)->setToggle(false);
	m_selectedBlocks.at(1)->setToggle(false);
	m_selectedBlocks.clear();
	// ����
	m_score->addScore(-1);
}

void QCCLScene::setBlockAnimation()
{
	for (int i = 0; i != m_pBlocks.count(); i++)
	{
		QGraphicsItem *block = m_pBlocks[i];

		QTimeLine *timer = new QTimeLine(500);
		timer->setFrameRange(0, 100);

		QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
		animation->setItem(block);
		animation->setTimeLine(timer);
		QPointF oriPos = block->pos();
		block->setPos(oriPos.x() - Width, oriPos.y());

		for (int i = 0; i < 200; ++i)
			animation->setPosAt(i / 200.0, QPointF(oriPos.x() - Width + i * Width / 200.0, oriPos.y()));
		animation->setPosAt(1, oriPos);

		timer->setCurveShape(QTimeLine::EaseInCurve);
		timer->start();
	}
}
