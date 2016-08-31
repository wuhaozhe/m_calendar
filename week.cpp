#include "week.h"
#include <QColor>

week::week(QWidget *parent): QWidget(parent)
{
    h_layout = new QHBoxLayout();

    m_widgets = new basicwidget*[8];
    for(int i = 0; i < 8; i++)
    {
        m_widgets[i] = new basicwidget();
        m_widgets[i]->setParent(this);
        m_widgets[i]->brush_color = QColor(0x7f, 0xff, 0x00);
        m_widgets[i]->setWindowOpacity(0.8);
        h_layout->addWidget(m_widgets[i]);
    }
    m_widgets[0]->content = tr("week");
    m_widgets[1]->content = tr("Monday");
    m_widgets[2]->content = tr("Tuesday");
    m_widgets[3]->content = tr("Wednesday");
    m_widgets[4]->content = tr("Thursday");
    m_widgets[5]->content = tr("Friday");
    m_widgets[6]->content = tr("Saturday");
    m_widgets[7]->content = tr("Sunday");
}
