#ifndef TERMINALDOCKWIDGET_H
#define TERMINALDOCKWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QDockWidget>


#include "base.h"
#include "monitor.h"
#include "tabdockright.h"
#include "tabdockwidget.h"
#include "terminal/ReplWidget.h"
#include "dataStructures/istack.h"
#include "dataStructures/queue.h"

#define MAX_N 20001
#define INF 987654321

typedef long long lld;


class TerminalDockWidget : public QDockWidget {

    Q_OBJECT

public:
    TerminalDockWidget(QWidget* parent);
    ReplWidget *repl;
private:

    void proccesCheck(QStringList&);
    void proccesDel(QStringList&);
    void proccesFind(QStringList&);

    bool checkFSM(QString&);
    void btCheckFSM(int index, int s, int e, bool &done, Queue c);
    bool promisingCheckFSM(int _i, int &s, int e, char c);

    QStringList findLoops();
    void tarjan();
    void tarjanDFS(int i);
    void deleteLoops();


    /////// Prim
    ///
    ///
    ///

    void primMST(int **graph, int size);
    int minKey(int key[], bool mstSet[], int size);

    ///
    ///
    ///
    ////// Prim

    int wordsToSearch;
    bool searchPhrase;

    QStringList loops;


    ////// TARJAN
    ///
    ///
    ///

    int min(int a, int b) {
        return ((a < b) ? a : b);
    }

    int n;
    struct Node {
        QVector<int> adj;
    };
    Node graf[MAX_N];
    IStack m_stack;
    bool onStack[MAX_N];
    int Indices;
    int Index[MAX_N];
    int LowLink[MAX_N];
    int component[MAX_N];
    int numComponents;
    QStringList components;

    ///
    ///
    ///
    ////// TARJAN



public slots:
    void procces(QString);
    void slt_searchFinished();
signals:
    void resultReady(QString);
    void sig_add(QString);
    void sig_update(QString);
    void sig_search();
    void sig_list();
    void sig_del(QString);
    void sig_showWords();
    void sig_searchWord(QString);
};

extern TerminalDockWidget* terminal;

#endif // TERMINALDOCKWIDGET_H
