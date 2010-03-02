#ifndef __MainWindow_h__
#define __MainWindow_h__

#include <QMainWindow>
#include "RenderWidget0.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

private slots:
	void startAnimation();
	void stopAnimation();
    void turnLeft();
    void turnRight();
    void turnUp();
    void turnDown();
    void toggleFly();
    void speedUp();
    void speedDown();

private:
	void createMenus();

	QMenu *fileMenu;
	QMenu *animationMenu;
    QMenu *flyingMenu;
	QAction *exitAct;
	QAction *startAct;
	QAction *stopAct;
    QAction *turnU;
    QAction *turnD;
    QAction *turnL;
    QAction *turnR;
    QAction *toggleF;
    QAction *speedU;
    QAction *speedD;

	RenderWidget0 *renderWidget;
};

#endif