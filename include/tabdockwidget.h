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
#include <QLabel>

#include "base.h"
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




    QString directory;

    int signalCounter;

    PropertyGet(int, State, m_state);
    PropertyGet(QStandardItemModel*, Model, model);
    PropertyGet(QComboBox*, cmb_Start, start);
    PropertyGet(QLineEdit*, cmb_end, end);

public slots:
    void slt_open();
    void slt_build();
    void slt_reset();
    void slt_browse();
    void slt_buildComplete();

private:
    void proccesFile(QFile&);

    QList< QList< QList<char> > > matrix;

signals:
    void sig_fileToBuild(File*);
    void sig_fileOpend();
    void sig_build();

};

extern TabDockWidget* tabDock;

#endif // TABDOCKWIDGET_H
