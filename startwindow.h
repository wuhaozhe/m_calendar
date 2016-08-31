#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "in_config.h"
#include <QLabel>
#include "global.h"

namespace Ui {
class startWindow;
}

class startWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit startWindow(global *a, QWidget *parent = 0);
    ~startWindow();
    MainWindow *window;
    global *c;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::startWindow *ui;
};

#endif // STARTWINDOW_H
