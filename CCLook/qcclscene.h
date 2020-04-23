/************************************************************
**
** @Name: ��Ϸ����
** @Description: ��Ҫ������Ϸ���߼�����
** @Date: 2013/04/19 19:33
**
*************************************************************/

#ifndef QCCLSCENE_H
#define QCCLSCENE_H

#include <QGraphicsScene>
#include "globaldefines.h"
#include "qcclookitem.h"
#include "qcclookline.h"
#include "qcclooktext.h"
#include "qcclooktimebar.h"
#include "qcclookscore.h"


template<typename T> inline T MAX(T a, T b){return ((a > b) ? a : b);}
template<typename T> inline T MIN(T a, T b){return ((a < b) ? a : b);}

class QCCLookItem;
class QCCLScene : public QGraphicsScene
{
	Q_OBJECT


public:
	enum gameStatus{INIT, RUNING, WIN, LOSE};
	QCCLScene(QObject *parent);
	~QCCLScene();

/// �ź�
signals:
	// ���ɼ����͸����а�
	void emitScore(int);

/// ��
public slots:
	// ������Ϸ״̬
	void setGameStatus(gameStatus status)
	{
		m_iStatus = status;
	}
	// ���÷���ͼƬ
	void setPicSets(QStringList images);
	// ������ѭ��
	void gameMain();
	// ��Ϸ��ʼ
	void gameStart();
	// ��ʼ������
	void initBlocks();
	// ��ʼ��ʱ��
	void initTimer();
	// ��ʼ������
	void initScore();
	// ��ȡ��ʾ
	void getTip();

/// �ӿ�
public:
	// ���ӱ�ѡ�еķ���,��cclookitem����
	bool addSelectedBlocks(QCCLookItem* item);
	// ���ٱ�ѡ�еķ���
	bool removeSelectedBlocks(QCCLookItem* item);
	// ����ʣ�෽����
	void reduceBlock(int index)
	{
		m_pBlocks[index] = NULL;
		--m_iBlockCount;
	}

/// �麯������
protected:
	void drawBackground(QPainter *painter, const QRectF &rect);

/// ˽�к���
private:
	// �жϷ����Ƿ������ȥ
	bool isBlocksRemovable();
	// ��ӷ���֮�������
	void addLines();
	// �ж������Ƿ����ȥ
	bool isBlockRemovable(QPointF i, QPointF j);
	// �ж������Ƿ���һ��ֱ����
	bool isInLine(QPointF i, QPointF j);
	// �ж�����֮���Ƿ����ͨ��һ��ֱ��
	bool isAbleToLine(QPointF i, QPointF j);
	// �ж�����֮���Ƿ��ͨ��һ��ֱ������
	bool isAbleToCorner(QPointF i, QPointF j);
	// �ж�����֮���Ƿ��ͨ������ֱ������
	bool isAbleToCorner2(QPointF i, QPointF j);
	// �ж�ָ��λ���Ƿ����
	bool isSpace(QPointF point);
	// �жϵ�ǰ�����Ƿ��н�
	bool isSovable();
	// ������ȥʱ�Ĵ���
	void doRemove();
	// ������ȥʱ�Ĵ���
	void doError();
	// �����ƶ���̬Ч��
	void setBlockAnimation();

private:
	int m_iStatus;								// ��Ϸ״̬
	QList<QCCLookItem*> m_pBlocks;				// �洢����ָ��
	QList<QCCLookItem*> m_selectedBlocks;		// �洢��ѡ�еķ���
	QCCLookLine* m_line;						// ����
	QList<QPointF> m_lPoints;					// �洢·��
	QStringList m_imageList;					// ͼƬ·��
	QMultiMap<int, QCCLookItem*> m_keyList;		// �洢����ͬһid�ķ����б�
	int m_iBlockCount;							// ʣ��ש����
	QCCLookTimeBar* m_timeBar;					// ʱ�������
	QCCLookScore* m_score;						// ����
	QPixmap m_background;						// ����ͼƬ
};

#endif // QCCLSCENE_H
