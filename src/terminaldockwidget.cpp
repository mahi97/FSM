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
    int s = tabDock->getcmb_Start() -> currentIndex() + 1;
    int e = tabDock->getcmb_end()   -> currentIndex() + 1;

    Queue q;
    for(int i {}; i < _str.size(); i++) {
        q.enqueue(_str.at(i).toLatin1());
    }
    int i {0};
    int* arr = new int [tabDock->getState()];
    bool done;
    backTrack(-1, arr, s, e, done, q);

    return done;

//    while (!q.isEmpty()) {
//        char c = q.dequeue();
//        for (int j{}; j < tabDockRight->getModel()->columnCount(); j++) {
//            if ( tabDockRight->getModel()->item(s,j)->text().contains(c) ) {
//                qDebug() << j;
//                s = j + 1;
//            }
//        }
//    }
}

void TerminalDockWidget::backTrack(int index, int arr[],
                                   int s,     int e,
                                   bool& done, Queue c) {

    if (done) {
        return;
    }
    if (c.isEmpty()) {
        if (s == e || done) done = true;
        else done = false;
        return;
    }
    if (index > tabDock->getState()) {
        return;
    }

    if (promising(index, arr, s, e, c.front())){
        if (index != -1)
            c.dequeue();
        qDebug() << tabDock->getModel()->columnCount();
        for (int i{}; i < tabDock->getModel()->columnCount() ; i++) {
            qDebug() << "sic" << s << " " << i << " " << c.size();
            backTrack(i , arr, s, e, done, c);
        }

    }
}

bool TerminalDockWidget::promising(int _i, int arr[],
                                   int& s, int e, char c) {
    if (_i == -1) return true;
    if (tabDock->getModel()->item(_i, s)->text().contains(c)) {
        s = _i;
        qDebug() << "f" << s;
        return true;

    } else {
        return false;

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
