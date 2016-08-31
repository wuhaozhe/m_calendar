#include "event.h"

event::event()
{
    happen_flag = -1;
    event_color = Qt::white;
    filename = "";
}

event::event(int in_flag, QColor in_color, string in_filename)
{
    happen_flag = in_flag;
    event_color = in_color;
    filename = in_filename;
}
