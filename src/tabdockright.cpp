#include "tabdockright.h"


TabDockRightWidget* tabDockRight;

TabDockRightWidget::TabDockRightWidget(QWidget *parent) : QDockWidget(parent) {

    m_table = new QTableView(this);
    m_model = new QStandardItemModel(this);

   // slt_update();

    m_table->setModel(m_model);
    setWidget(m_table);


    //Connections
    connect(tabDock, SIGNAL(sig_fileOpend()), this, SLOT(slt_update()));
    connect(tabDock, SIGNAL(sig_build()), this, SLOT(slt_build()));
}

TabDockRightWidget::~TabDockRightWidget() {

}

void TabDockRightWidget::slt_update() {

    m_model->clear();
    QStandardItem* item1 = new QStandardItem("State");
//    QStandardItem* item2 = new QStandardItem("Adjacent");

    QList<QStandardItem*> items;
    items.append(item1);
//    items.append(item2);
    m_model->appendRow(items);

    for (size_t j{}; j < tabDock->getState(); j++) {
        QList<QStandardItem*> rows;
            QStandardItem *item = new QStandardItem(QString("> %1").arg(j));
            rows.append(item);
        m_model->appendRow(rows);
    }

}
void TabDockRightWidget::slt_build() {
    QList<QStandardItem*> items;
    QStandardItem* adj = new QStandardItem("Adjacent");
    items.append(adj);
    for (size_t i{1}; i <= tabDock->getState(); i++) {
        QStandardItem* item;
        QString sss;
        for (size_t j{1}; j <= tabDock->getState(); j++) {
            QStandardItem* item = tabDock->getModel()->
                    item(i, j);
            if (item->text() == "-") continue;
            QStringList s = item->text().split(",");
            Q_FOREACH(QString ss, s) {
                sss.append(QString("(%1, %2), ").arg(j - 1).arg(ss));

            }
        }
        item = new QStandardItem(sss);
        items.append(item);

    }
    m_model->removeColumn(1);
    m_model->insertColumn(1, items);
    m_table->setColumnWidth(1, 300);

}
