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

    connect(this   , SIGNAL(resualtReady(QString)),
            repl   , SLOT(result(QString)));

    connect(this   , SIGNAL(sig_add(QString)),
            tabDock, SLOT(slt_update(QString)));

    connect(this   , SIGNAL(sig_update(QString)),
            tabDock, SLOT(slt_update(QString)));

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
//    QStringList comList = _commad.split(" ");
//    comList.removeAll(" ");

//    if (comList.size()) {
//        QString cmd = comList[0];
//        comList.removeAt(0);
//        if (cmd == "add") {
//            proccesAdd(comList);
//        } else if (cmd == "del") {
//            proccesDel(comList);
//        } else if (cmd == "update") {
//            proccesUpdt(comList);
//        } else if (cmd == "list") {
//            proccesList(comList);
//        } else if (cmd == "search") {
//            proccesSrch(comList);
//        } else if (cmd == "exit") {
//            qApp->exit();
//        } else {
//            emit resualtReady("err : command not found  ->  " + _commad);
//        }
//        return;
//    }
    emit resualtReady("err : command not found!!!");

}

void TerminalDockWidget::slt_searchFinished() {
    wordsToSearch--;
    if (wordsToSearch == 0) {
        emit resualtReady("Search is Done. ");
    }
}
