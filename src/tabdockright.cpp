#include "tabdockright.h"


TabDockRightWidget* tabDockRight;

TabDockRightWidget::TabDockRightWidget(QWidget *parent) : QDockWidget(parent) {

    m_table = new QTableView(this);
    m_model = new QStandardItemModel(this);
    for (size_t j{}; j < 10; j++) {
        QList<QStandardItem*> rows;
        for (size_t i {}; i < 10;i++) {
            QStandardItem *item = new QStandardItem(QString("> %1").arg(i));
            rows.append(item);
        }
        m_model->appendRow(rows);
    }
    m_table->setModel(m_model);
    setWidget(m_table);
}

TabDockRightWidget::~TabDockRightWidget() {

}
