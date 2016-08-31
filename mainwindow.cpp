#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(global *b, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    a = b;
    ui->setupUi(this);
    //qDebug("hehe");
    m_calendar = new basiccalendar(a, this);
    ui->verticalLayout->addWidget(m_calendar);
    ui->spinBox->setValue(m_calendar->calendar_year);
    ui->spinBox_2->setValue(m_calendar->calendar_month);
    connect(this, SIGNAL(drag_index_change()), m_calendar, SLOT(react_drag_change()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(m_calendar->calendar_month == 1)
    {
        m_calendar->calendar_month = 12;
        m_calendar->calendar_year--;
    }
    else
        m_calendar->calendar_month--;
    m_calendar->set_calendar(m_calendar->calendar_year, m_calendar->calendar_month);
    ui->spinBox->setValue(m_calendar->calendar_year);
    ui->spinBox_2->setValue(m_calendar->calendar_month);
    m_calendar->fresh_calendar();
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(m_calendar->calendar_month == 12)
    {
        m_calendar->calendar_month = 1;
        m_calendar->calendar_year++;
    }
    else
        m_calendar->calendar_month++;
    m_calendar->set_calendar(m_calendar->calendar_year, m_calendar->calendar_month);
    ui->spinBox->setValue(m_calendar->calendar_year);
    ui->spinBox_2->setValue(m_calendar->calendar_month);
    m_calendar->fresh_calendar();
    update();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    m_calendar->calendar_year = arg1;
    m_calendar->set_calendar(m_calendar->calendar_year, m_calendar->calendar_month);
    m_calendar->fresh_calendar();
    update();
}

void MainWindow::on_spinBox_2_editingFinished()
{

}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    m_calendar->calendar_month = arg1;
    m_calendar->set_calendar(m_calendar->calendar_year, m_calendar->calendar_month);
    m_calendar->fresh_calendar();
    update();
}


void MainWindow::on_pushButton_4_clicked(bool checked)
{
    if(checked)
    {
        this->setWindowFlags(Qt::WindowTransparentForInput | Qt::FramelessWindowHint);
        this->setWindowOpacity(0.8);
        this->show();
        QLabel *p = new QLabel(tr("press Enter to set the calendar not transparent"));
        p->show();
    }
    else
    {
            this->setWindowFlags(Qt::Window);
            this->setWindowOpacity(1);
            this->show();
    }
}


void MainWindow::fresh()
{


    ui->retranslateUi(this);


}

void MainWindow::on_pushButton_3_clicked()
{
    //qDebug("pu");
    QTranslator translator;
    if(ui->radioButton_2->isChecked())
    {
        a->index = 0;
        //qDebug("hehe");
        if(translator.load("cn.qm"))
            qApp->installTranslator(&translator);
        fresh();

        //qDebug("hehe");
        m_calendar->fresh();
        //qDebug("hehe");
    }
    else if(ui->radioButton->isChecked())
    {
        //qDebug("haha");
        a->index = 1;
        if(translator.load(""))
        {
             qApp->installTranslator(&translator);
        }
        fresh();
        m_calendar->fresh();
    }
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
        a->drag_index = 1;
    else
        a->drag_index = 0;
    emit drag_index_change();
}
