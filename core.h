#ifndef CORE_H
#define CORE_H
#include <QVector>
#include <QTime>

class core
{
public:
    QVector<int> calendar_num;
    core();
    QVector<int> get_num(int year, int month);
};

#endif // CORE_H
