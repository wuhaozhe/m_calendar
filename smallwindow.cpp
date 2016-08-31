#include "smallwindow.h"
#include "ui_smallwindow.h"
#include "basiccalendar.h"
#include <QTranslator>

SmallWindow::SmallWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmallWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    win_parent = dynamic_cast<basiccalendar*>(this->parentWidget());
}

SmallWindow::SmallWindow(int index, QWidget *parent):
    QMainWindow(parent), trans_index(index), ui(new Ui::SmallWindow)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::WindowModal);
    this->setWindowFlags(Qt::Window);
    win_parent = dynamic_cast<basiccalendar*>(this->parentWidget());
    int index1 = win_parent->a->index;
    QTranslator translator;
    if(index1 == 0)
    {
        //qDebug("hehe");
        if(translator.load("cn.qm"))
            qApp->installTranslator(&translator);
        fresh();
    }
    else if(index1 == 1)
    {
        if(translator.load(""))
        {
             qApp->installTranslator(&translator);
        }
        fresh();
    }
    connect(this, SIGNAL(parent_update()), win_parent, SLOT(react_smallwindow()));
    for(int i = 0; i < (win_parent->trans_info).each_message[trans_index].filename.size(); i++)
    {
        //qDebug()<<i;
        QString temp = QString::fromStdString((win_parent->trans_info).each_message[trans_index].filename[i]);
        ui->comboBox->addItem(temp);
    }
    QString year = QString::number(win_parent->calendar_year);
    QString month = QString::number(win_parent->calendar_month);
    QString day = win_parent->m_widgets[trans_index]->content;
    QString date = year; date += '-'; date += month; date += '-'; date += day;
    listwidget = new ProjectListWidget(date, this);
    connect(listwidget, SIGNAL(pressed(int)), this, SLOT(react_pressed(int)));
    ui->verticalLayout->addWidget(listwidget);
    for(int i = 0; i < ui->comboBox->count(); i++)
    {
        //QLabel label(ui->comboBox->itemText(i));
        listwidget->addItem(ui->comboBox->itemText(i));
    }
    //ui->radioButton->setDown(true);
}
SmallWindow::~SmallWindow()
{
    delete ui;
}

void SmallWindow::on_pushButton_6_clicked()
{
    QColor temp;
    temp = QColorDialog::getColor(Qt::white);
    if(temp.isValid())
    {
        //qDebug("hehe");
        trans_color = temp;
        //qDebug()<<trans_color.red()<<" "<<trans_color.green()<<" "<<trans_color.blue();
    }
    //qDebug()<<trans_index;
    //qDebug("hehe");
    (win_parent->trans_info).each_message[trans_index].color = trans_color;
    //qDebug("1");
    //(win_parent->trans_info).change_message((win_parent->trans_info).each_message[trans_index]);
    //qDebug("2");
    //(win_parent->trans_info).assign_message(win_parent->calendar_year, win_parent->calendar_month);
}

void SmallWindow::on_comboBox_activated(int index)
{
    present_edit_index = index;
    ui->textEdit->setPlainText(QString::fromStdString((win_parent->trans_info).each_message[trans_index].filecontent[index]));
}

void SmallWindow::on_pushButton_5_clicked()             //这项改变要添加到widget中显示，处理日期后更改widget_message中的信息，change,assign后发出parent_update信号
{
    QString get_text = ui->textEdit->toPlainText();
    QString file_name;
    for(int i = 0; i < 5; i++)
    {
        if(get_text.size() > i)
            file_name += get_text[i];
    }
    file_name += ".txt";
    ui->comboBox->addItem(file_name);
    ui->comboBox->setCurrentIndex(ui->comboBox->count() - 1);
    //QLabel label(file_name);
    listwidget->addItem(file_name);
    //(win_parent->m_widgets[trans_index]->content_filename).push_back(file_name);
    QString year = QString::number(win_parent->calendar_year);
    QString month = QString::number(win_parent->calendar_month);
    QString day = win_parent->m_widgets[trans_index]->content;
    QString date = year; date += '-'; date += month; date += '-'; date += day;
    (win_parent->trans_info).each_message[trans_index].filedate.push_back(date.toStdString());
    (win_parent->trans_info).each_message[trans_index].filecontent.push_back(get_text.toStdString());
    (win_parent->trans_info).each_message[trans_index].filename.push_back(file_name.toStdString());
    (win_parent->trans_info).each_message[trans_index].happen_flag = add_mode;

    (win_parent->trans_info).change_message((win_parent->trans_info).each_message[trans_index]);
    (win_parent->trans_info).assign_message(win_parent->calendar_year, win_parent->calendar_month);
    emit parent_update();
}

void SmallWindow::on_pushButton_3_clicked()
{
    if(ui->radioButton->isChecked())
        add_mode = 0;
    else if(ui->radioButton_2->isChecked())
        add_mode = 1;
    else if(ui->radioButton_3->isChecked())
        add_mode = 2;
    qDebug()<<add_mode;
}

void SmallWindow::on_pushButton_2_clicked()
{
    int delete_mode = 0;
    if(ui->radioButton_4->isChecked())
        delete_mode = 0;
    else if(ui->radioButton_5->isChecked())
        delete_mode = 1;
    else if(ui->radioButton_6->isChecked())
        delete_mode = 2;
    //qDebug()<<delete_mode;

    int year = win_parent->calendar_year;
    int month = win_parent->calendar_month;
    int day = (win_parent->m_widgets[trans_index]->content).toInt();
    int temp_index = ui->comboBox->currentIndex();
    ui->comboBox->removeItem(temp_index);
    QListWidgetItem *w_item = listwidget->item(temp_index);
    listwidget->removeItemWidget(w_item);
    string from_date = (win_parent->trans_info).each_message[trans_index].filedate[temp_index];
    string from_filename = (win_parent->trans_info).each_message[trans_index].filename[temp_index];
    (win_parent->trans_info).assign_delete_message(year, month, day, from_date, from_filename, delete_mode);
    emit parent_update();
}

void SmallWindow::react_pressed(int index)
{
    listwidget_index = index;
    string from_filename = (win_parent->trans_info).each_message[trans_index].filedate[index];
    listwidget->prensent_date = QString::fromStdString(from_filename);
}

void SmallWindow::fresh()
{
    ui->retranslateUi(this);
    qDebug("hehe");
}
