#include "basiccalendar.h"

basiccalendar::basiccalendar(global * b, QWidget *parent, int year, int month): QWidget(parent), calendar_year(year), calendar_month(month)
{
    //qDebug("hehe");
    a = b;
    this->resize(1000, 800);
    m_widgets = new basicwidget*[40];
    for(int i = 0; i < 40; i++)
    {
        m_widgets[i] = new basicwidget;
        m_widgets[i]->setParent(this);
    }
    h_layouts = new QHBoxLayout*[5];
    for(int i = 0; i < 5; i++)
    {
        h_layouts[i] = new QHBoxLayout();
        h_layouts[i]->setSpacing(2);
    }
    v_layouts = new QVBoxLayout(this);
    v_layouts->setSpacing(2);
    firstline = new week();
    v_layouts->addLayout(firstline->h_layout);
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 8; j++)
        {
            h_layouts[i]->addWidget(m_widgets[8 * i + j]);
        }
    for(int i = 0; i < 5; i++)
    {
        v_layouts->addLayout(h_layouts[i]);
    }
    set_calendar(calendar_year, calendar_month);
    for(int i = 0; i < 40; i++)
    {
        if(i % 8 == 0)
            continue;
        connect(m_widgets[i], SIGNAL(clicked()), m_map, SLOT(map()));
        m_map->setMapping(m_widgets[i], i);
        //connect(m_map, SIGNAL(mapped(int)), this, SIGNAL(clicked(int)));

        connect(m_widgets[i], SIGNAL(doubleclicked()), m_map2, SLOT(map()));
        m_map2->setMapping(m_widgets[i], i);
        //connect(m_map2, SIGNAL(mapped(int)), this, SIGNAL(double_clicked(int)));

        connect(m_widgets[i], SIGNAL(addfile()), m_map3, SLOT(map()));
        m_map3->setMapping(m_widgets[i], i);
    }
    connect(m_map, SIGNAL(mapped(int)), this, SIGNAL(clicked(int)));
    connect(m_map2, SIGNAL(mapped(int)), this, SIGNAL(double_clicked(int)));
    connect(m_map3, SIGNAL(mapped(int)), this, SIGNAL(addfile(int)));
    connect(this, SIGNAL(clicked(int)), this, SLOT(react_clicked(int)));
    connect(this, SIGNAL(double_clicked(int)), this, SLOT(react_doubleclicked(int)));
    connect(this, SIGNAL(addfile(int)), this, SLOT(react_addfile(int)));
    //qDebug("hehe");
    this->fresh_calendar();
}
basiccalendar::~basiccalendar()
{
    for(int i = 0; i < 40; i++)
        delete m_widgets[i];
    for(int i = 0; i < 5; i++)
        delete h_layouts[i];
    delete[] h_layouts;
    delete[] m_widgets;
    delete m_map;
}

void basiccalendar::set_calendar(int year, int month)
{
    core temp;
    QVector<int> out_put = temp.get_num(year, month);
    for(int i = 0; i < 40; i++)
    {
        m_widgets[i]->init_color = Qt::white;
        m_widgets[i]->brush_color = Qt::white;
    }
    for(int i = 0; i < 40; i++)
    {
        m_widgets[i]->content = QString::number(out_put[i]);
        if(i % 8 == 0)
        {
            m_widgets[i]->brush_color = QColor(240, 240, 240);
            m_widgets[i]->init_color = QColor(240, 240, 240);
        }
        else
        {
            if((m_widgets[i]->content).toInt() > 20 && i < 20)
            {
                m_widgets[i]->brush_color = QColor(240, 240, 1);
                m_widgets[i]->init_color = QColor(240, 240, 1);
            }
            if((m_widgets[i]->content).toInt() < 20 && i > 30)
            {
                m_widgets[i]->brush_color = QColor(240, 240, 1);
                m_widgets[i]->init_color = QColor(240, 240, 1);
            }
            //connect(m_widgets[i], SIGNAL(clicked()), m_widgets[i], SLOT(react_clicked()));
        }
    }
    for(int i = 0; i < 40; i++)
    {
        m_widgets[i]->init_color = m_widgets[i]->brush_color;
        if(m_widgets[i]->input_color != Qt::white)
        {
            m_widgets[i]->init_color = m_widgets[i]->input_color;
            m_widgets[i]->brush_color = m_widgets[i]->input_color;
        }
    }
    update();
}

void basiccalendar::react_clicked(int get_signal)
{
    for(int i = 0; i < 40; i++)
    {
        if(i % 8 != 0)
        {
            m_widgets[i]->brush_color = m_widgets[i]->init_color;
        }
    }
    //("hehe");
    m_widgets[get_signal]->brush_color = QColor(0x8F, 0x8F, 0xBD);
    update();
}

void basiccalendar::react_doubleclicked(int get_signal)
{

    SmallWindow *temp = new SmallWindow(get_signal, this);
    temp->show();
}

void basiccalendar::react_smallwindow()
{
    //qDebug("hehe");
    trans_info.assign_message(calendar_year, calendar_month);
    for(int i = 0; i < 40; i++)
    {
        (m_widgets[i]->content_filename).clear();
    }
    for(int i = 0; i < 40; i++)
    {
        m_widgets[i]->set_color(trans_info.each_message[i].color);
        for(int j = 0; j < trans_info.each_message[i].filecontent.size(); j++)
        {
            //qDebug()<<i<<" "<<qPrintable(QString::fromStdString(trans_info.each_message[i].filename[j]));
            m_widgets[i]->content_filename.push_back(QString::fromStdString(trans_info.each_message[i].filename[j]));
        }
    }
    set_calendar(calendar_year, calendar_month);
    for(int i = 0; i < 40; i++)
        m_widgets[i]->update();
    update();
}

void basiccalendar::fresh_calendar()
{
    for(int i = 0; i < 40; i++)
    {
        (m_widgets[i]->content_filename).clear();
    }
    //trans_info.assign_message(calendar_year, calendar_month);
    react_smallwindow();
}

void basiccalendar::react_addfile(int index)
{
    string file_text;
    QString add_filename = m_widgets[index]->add_filename;

    QString year = QString::number(calendar_year);
    QString month = QString::number(calendar_month);
    QString day = m_widgets[index]->content;
    QString date = year; date += '-'; date += month; date += '-'; date += day;
    QColor default_color = Qt::white;
    QString to_dir = date;
    to_dir += '/';
    to_dir += m_widgets[index]->filename_withoutpath;
    //qDebug()<<qPrintable(to_dir);
    if(!QFile::copy(add_filename, to_dir))
    {
        QDir *p = new QDir();
        p->mkdir(date);
        QFile::copy(add_filename, to_dir);
    }

    ifstream fin;
    fin.open(to_dir.toStdString().c_str());
    char a;
    while(fin.get(a))
        file_text += a;
    trans_info.each_message[index].color = default_color;
    trans_info.each_message[index].filedate.push_back(date.toStdString());
    trans_info.each_message[index].filecontent.push_back(file_text);
    trans_info.each_message[index].filename.push_back(m_widgets[index]->filename_withoutpath.toStdString());
    trans_info.each_message[index].happen_flag = 0;
    trans_info.change_message(trans_info.each_message[index]);

    trans_info.assign_message(calendar_year, calendar_month);
    react_smallwindow();
}

void basiccalendar::fresh()
{
    firstline->m_widgets[0]->content = tr("week");
    firstline->m_widgets[1]->content = tr("Monday");
    firstline->m_widgets[2]->content = tr("Tuesday");
    firstline->m_widgets[3]->content = tr("Wednesday");
    firstline->m_widgets[4]->content = tr("Thursday");
    firstline->m_widgets[5]->content = tr("Friday");
    firstline->m_widgets[6]->content = tr("Saturday");
    firstline->m_widgets[7]->content = tr("Sunday");
    for(int i = 0; i < 8; i++)
    {
        firstline->m_widgets[i]->update();
    }
}

void basiccalendar::react_drag_change()
{
    if(a->drag_index == 1)           //1 disconnect
    {
        disconnect(m_map3, SIGNAL(mapped(int)), this, SIGNAL(addfile(int)));
        disconnect(this, SIGNAL(addfile(int)), this, SLOT(react_addfile(int)));
        qDebug()<<a->drag_index;
    }
    else
    {
        connect(m_map3, SIGNAL(mapped(int)), this, SIGNAL(addfile(int)));
        connect(this, SIGNAL(addfile(int)), this, SLOT(react_addfile(int)));
        qDebug()<<a->drag_index;
    }
}
