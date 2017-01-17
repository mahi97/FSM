#include "monitor.h"

Monitor* monitor;

Monitor::Monitor(QWidget *parent) : QTextEdit(parent) {

    this->setReadOnly(true);
    this->setFont(QFont("Monaco"));
    this->defaultColor = Qt::black;

}

Monitor::~Monitor() {
    QFileDialog fd;
    QString str;
    str = fd.getSaveFileName(this, "Save output File");
    if (str.size() > 3) {
        QFile file(str);
        file.open(QIODevice::WriteOnly);
        file.write(this->toPlainText().toLatin1());
        file.close();
    }
}

void Monitor::show(QString _str, QColor _color) {
    this->setTextColor(_color);
    this->append(_str);
    this->setTextColor(Qt::black);
}

void Monitor::slt_show(ShowMaterial * _toShow) {
    this->setTextColor(_toShow->color);
    this->append(_toShow->line);
    this->setTextColor(defaultColor);
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());

}
