#ifndef WIDGET_MESSAGE_H
#define WIDGET_MESSAGE_H
#include <string>
#include <QColor>
#include <vector>
#include <sstream>
using namespace std;

class widget_message
{
public:
    string dir = "";
    QColor color = Qt::white;                //格子的颜色
    vector<string> filedate;         //来自的文件夹
    vector<string> filename;         //文件名
    vector<string> filecontent;         //文件内容
    int happen_flag  = -1;             //0 is byday, 1 is byweek, 2 is bymonth
    widget_message();
    string delete_filedate;                     //建立该文件的文件夹
    string delete_fliename;
    int delete_filemode;
    //void get_delete(int year, int month, int day, string file_name, int filemode);
};

#endif // WIDGET_MESSAGE_H
