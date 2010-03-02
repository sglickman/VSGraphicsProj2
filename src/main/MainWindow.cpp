#include <QtGui>
#include "MainWindow.h"

MainWindow::MainWindow()
{
	createMenus();
	setWindowTitle("CSCI330SP09 Rendering Engine");

	// the menu bar (21 pixels) is part of the widget size...
	resize(512,512+21);	
	
	renderWidget = new RenderWidget0();
	setCentralWidget(renderWidget);
}

void MainWindow::createMenus()
{
	exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	startAct = new QAction(tr("Start animation"), this);
    startAct->setShortcut(tr("Ctrl+p"));
    connect(startAct, SIGNAL(triggered()), this, SLOT(startAnimation()));
	
	stopAct = new QAction(tr("St&op animation"), this);
    stopAct->setShortcut(tr("Ctrl+l"));
    connect(stopAct, SIGNAL(triggered()), this, SLOT(stopAnimation()));
    
    toggleF = new QAction(tr("Toggle flying"), this);
    toggleF->setShortcut(tr("Ctrl+t"));
    connect(toggleF, SIGNAL(triggered()), this, SLOT(toggleFly()));
    
    turnL = new QAction(tr("Turn left"), this);
    turnL->setShortcut(tr("Ctrl+a"));
    connect(turnL, SIGNAL(triggered()), this, SLOT(turnLeft()));
    
    turnR = new QAction(tr("Turn right"), this);
    turnR->setShortcut(tr("Ctrl+d"));
    connect(turnR, SIGNAL(triggered()), this, SLOT(turnRight()));
    
    turnU = new QAction(tr("Turn up"), this);
    turnU->setShortcut(tr("Ctrl+w"));
    connect(turnU, SIGNAL(triggered()), this, SLOT(turnUp()));
    
    turnD = new QAction(tr("Turn down"), this);
    turnD->setShortcut(tr("Ctrl+s"));
    connect(turnD, SIGNAL(triggered()), this, SLOT(turnDown()));
    
    speedU = new QAction(tr("Speed up"), this);
    speedU->setShortcut(tr("Ctrl+i"));
    connect(speedU, SIGNAL(triggered()), this, SLOT(speedUp()));

    speedD = new QAction(tr("Speed down"), this);
    speedD->setShortcut(tr("Ctrl+k"));
    connect(speedD, SIGNAL(triggered()), this, SLOT(speedDown()));
    
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);

    animationMenu = menuBar()->addMenu(tr("&Animation"));
    animationMenu->addAction(startAct);
    animationMenu->addAction(stopAct);
    
    flyingMenu = menuBar()->addMenu(tr("&Flying"));
    flyingMenu->addAction(toggleF);
    flyingMenu->addAction(turnL);
    flyingMenu->addAction(turnR);
    flyingMenu->addAction(turnU);
    flyingMenu->addAction(turnD);
    flyingMenu->addAction(speedU);
    flyingMenu->addAction(speedD);
}

void MainWindow::startAnimation()
{
	renderWidget->startAnimation();
}

void MainWindow::stopAnimation()
{
	renderWidget->stopAnimation();
}

void MainWindow::turnLeft()
{
    renderWidget->turnLeft();
}

void MainWindow::turnRight()
{
    renderWidget->turnRight();
}

void MainWindow::turnUp()
{
    renderWidget->turnUp();
}

void MainWindow::turnDown()
{
    renderWidget->turnDown();
}

void MainWindow::toggleFly()
{
    renderWidget->toggleFly();
}

void MainWindow::speedUp()
{
    renderWidget->speedUp();
}

void MainWindow::speedDown()
{
    renderWidget->speedDown();
}