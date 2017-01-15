#ifndef TERMINALDOCKWIDGET_H
#define TERMINALDOCKWIDGET_H

#include <QQueue>
#include <QWidget>
#include <QTextEdit>
#include <QDockWidget>


#include "base.h"
#include "monitor.h"
#include "tabdockright.h"
#include "tabdockwidget.h"
#include "terminal/ReplWidget.h"

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
    void backTrack(int index, int arr[], int s, int e, bool &done, Queue c);
    bool promising(int _i, int arr[], int &s, int e, char c);

    int wordsToSearch;
    bool searchPhrase;

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
