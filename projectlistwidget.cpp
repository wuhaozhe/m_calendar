#include "projectlistwidget.h"

ProjectListWidget::ProjectListWidget(QString date, QWidget *parent): QListWidget(parent)
{
    prensent_date = date;
    setAcceptDrops(true);
}

void ProjectListWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        performDrag();
    }
    QListWidget::mousePressEvent(event);
}


void ProjectListWidget::performDrag()
{
    QListWidgetItem *item = currentItem();
    if (item) {
        emit pressed(currentRow());
        QMimeData *mimeData = new QMimeData;
        QString name = prensent_date;
        name += '/';
        name += item->text();
        qDebug()<<qPrintable(name);
        QFileInfo i(name);
        QUrl u(QUrl::fromLocalFile(i.absoluteFilePath()));
        QList<QUrl> l;
        l.append(u);
        mimeData->setUrls(l);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        Qt::DropAction dropAction = drag->exec(Qt::CopyAction);
    }
}

