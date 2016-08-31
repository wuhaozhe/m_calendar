#ifndef SMALLWINDOW_H
#define SMALLWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QColor>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <string>
#include <QListWidgetItem>
#include "projectlistwidget.h"

class basiccalendar;

namespace Ui {
class SmallWindow;
}

class SmallWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmallWindow(QWidget *parent = 0);
    SmallWindow(int index, QWidget *parent = 0);
    QColor trans_color;
    ~SmallWindow();
    Ui::SmallWindow *ui;
    int trans_index;
    basiccalendar* win_parent;
    int present_edit_index;
    ProjectListWidget *listwidget;
    int add_mode = 0;
    //QString date_of_listwidget;
    int listwidget_index;
    void fresh();
private slots:
    void on_pushButton_6_clicked();
    void on_comboBox_activated(int index);

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void react_pressed(int index);

signals:
    void parent_update();
};

#endif // SMALLWINDOW_H
