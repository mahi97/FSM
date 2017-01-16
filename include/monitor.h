#ifndef MONITOR_H
#define MONITOR_H

#include <QTextEdit>
#include <QScrollBar>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "base.h"

class Monitor : public QGraphicsView {

    Q_OBJECT

public:
    Monitor(QWidget* parent);
    ~Monitor();
private:
public slots:

};

extern Monitor* monitor;

#endif // MONITOR_H
