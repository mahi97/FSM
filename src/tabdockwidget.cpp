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
    connect(this             , SIGNAL(sig_changeTree(ETree)),
            search           , SLOT(slt_chooseTree(ETree)));
    connect(this             , SIGNAL(sig_fileToBuild(File*)),
            search           , SLOT(slt_buildFile(File*)),
            Qt::QueuedConnection);
    connect(search           , SIGNAL(sig_summery(Summery*)),
            this             , SLOT(slt_buildComplete()),
            Qt::QueuedConnection);

    connect(btnReset         , SIGNAL(clicked(bool)),
            this             , SLOT(slt_reset()));

    connect(search           , SIGNAL(sig_searchFinished(SearchResult*)),
            this             , SLOT(slt_showLines(SearchResult*)));
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
    browse->addWidget(lineEditDirectory);
    browse->addWidget(btnBrowse);

    btns->addWidget(btnBuild);
    btns->addWidget(btnReset);
    btns->addWidget(btnHelp);



    _layout->addLayout(browse);
    _layout->addWidget(table);
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

    //TODO : change it to file
//    QDirIterator it(directory);
//    while (it.hasNext()) {
//        QString temp = it.next();
//        if (temp.endsWith(".txt")) {
//            slt_add(temp);
//        }
//    }

}

void TabDockWidget::slt_update(QString _file) {
    // TODO : write update code
//    QStringList temp;
//    temp = _file.split(QDir::separator());
//    File* tFile = new File;
//    tFile->name = temp.back();
//    tFile->path = _file;
//    names.append(tFile->name);
//    paths.append(tFile->path);
//    files.append(tFile);
//    QStandardItem *item = new QStandardItem(temp.back());
//    item->setEditable(false);
//    model->appendRow(item);

//    emit sig_fileToBuild(tFile);
//    signalCounter++;
}

void TabDockWidget::slt_build() {

    // TODO : write build code
//    Q_FOREACH(File* file, files) {
//        if (!lastFiles.contains(file->name)) {
//            btnBuild->setEnabled(false);
//            cmbDataStrct->setEnabled(false);
//            lastFiles.append(file->name);
//            emit sig_fileToBuild(file);
//            signalCounter++;
//        }
//    }
//    if (signalCounter == 0) {
//        monitor->show("Tree is Update, There's Nothing to build", Qt::red);
//    }
}

void TabDockWidget::slt_buildComplete() {

    btnBuild->setEnabled(true);
}

void TabDockWidget::slt_showLines(SearchResult * _sr) {
    // TODO : check this
    return;
    if (_sr->words.size() == 0) {
        monitor->show("Nothing found", Qt::black);
        return;
    }
    if (_sr->words.size() == 1) {
        Q_FOREACH(Data datum, _sr->result[0]) {
            showDatum(datum);
        }
    } else {
        QList<Data> shared = _sr->result[0];
        QList<bool> sameLine;
        QStringList files;
        for (int i{}; i < shared.size();i++)
            sameLine.append(true);
        bool common = false;
        for (size_t i{1}; i < _sr->words.size(); i++) {
            for (size_t k{}; k < shared.size(); k++) {
                common = false;
                for(size_t j{}; j < _sr->result[i].size(); j++) {
                    if (shared[k].file == _sr->result[i][j].file) {
                        common = true;
                        if (i == _sr->words.size() - 1) {
                            if (!files.contains(shared[k].file)) {
                                files.append(shared[k].file);
                            }
                        }
                    }
                }
                if (!common) {
                    shared.removeAt(k--);
                }
            }
        }

        qDebug() << "Share " << files.size();
        QString result = "|";
        Q_FOREACH(QString file, files) {
            file.chop(4);
            result += file + ", ";
        }
        monitor->show(result, Qt::black);
    }
}

void TabDockWidget::showDatum(const Data& _datum) {
    // TODO : check this
    return;
    QFile file(directory + QDir::separator() + _datum.file);
    QByteArray byteArr;
    file.open(QIODevice::ReadOnly);
    for(int i{};i < _datum.lineNum; i++) byteArr = file.readLine();
    byteArr.chop(2);
    showLine(QString(byteArr), _datum);
    file.close();
}

void TabDockWidget::showLine(const QString& _line,
                             const Data&    _datum) {
    // TODO : check this
    return;
    QString result;
    QString start{};
    QString end{};
    QStringList split = _line.split(" ");
    if (split.size() < 8) { //Full Sentence
        result = _line;

    } else {
        if (_datum.wordNum > 3) { // START WITH ...
            start = " ... ";
            for(size_t i{0}; i < _datum.wordNum - 3;i++) {
                if (split.first() != "\n" && split.first() != "\r\n") {
                    split.pop_front();
                }
            }
        }
        int sc = split.count() - _datum.wordNum;
        if (sc > 3) { // END WITH ...
            for(int i{split.size()}; i > _datum.wordNum + 3;i--) {
                if (split.last() != "\n" && split.last() != "\r\n") {
                    split.pop_back();
                }
            }
            end = " ... ";
        }

        Q_FOREACH(QString word, split) {
            if (word != "\n" && word != "\r\n") {
                result.append(word + " ");
            }
        }


    }

    result = "|"
            + _datum.file
            + QString(" -> L: %1 ").arg(_datum.lineNum)
            + start
            + result
            + end;

    monitor->show(result, Qt::black);
}

void TabDockWidget::proccesFile(QFile & _file) {
    QList<QByteArray> first = _file.readLine().simplified().split(' ');
    QList<int> states;
    Q_FOREACH(QByteArray word, first) {
        bool ok {false};
        int tState {word.toInt(&ok)};
        if (ok) {
            states.append(tState);
        }
    }

    while(_file.canReadLine()) {
        QList<QByteArray> tLine = _file.readLine().simplified().split(' ');
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
    monitor->clear();
}
