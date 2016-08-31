#include "basicwidget.h"

void basicwidget::paintEvent(QPaintEvent *ev)
{
    QPainter m_painter(this);
    QFont m_font("Helvetica");
    m_font.setPointSize(10);
    m_painter.setPen(QPen(pen_color));
    m_painter.setBrush(QBrush(brush_color));
    m_painter.setFont(m_font);
    m_painter.drawRect(0, 0, this->width(), this->height());
    m_painter.drawText(this->width() / 2 - 50, this->height() / 2 - 10, 100, 20, Qt::AlignCenter, content);
    m_font.setPointSize(3);
    for(int i = 0; i < content_filename.size(); i++)
    {
        //qDebug()<<i;
        m_painter.drawText(1, i * 10 + 2, 70, 15, Qt::AlignLeft, content_filename[i]);
    }

}
basicwidget::basicwidget(QString temp, QWidget *parent): QWidget(parent)
{
    setAcceptDrops(true);
    input_color = brush_color;
    content = temp;
    update();
}
void basicwidget::react_clicked()
{
    brush_color = QColor(0x8F, 0x8F, 0xBD);
    update();
}
void basicwidget::mousePressEvent(QMouseEvent *ev)
{
    emit clicked();
    QColor(0x8F, 0x8F, 0xBD);
}

void basicwidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
    //qDebug("haha");
    emit doubleclicked();
}

void basicwidget::set_color(QColor input)
{
    input_color = input;
}

void basicwidget::dragEnterEvent(QDragEnterEvent *ev)
{
    if(ev->mimeData()->hasFormat("text/uri-list"))       //测试是否含有文字资讯的uri
        ev->acceptProposedAction();         //接受建议动作
}

void basicwidget::dropEvent(QDropEvent *ev)
{
    QList<QUrl> urls = ev->mimeData()->urls();
    if(urls.isEmpty())
        return;
    for(int i = 0; i < urls.size(); i++)
    {
        add_filename = urls[i].toLocalFile();
        filename_withoutpath = urls[i].fileName();
        //add_filename.replace("/", "\\");
        emit addfile();
    }
}
