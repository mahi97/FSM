#include "tabdockwidget.h"

TabDockWidget* tabDock;

TabDockWidget::TabDockWidget(QWidget *parent)
    : QDockWidget(parent) {
    w = new QWidget(this);
    QVBoxLayout *control = new QVBoxLayout(w);
    table = new QTableView(this);
    model = new QStandardItemModel(this);
    table->setModel(model);

    fillLayout(control);

    w->setLayout(control);
    setWidget(w);

    signalCounter = 0;

    // Conecctions
    connect(btnBrowse        , SIGNAL(clicked(bool)),
            this             , SLOT(slt_browse()));
    connect(btnBuild         , SIGNAL(clicked(bool)),
            this             , SLOT(slt_build()));


    connect(btnBuild, SIGNAL(clicked(bool)), monitor, SLOT(slt_show()));
}

TabDockWidget::~TabDockWidget() {

}

void TabDockWidget::fillLayout(QVBoxLayout *_layout) {

    btnBrowse = new QPushButton("Browse", this);
    btnBuild = new QPushButton("Build", this);
    btnHelp = new QPushButton("Help", this);
    btnReset = new QPushButton("Reset", this);
    lineEditDirectory = new QLineEdit(this);
    lineEditDirectory->setReadOnly(true);
    QHBoxLayout *browse = new QHBoxLayout;
    QHBoxLayout *btns = new QHBoxLayout;
    QHBoxLayout *combo = new QHBoxLayout;
    browse->addWidget(lineEditDirectory);
    browse->addWidget(btnBrowse);

    btns->addWidget(btnBuild);
    btns->addWidget(btnReset);
    btns->addWidget(btnHelp);

    QLabel *s = new QLabel("Start : ");
    QLabel *e = new QLabel("End : ");

    start = new QComboBox(this);
    end   = new QComboBox(this);


    combo->addWidget(s);
    combo->addWidget(start);
    combo->addWidget(e);
    combo->addWidget(end);

    _layout->addLayout(browse);
    _layout->addWidget(table);
    _layout->addLayout(combo);
    _layout->addLayout(btns);
    _layout->setAlignment(browse, Qt::AlignTop);

}

/* SLOTS */

void TabDockWidget::slt_browse() {
    QString tempDir;
    QFileDialog fd;
    tempDir = fd.getOpenFileName(this,
                                      "Please choose a file",
                                      "");
    if (tempDir.size() >= 3) {
        directory = tempDir;
        lineEditDirectory->setText(tempDir);
        slt_open();
    }
}


void TabDockWidget::slt_open() {
    model->clear();
    QFile f(directory);
    f.open(QIODevice::ReadOnly);
    proccesFile(f);
    for (int i{}; i < m_state; i++) {
        start->addItem(QString("%1").arg(i));
        end->addItem(QString("%1").arg(i));
    }
    start->setCurrentIndex(0);
    end->setCurrentIndex(m_state - 1);
    emit sig_fileOpend();
    f.close();
}


void TabDockWidget::slt_build() {

    emit sig_build();
}

void TabDockWidget::slt_buildComplete() {

    btnBuild->setEnabled(true);
}



void TabDockWidget::proccesFile(QFile & _file) {
    QList<QByteArray> first = _file.readLine().simplified().split(' ');
    QList<int> states;
    QList<QStandardItem*> firstRow;
    QStandardItem* state = new QStandardItem("State");
    firstRow.append(state);
    m_state = 0;
    Q_FOREACH(QByteArray word, first) {
        bool ok {false};
        int tState {word.toInt(&ok)};
        if (ok) {
            QStandardItem* item = new QStandardItem(QString("S : %1").arg(tState));
            states.append(tState);
            firstRow.append(item);
            m_state++;
        }
    }
    model->appendRow(firstRow);

    while(_file.canReadLine()) {
        QByteArray text = _file.readLine();
        if (text.size() < 5) break;
        QList<QByteArray> tLine = text.simplified().split(' ');

        QList<QStandardItem*> items;
        bool ok {false};
        int cur_state = tLine[0].toInt(&ok);
        if (!ok) qWarning() << "SomeThings wrong with input file";
        tLine.pop_front();
        QStandardItem* first_ = new QStandardItem(QString("S : %1").arg(cur_state));
        items.append(first_);

        Q_FOREACH (QByteArray word, tLine) {
            if (word.startsWith("(") && word.endsWith(")")) {
                word.chop(1);
                word.remove(0,1);
                QStandardItem *item = new QStandardItem(QString(word));
                items.append(item);
                QList<QByteArray> chars = word.split(',');
                QList<char> tChar;
                Q_FOREACH(QByteArray c, chars) {
                    tChar.append(c.at(0));
                }
            }
        }
        model->appendRow(items);
    }

}

void TabDockWidget::slt_reset() {
    // TODO : new reset for graphviz
}
