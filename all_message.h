#ifndef ALL_MESSAGE_H
#define ALL_MESSAGE_H
#include <fstream>
#include <QColor>
#include <string>
#include <vector>
#include <QVector>
#include <QDebug>
#include <QString>
#include "event.h"
#include "widget_message.h"
#include <map>
#include <sstream>
#include <QDir>
#include <QDate>
#include <QFile>
#include <fstream>
#include <utility>
#include "core.h"
using namespace std;

class All_Message
{
public:
    string config_filename;
    widget_message each_message[50];
    map< string, vector<event> > m_map;
    map< pair<string, string> , vector<string> > delete_info;         //文件对应删除！ date, filename, 需要删除的时间
    All_Message();
    void explain_config(string filename);
    void deal_each_day(vector<string> string_array);
    void assign_message(int year, int month);      //use this one to update
    void assign_delete_message(int year , int month , int day , string from_date, string file_name , int delete_filemode);
    int index(int year, int month, int day);
    void set_widget_message(event &temp_event, widget_message &temp_message, string temp_date);
    void delete_configline(string delete_filedate, string delete_filename);
    void add_delete_info(int year, int month, int day, string from_date, string file_name);
    int search_index(string file_date, string file_name, vector<string> input);
    bool judge(string from_date, string file_name, int year, int month, int day);
                                       //注意执行结尾要explain_config, assignmessage!
    void change_message(widget_message temp_message);
    void clear_each_message();
};

#endif // ALL_MESSAGE_H
