#ifndef BASICCALENDAR_H
#define BASICCALENDAR_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDate>
#include <QDir>
#include <QString>
#include <string>
#include <QFile>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QSignalMapper>
#include <QColor>
#include <QTextStream>
#include <fstream>
#include <QDebug>
#include "basicwidget.h"
#include "core.h"
#include "week.h"
#include "smallwindow.h"
#include "all_message.h"
#include "global.h"

class basiccalendar: public QWidget
{
    Q_OBJECT
public:
    void fresh();
    All_Message trans_info;          // 底层和gui传输信息
    int calendar_year, calendar_month;
    QSignalMapper *m_map = new QSignalMapper(this);
    QSignalMapper *m_map2 = new QSignalMapper(this);
    QSignalMapper *m_map3 = new QSignalMapper(this);
    QHBoxLayout ** h_layouts;
    QVBoxLayout * v_layouts;
    basicwidget ** m_widgets;
    week *firstline;
    void set_calendar(int year, int month);
    global *a;
    basiccalendar(global *b, QWidget *parent = 0, int year = QDate::currentDate().year(), int month = QDate::currentDate().month());
    ~basiccalendar();
signals:
    void clicked(int);
    void double_clicked(int);
    void addfile(int);
public slots:
    void react_addfile(int);
    void react_clicked(int);
    void react_doubleclicked(int);
    void react_smallwindow();
    void fresh_calendar();             //up_date the calendar
    void react_drag_change();
};

#endif // BASICCALENDAR_H
