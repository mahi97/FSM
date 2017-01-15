#ifndef QUEUE_H
#define QUEUE_H

#include <QList>

class Queue : public QList<char> {
public:
    inline void enqueue(const char &t) { QList<char>::append(t); }
    inline char dequeue() { return QList<char>::takeFirst(); }
    inline char &head() { return QList<char>::first(); }
    inline const char &head() const { return QList<char>::first(); }};

#endif // QUEUE_H
