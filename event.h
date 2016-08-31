#ifndef EVENT_H
#define EVENT_H
#include <QColor>
#include <string>
using namespace std;

class event
{
public:
    int happen_flag;      //0 is byday, 1 is byweek, 2 is bymonth
    QColor event_color;
    string filename;
    event();
    event(int in_flag, QColor in_color, string in_filename);
};

#endif // EVENT_H
