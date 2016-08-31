#ifndef BASICWIDGET_H
#define BASICWIDGET_H
#include <QWidget>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QRect>
#include <QDebug>
#include <QDate>
#include <QVector>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QList>
#include <QUrl>

class basicwidget: public QWidget
{
    Q_OBJECT
public:
    QString content;
    //QString dragin_file;
    QVector <QString> content_filename;
    QColor brush_color = Qt::white;
    QColor init_color;
    QColor pen_color = Qt::black;
    QColor input_color = Qt::white;         //改颜色用的！
    QString add_filename;
    QString filename_withoutpath;
    basicwidget(QString temp = "", QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void set_color(QColor input);
protected:
    void paintEvent(QPaintEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);
    void dropEvent(QDropEvent *ev);
public slots:
    void react_clicked();
signals:
    void clicked();
    void doubleclicked();
    void addfile();
};

#endif // BASICWIDGET_H
