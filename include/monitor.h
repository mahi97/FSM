#ifndef MONITOR_H
#define MONITOR_H

#include <QTextEdit>
#include <QScrollBar>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenu>
#include <QMessageBox>

#include "base.h"

class Monitor : public QTextEdit {

    Q_OBJECT

public:
    Monitor(QWidget* parent);
    ~Monitor();
    void show(QString, QColor);
private:
    QColor defaultColor;
public slots:
    void slt_show(ShowMaterial*);
};

extern Monitor* monitor;

#endif // MONITOR_H
