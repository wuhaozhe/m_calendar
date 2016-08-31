#ifndef PROJECTLISTWIDGET_H
#define PROJECTLISTWIDGET_H
#include <QListWidget>
#include <QString>
#include <QPoint>
#include <QDrag>
#include <QListWidget>
#include <QDebug>
#include <QUrl>
#include <QList>
#include <QMimeData>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QFileInfo>
class ProjectListWidget: public QListWidget
{
    Q_OBJECT
public:
    QString prensent_date;
    ProjectListWidget(QString date, QWidget *parent = 0);

protected:
    void mousePressEvent (QMouseEvent *event);
private:
    void performDrag();
signals:
    void pressed(int);

};

#endif // PROJECTLISTWIDGET_H
