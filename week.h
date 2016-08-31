#ifndef WEEK_H
#define WEEK_H
#include <QWidget>
#include <QHBoxLayout>
#include "basicwidget.h"

class week: public QWidget
{
    Q_OBJECT
public:
    basicwidget ** m_widgets;
    QHBoxLayout *h_layout;
    week(QWidget *parent = 0);
};

#endif // WEEK_H
