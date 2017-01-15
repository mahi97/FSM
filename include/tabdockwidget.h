#ifndef TABDOCKWIDGET_H
#define TABDOCKWIDGET_H

#include <QDockWidget>
#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QLayout>
#include <QComboBox>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QLineEdit>
#include <QDirIterator>
#include <QDir>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QListView>
#include <QApplication>
#include <QFileInfo>
#include <QCheckBox>
#include <QTableView>

#include "base.h"
#include "searchthread.h"
#include "monitor.h"

class TabDockWidget : public QDockWidget
{

    Q_OBJECT

public:
    TabDockWidget(QWidget* parent);
    ~TabDockWidget();


private:

    void fillLayout(QVBoxLayout *_layout);
    QWidget *w;
    ///////
    QPushButton *btnBrowse;
    QPushButton *btnBuild;
    QPushButton *btnReset;
    QPushButton *btnHelp;
    QLineEdit   *lineEditDirectory;
    QTableView  *table;
    QStandardItemModel *model;

    QString directory;

    int signalCounter;

public slots:
    void slt_open();
    void slt_build();
    void slt_reset();
    void slt_browse();
    void slt_buildComplete();
    void slt_update(QString _file);
    void slt_showLines(SearchResult*);

private:
    void showDatum(const Data &);
    void showLine (const QString&, const Data&);
    void proccesFile(QFile&);

    QList< QList< QList<char> > > matrix;

signals:
    void sig_changeTree(ETree);
    void sig_fileToBuild(File*);


};

extern TabDockWidget* tabDock;

#endif // TABDOCKWIDGET_H
