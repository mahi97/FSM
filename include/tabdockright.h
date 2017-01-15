#ifndef TABDOCKRIGHT_H
#define TABDOCKRIGHT_H

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
#include <QStandardItemModel>

#include "base.h"
#include "searchthread.h"
#include "monitor.h"
#include "tabdockwidget.h"

class TabDockRightWidget : public QDockWidget{

    Q_OBJECT

public:
    TabDockRightWidget(QWidget* parent);
    ~TabDockRightWidget();
private:
    QTableView* m_table;
    QStandardItemModel* m_model;
    QStringList adjacents;

public slots:
    void slt_update();
    void slt_build();

};

extern TabDockRightWidget* tabDockRight;

#endif // TABDOCKRIGHT_H
