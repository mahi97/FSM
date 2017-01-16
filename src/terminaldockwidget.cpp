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
    btCheckFSM(-1, s, e, done, q);

    return done;

}

void TerminalDockWidget::btCheckFSM(int index,
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

    if (promisingCheckFSM(index, s, e, c.front())){
        if (index != -1)
            c.dequeue();
        qDebug() << tabDock->getModel()->columnCount();
        for (int i{}; i < tabDock->getModel()->columnCount() ; i++) {
            qDebug() << "sic" << s << " " << i << " " << c.size();
            btCheckFSM(i, s, e, done, c);
        }

    }
}

bool TerminalDockWidget::promisingCheckFSM(int _i,
                                           int& s, int e, char c) {
    if (_i == -1) return true;
    if (tabDock->getModel()->item(_i, s)->text().contains(c)) {
        s = _i;
        return true;

    } else {
        return false;

    }
}

QStringList TerminalDockWidget::findLoops() {
    QStandardItemModel*& rModel = tabDock->getModel();
    int size = tabDock->getState();
    n = size;
    for (int i{}; i < size; i++) {
        for (int j{}; j < size; j++) {
            if (rModel->item(i + 1, j + 1)->text() != "-") {
                graf[i].adj.push_back(j);
            }
        }
    }
    components.clear();
    tarjan();

    return components;

}

void TerminalDockWidget::tarjan()
{
    Indices = 0;
    while (!m_stack.empty()) {
        m_stack.pop();
    }

    for (int i=n;i>0;i--) {
        onStack[i] = LowLink[i] = Index[i] = 0;
    }

    numComponents = 0;
    for (int i{}; i < n; i++) {
        if (Index[i] == 0) {
            tarjanDFS(i);
        }

    }
}

void TerminalDockWidget::tarjanDFS(int i) {
    Index[i] = ++Indices;
    LowLink[i] = Indices;
    m_stack.push(i);
    onStack[i] = true;
    for (int j{} ; j < graf[i].adj.size() ; j++)
    {
        int w = graf[i].adj[j];
        if (Index[w] == 0) {
            tarjanDFS(w);
            LowLink[i] = min(LowLink[i], LowLink[w]);

        } else if (onStack[w]) {
            LowLink[i] = min(LowLink[i], Index[w]);

        }
    }
    if (LowLink[i] == Index[i]) {
        int w = 0;
        QString com;
        com.append(" ");
        do {
            w = m_stack.top();
            m_stack.pop();

            component[w] = numComponents;
            onStack[w]=false;
            com.append(QString("%1 ").arg(w));

        } while (i != w && !m_stack.empty());

        components.append(com);
        numComponents++;

    }

}



void TerminalDockWidget::deleteLoops() {

}

void TerminalDockWidget::proccesDel(QStringList & _cmd) {
    if (_cmd.size() == 1) {
        if (_cmd[0] == "loop") {
            deleteLoops();
            emit resultReady("Deleted !");
        } else {
            emit resultReady("err : just write `del loop`");

        }
    } else {
        emit resultReady("err: just write `del loop`");
    }
}


void TerminalDockWidget::proccesFind(QStringList & _cmd) {
    if (_cmd.size() == 1) {
        if (_cmd[0] == "loop") {
            loops = findLoops();
            QString tStr;
            Q_FOREACH(QString str, loops) {
                tStr.append("(");
                tStr.append(str);
                tStr.append("), ");
            }
            emit resultReady(tStr);
        } else {
            emit resultReady("err : just write `find loop`");
        }
    } else {
        emit resultReady("err : just write `find loop`");
    }
}

void TerminalDockWidget::slt_searchFinished() {
    wordsToSearch--;
    if (wordsToSearch == 0) {
        emit resultReady ("Search is Done. ");
    }
}
