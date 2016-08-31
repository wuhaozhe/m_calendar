#include "startwindow.h"
#include "ui_startwindow.h"

startWindow::startWindow(global *b, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::startWindow)
{
    c = b;
    ui->setupUi(this);
}

startWindow::~startWindow()
{
    delete ui;
}

void startWindow::on_pushButton_clicked()
{
    this->window = new MainWindow(c);
    this->window->show();
    this->hide();
}

void startWindow::on_pushButton_2_clicked()
{
    string filename = ui->lineEdit->text().toStdString();
    in_config temp;
    temp.set_configname(filename);
    this->window = new MainWindow(c);
    this->window->show();
    this->hide();
}

void startWindow::on_pushButton_3_clicked()
{
    in_config temp;
    temp.out_configname("configuration.txt");
    QLabel *label = new QLabel(tr("config success!"));
    label->show();
}
