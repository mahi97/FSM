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
//    int e = tabDock->getcmb_end()   -> currentIndex() + 1;
    QString e = tabDock->getcmb_end()->text();

    Queue q;
    for(int i {}; i < _str.size(); i++) {
        q.enqueue(_str.at(i).toLatin1());
    }
    int i {0};
    bool done {false};
    btCheckFSM(-1, s, e, done, q);

    return done;

}

void TerminalDockWidget::btCheckFSM(int index,
                                    int s,     QString e,
                                    bool& done, Queue c) {

    if (done) {
        return;
    }
    if (c.isEmpty()) {
        if (e.contains(QString("%1").arg(s - 1)) || done) done = true;
        else done = false;
        return;
    }
    if (index > tabDock->getState()) {
        return;
    }

    if (promisingCheckFSM(index, s, c.front())){
        if (index != -1)
            c.dequeue();
        for (int i{}; i < tabDock->getModel()->columnCount() ; i++) {
            btCheckFSM(i, s, e, done, c);
        }

    }
}

bool TerminalDockWidget::promisingCheckFSM(int _i,
                                           int& s, char c) {
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


    for (int i{}; i < size; i++)
        graf[i].adj.clear();



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

    for (int i{}; i < n; i++) {
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
    for (int j{} ; j < graf[i].adj.size() ; j++) {
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
            onStack[w] = false;
            com.append(QString("%1 ").arg(w));

        } while (i != w && !m_stack.empty());
        qDebug() << "cs " << com.size();
        qDebug() << "ci " << com.toInt();
        qDebug() << "tx " << tabDock->getModel()->item(com.toInt(), com.toInt())->text();

        if (com.size() != 3
        || tabDock->getModel()->item(com.toInt() + 1, com.toInt() + 1)->text() != "-") {
            components.append(com);
            numComponents++;
        }


    }

}



void TerminalDockWidget::deleteLoops() {
    QStandardItemModel*& rModel = tabDock->getModel();
    int size = tabDock->getState();

    int **graph = new int* [size];
    for (size_t i {}; i < size; i++) {
        graph[i] = new int[size];
        for (size_t j {}; j < size; j++) {
            if (rModel->item(j + 1, i + 1)->text() != "-"
            && i != j) {
                graph[i][j] = 100 - rModel->item(j + 1, i + 1)->text().size();

            } else {
                graph[i][j] = 0;

            }
        }
    }

    for (int i{}; i < size; i++) {
        for (int j{}; j < size; j++) {
            qDebug() << graph[i][j];
        }
        qDebug() << "---------------";
    }

    primMST(graph, size);

    for (int i{}; i < size; i++) {
        for (int j{}; j < size; j++) {
            if (!graph[i][j]) {
                rModel->item(i + 1, j + 1)->setText("-");
            }
            qDebug() << graph[i][j];
        }
        qDebug() << "---------------";
    }



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
            loops.clear();
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


int TerminalDockWidget::minKey(int key[], bool mstSet[], int size) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < size; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void TerminalDockWidget::primMST(int **graph, int size) {
    int  *parent = new int[size];
    int  *key    = new int[size];
    bool *mstSet = new bool[size];

    for (int i = 0; i < size; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
        parent[i] = 0;
    }


    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < size - 1; count++) {

        int u = minKey(key, mstSet, size);

        mstSet[u] = true;

        for (int v = 0; v < size; v++) {
            if (graph[u][v]
                    &&  mstSet[v] == false
                    &&  graph[u][v] <  key[v]) {

                parent[v]  = u;
                key[v] = graph[u][v];
            }
        }
    }


    qDebug() << "Edge           Weight";
    for (int i{}; i < size; i++) {
        for (int j{}; j < size; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 1; i < size; i++) {
        graph[i][parent[i]] = 1;
        qDebug() << "p " << parent[i];
        qDebug() << "i " << i;
        qDebug() << "g " << graph[i][parent[i]];
    }

    //     printMST(parent, size, graph);
}
