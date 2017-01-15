#include "terminaldockwidget.h"

TerminalDockWidget* terminal;

TerminalDockWidget::TerminalDockWidget(QWidget *parent)
    : QDockWidget(parent)
{
    repl = new ReplWidget(this);
    setWidget(repl);
    searchPhrase = false;
    wordsToSearch = 0;

    connect(repl   , SIGNAL(command(QString)),
            this   , SLOT(procces(QString)));

    connect(this   , SIGNAL(resultReady(QString)),
            repl   , SLOT(result(QString)));

    connect(this   , SIGNAL(sig_showWords()),
            search , SLOT(slt_showWords()),
            Qt::QueuedConnection);

    connect(this   , SIGNAL(sig_searchWord(QString)),
            search , SLOT(slt_search(QString)),
            Qt::QueuedConnection);

    connect(search , SIGNAL(sig_wordFinished()),
            this   , SLOT(slt_searchFinished()),
            Qt::QueuedConnection);

}

void TerminalDockWidget::procces(QString _commad) {
    // TODO : proccec commands
    QStringList comList = _commad.simplified().split(" ");
    comList.removeAll(" ");

    if (comList.size()) {
        QString cmd = comList[0];
        comList.removeAt(0);
        if (cmd == "check") {
            proccesCheck(comList);
        } else if (cmd == "del") {
            proccesDel(comList);
        } else if (cmd == "find") {
            proccesFind(comList);
        } else if (cmd == "exit") {
            qApp->exit();
        } else {
            emit resultReady("err : command not found  ->  " + _commad);
        }
        return;
    }
    emit resultReady("err : command not found!!!");

}

void TerminalDockWidget::proccesCheck(QStringList & _cmd) {
    if (_cmd.size() == 1) {
        if (checkFSM(_cmd[0])) {

            emit resultReady("True");

        } else {

            emit resultReady("False");

        }
    } else {
        emit resultReady("err : you should enter just one string");
    }
}

bool TerminalDockWidget::checkFSM(QString & _str) {
    int s = tabDock->getcmb_Start() -> currentIndex();
    int e = tabDock->getcmb_end()   -> currentIndex();

    Queue q;
    for(int i {}; i < _str.size(); i++) {
        q.enqueue(_str.at(i).toLatin1());
    }
    int i {0};
    while (!q.isEmpty()) {
        char c = q.dequeue();
        for (int j{}; j < tabDockRight->getModel()->columnCount(); j++) {
            if ( tabDockRight->getModel()->item(s,j)->text().contains(c) ) {
                qDebug() << j;
                s = j;
            }
        }
    }

}

void TerminalDockWidget::proccesDel(QStringList & _cmd) {

}


void TerminalDockWidget::proccesFind(QStringList & _cmd) {

}

void TerminalDockWidget::slt_searchFinished() {
    wordsToSearch--;
    if (wordsToSearch == 0) {
        emit resultReady ("Search is Done. ");
    }
}
