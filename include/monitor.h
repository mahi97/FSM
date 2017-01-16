#ifndef MONITOR_H
#define MONITOR_H

#include <QTextEdit>
#include <QScrollBar>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenu>
#include <QMessageBox>

#include <qgv/QGVEdge.h>
#include <qgv/QGVScene.h>
#include <qgv/QGVNode.h>
#include <qgv/QGVSubGraph.h>



#include "base.h"

class Monitor : public QGraphicsView {

    Q_OBJECT

public:
    Monitor(QWidget* parent);
    ~Monitor();
private:
    QGVScene *m_scene;

public slots:
    void slt_show();
    void nodeContextMenu(QGVNode* node);
    void nodeDoubleClick(QGVNode* node);
};

extern Monitor* monitor;

#endif // MONITOR_H
