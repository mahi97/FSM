#ifndef ISTACK_H
#define ISTACK_H

#include "base.h"

class IStack : public QVector<int> {
public:
    inline void push(const int& _str) {QVector<int>::append(_str);}
    inline int pop() {int s = this->data()[this->size() - 1];
                           this->resize(this->size() -1);
                           return s;}

    const int& top() const {return this->data()[this->size() - 1];}
    inline int top() {this->detach();
                          return this->data()[this->size() - 1];}

};


#endif // ISTACK_H
