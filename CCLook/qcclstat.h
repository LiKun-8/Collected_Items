/************************************************************
**
** @Name: ���а�
** @Description: ���ڲ�����ʷ��¼
** @Date: 2013/04/19 19:26
**
*************************************************************/

#ifndef QCCLSTAT_H
#define QCCLSTAT_H

#include <QtWidgets>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

struct QScoreStruct
{
	QString m_userName;
	int m_userScore;
};

class QCCLStat : public QObject
{
	Q_OBJECT

public:
	QCCLStat(QObject *parent);
	~QCCLStat();

/// �ӿ�
public:
	QList<QScoreStruct> getUserScore() const;
	void setUserScore(QList<QScoreStruct> list);

private:
};

#endif // QCCLSTAT_H
