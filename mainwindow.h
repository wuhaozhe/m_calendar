#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "basiccalendar.h"
#include <QLabel>
#include <QKeyEvent>
#include <QTranslator>
#include <QTime>
#include <QTimer>
#include "global.h"
#include <QPaintEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    basiccalendar *m_calendar;
    void fresh();
    explicit MainWindow(global *b, QWidget *parent = 0);
    int flag = 0;
    global *a;
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *ev);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_editingFinished();

    void on_spinBox_2_valueChanged(int arg1);


    void on_pushButton_4_clicked(bool checked);


    void on_pushButton_3_clicked();


    void on_checkBox_clicked(bool checked);

private:
    Ui::MainWindow *ui;
signals:
    void drag_index_change();
};

#endif // MAINWINDOW_H
