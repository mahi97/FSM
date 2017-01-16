#include "mainwindow.h"
#include "graphviz/gvc.h"
#include "graphviz/cgraph.h"
#include "graphviz/cdt.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {


    setFocus();

    tabDock = new TabDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, tabDock);
    initWidget(tabDock);

    tabDockRight = new TabDockRightWidget(this);
    initWidget(tabDockRight);
    addDockWidget(Qt::RightDockWidgetArea, tabDockRight);

    terminal = new TerminalDockWidget(this);
    initWidget(terminal);
    addDockWidget(Qt::BottomDockWidgetArea, terminal);

    monitor = new Monitor(this);
    initWidget(monitor);
    setCentralWidget(monitor);



    QLabel* lll = new QLabel("Hello Mahi :D", statusBar());
    statusBar()->addWidget(lll);


    /* Final */
//    this->showMaximized();
    this->setWindowTitle(QString("DS Project2 (%1)").arg(QString(REVNUM)));
}

MainWindow::~MainWindow() {

}

void MainWindow::initWidget(Monitor *_monitor) {
    _monitor->setMinimumSize(QSize(700, 500));
}

void MainWindow::initWidget(TabDockWidget *_tab) {
    _tab->setMinimumSize(QSize(300, 500));
    _tab->setMaximumSize(QSize(500, 700));
}

void MainWindow::initWidget(TerminalDockWidget *_terminal) {
    _terminal->setMinimumSize(QSize(800, 200));
}

void MainWindow::initWidget(TabDockRightWidget *_tab) {
    _tab->setMinimumSize(QSize(300, 500));
    _tab->setMaximumSize(QSize(500, 700));}
