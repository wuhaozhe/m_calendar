#include "core.h"

core::core()
{

}

QVector<int> core::get_num(int year, int month)
{
    QVector<int> temp;
    QDate firstday = QDate(year, month, 1);
    int firstday_of_month = (firstday.dayOfWeek() - 1) * (-1);
    QDate firstday_of_calendar = firstday.addDays(firstday_of_month);
    temp.push_back(firstday_of_calendar.weekNumber());         //get the week number

    if(firstday_of_month != 0)
    {
        for(int i = firstday_of_calendar.day(); i <= firstday_of_calendar.daysInMonth(); i++)
            temp.push_back(i);
    }
    for(int i = 0; i < firstday.daysInMonth(); i++)
    {
        QDate temp_date = firstday.addDays(i);
        temp.push_back(temp_date.day());
        if(temp_date.dayOfWeek() == 7 && i != (firstday.daysInMonth() - 1))
            temp.push_back((temp_date.weekNumber() + 1) % 52);
        if(i == firstday.daysInMonth() - 1)
        {
            for(int j = 1; j <= 7 - temp_date.dayOfWeek(); j++)
                temp.push_back(j);
        }
    }

    return temp;
}
