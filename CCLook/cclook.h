#ifndef CCLOOK_H
#define CCLOOK_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtOpenGL>
#include "ui_cclook.h"
#include "qcclscene.h"
#include "qaboutdlg.h"
#include "qscoredlg.h"
#include "qcclstat.h"

class CCLook : public QMainWindow
{
	Q_OBJECT

public:
    CCLook(QWidget *parent = 0,  Qt::WindowFlags flags = 0);
	~CCLook();

/// ��
public slots:
	// ��ʾ���ڶԻ���
	void showAbout();
	// ��ʾ���а�
	void showScore();
	// �ύ����
	void commitScore(int score);

/// ˽�к���
private:
	// ��ʼ��scene & view
	void initScene();
	// ��ʼ���˵���������
	void initAction();

private:
	Ui::CCLookClass ui;
	QCCLScene* m_scene;
	QGraphicsView* m_view;
	QCCLStat m_stat;
	QList<QScoreStruct> m_scoreList;
};

#endif // CCLOOK_H
